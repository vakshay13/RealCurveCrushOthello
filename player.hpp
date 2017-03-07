#ifndef __PLAYER_H__
#define __PLAYER_H__
#define POSINF 2147483647
#define NEGINF -2147483648

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "common.hpp"
#include "board.hpp"
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft);
    vector<Move *> possibleMoves(Board boardCopy, Side side);
    vector<int> scores(vector<Move *> possible_moves);
    int naiveHeuristicScore(Board boardClone);
    int betterNaiveHeuristicScore(Board boardClone);
    scoredMove minimax(Board clone, int depth, bool maximizingPlayer);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
    Board board; //this is the internal board the player stores
    Side ourSide;
    Side opponentSide;
    vector<Move> opponentsSpots;
    vector<Move> ourSpots;
};

#endif
