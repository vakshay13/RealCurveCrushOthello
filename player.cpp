#include "player.hpp"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in tcest_minimax.cpp.
    testingMinimax = false;
    board = Board(); //this is the internal board the player stores
    ourSide = side;
    if(side == WHITE){ opponentSide = BLACK; } //set the opponent side
    else{ opponentSide = WHITE; } // That's racist
    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */

	board.doMove(opponentsMove, opponentSide); //update the board
	//opponentsSpots.push_back(opponentsMove);

	//Analyze the board
    //vector<Move *> possible_moves;
	if(board.hasMoves(ourSide)){
        /*
		//get possible moves
        possible_moves = possibleMoves(board);
        //Generate some Move
        srand(time(NULL));
        //Update the board
        vector<int> scoreArray = scores(possible_moves);
        //get the maximum score index in array
        int max = 0;
        int maxIndex = 0;
        for(int i = 0; i < (int)scoreArray.size(); i++){
        	if(scoreArray[i] > max){
        		max = scoreArray[i]; 
        		maxIndex = i;
        	 }
        }
        board.doMove(possible_moves[maxIndex], ourSide);
        //ourSpots.push_back(ourMove);
        return possible_moves[maxIndex];*/
        cerr << "before minimax" << endl;
        scoredMove scmove = minimax(board, 2 , true);
        cerr << "after minimax" << endl;
        cerr<< "ajsdlfjhaslkdfjh" <<scmove.move.x << ", " << scmove.move.y << endl;
        Move *actualmove = new Move(scmove.move.x, scmove.move.y);
        board.doMove(actualmove, ourSide);
        return actualmove;
    }
	return nullptr;
}

vector<Move *> Player::possibleMoves(Board boardCopy){
	//go through all the opponents spots naively
    vector<Move*> possible_moves;
	for(int x = 0; x < 8; x++){
		for (int y = 0; y < 8; y++){
            Move *move = new Move(x, y);
            if (boardCopy.checkMove(move, ourSide)){
                possible_moves.push_back(move);
            }
        }
	}
    return possible_moves;
}

//arguments: board
//create clone of board for every move and score each move
vector<int> Player::scores(vector<Move *> possible_moves){
	vector<int> scoreArray;
	for(int i = 0; i < (int)possible_moves.size(); i++){
		Board *boardClone = board.copy();
		boardClone->doMove(possible_moves[i], ourSide);
		scoreArray.push_back(betterNaiveHeuristicScore(*boardClone));
	}
	return scoreArray;
}

int Player::naiveHeuristicScore(Board boardClone){
	//Our chips - opponent chips
	return boardClone.count(ourSide) - boardClone.count(opponentSide);
}

int Player::betterNaiveHeuristicScore(Board boardClone){
    //found an arrray from a research paper.
    int scores_array[8][8] = {{4, -3, 2, 2, 2, 2, -3, 4}, {-3, -4, -1, -1, -1, -1, -4, -3}, 
    {2, -1, 1, 0, 0, 1, -1, 2}, {2, -1, 0, 1, 1, 0, -1, 2}, {2, -1, 0, 1, 1, 0, -1, 2}, 
    {2, -1, 1, 0, 0, 1, -1, 2}, {-3, -4, -1, -1, -1, -1, -4, -3},{4, -3, 2, 2, 2, 2, -3, 4}};
    vector<vector<int>> scoresVector;
    for(int i = 0; i < 8; i++){
    	vector<int> row;
    	for(int j = 0; j < 8; j++){
    		row.push_back(scores_array[i][j]);
    	}
    	scoresVector.push_back(row);
    }
    int score = 0;
    for (int x = 0; x < 8; x++){
        for (int y = 0; y < 8; y++){
            if (boardClone.getIndex(ourSide, x, y)){

                score += scoresVector[x][y];
            }
        }
    }
    return score;
}

scoredMove Player::minimax(Board clone, int depth, bool maximizingPlayer){
    //base case
    if(depth == 0 || clone.isDone()){
        return scoredMove(naiveHeuristicScore(clone), Move());
    }
    cerr << "1" << endl;
    //maximizing player
    if(maximizingPlayer){
        int bestValue = NEGINF; 
        Move *bestMove;
        vector<Move *> possible_moves = possibleMoves(clone);
        for(int i = 0; i < (int)possible_moves.size(); i++){
            Board *cloneCopy = clone.copy();
            (*cloneCopy).doMove(possible_moves[i], ourSide);
            scoredMove candidate = minimax(*cloneCopy, depth - 1, false);
            if(candidate.score > bestValue){ 
                bestValue = candidate.score;
                bestMove = new Move(possible_moves[i]->x, possible_moves[i]->y);
            }
        }
        cerr << "2" << endl;
        return scoredMove(bestValue, *bestMove);
    }
    
    else{
        cerr << "3" << endl;
        int bestValue = POSINF; 
        Move *bestMove;
        vector<Move *> possible_moves = possibleMoves(clone);
        for(int i = 0; i < (int)possible_moves.size(); i++){
            Board *cloneCopy = clone.copy();
            (*cloneCopy).doMove(possible_moves[i], opponentSide);
            scoredMove candidate = minimax(*cloneCopy, depth - 1, true);
            if(candidate.score < bestValue){ 
                bestValue = candidate.score;
                bestMove = new Move(possible_moves[i]->x, possible_moves[i]->y);
            }
        }
        cerr << "4" << endl;
        return scoredMove(bestValue, *bestMove);
    }
}