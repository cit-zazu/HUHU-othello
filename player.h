#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.h"
#include "board.h"
using namespace std;

class Player {
private:
    Board board;
    Side my_side;
    Side opponent_side;

public:
    Player(Side side);
    ~Player();
    
    
    Move *doMove(Move *opponentsMove, int msLeft);
    vector<int> simple_heuristic(Board* current_board, vector<Move*> validmoves, Side what_side);
    vector<int> minmax(vector<Move*> validmoves);
    int max_index(vector<int> vec);
    void set_board(Board board);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
