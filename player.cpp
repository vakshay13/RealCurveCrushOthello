#include "player.hpp"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
    Board board = Board(); //this is the internal board the player stores
    Side ourSide = side;
    Side opponentSide;
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
    vector<Move> possible_moves;
	if(board.hasMoves(ourSide)){
		//get possible moves
        possible_moves = possibleMoves();
	}

	//Generate some Move
    int random = rand()%((int)possible_moves.size()) + 1;

	//Update the board
	board.doMove(&possible_moves[random], ourSide);
	//ourSpots.push_back(ourMove);

    return nullptr;
}

vector<Move> Player::possibleMoves(){
	//go through all the opponents spots naively
    vector<Move> possible_moves;
	for(int x = 0; x < 8; x++){
		for (int y = 0; y < 8; y++){
            Move move = Move(x, y);
            if (board.checkMove(&move, ourSide)){
                possible_moves.push_back(move);
            }
        }
	}
    return possible_moves;
}
