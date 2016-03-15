#include "player.h"
#include <unistd.h>
#include <stdio.h>

/*
 * Leon's comment
 */ 

/*
 * Amy's comment
 */

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
    
    my_side = side;
    if (side == WHITE) {
        opponent_side = BLACK;
    }
    else {
        opponent_side = WHITE;
    }

    /* 
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
    cerr << "[Inside Player Default Constructor]\n";
}

/*
 * Destructor for the player.
 */
Player::~Player() {
    
    
}

int Player::max_index(vector<int> vec) {
    int max_index = 0;
    for (unsigned int i = 1; i < vec.size(); i++) {
        if (vec[i] > vec[max_index]) {
            max_index = i;
        }
    }
    return max_index;
}

/*
 * Gives the heuristic values corresponding to a vector of
 * valid moves.
 */
vector<int> Player::simple_heuristic(Board* current_board, vector<Move*> validmoves, Side what_side) {
    cerr << "[Inside Player simple_heuristic]\n";
    
    vector<int> heuristic_values;
    int value;
    int weight;
    if ((my_side == BLACK && what_side == WHITE) || (my_side == WHITE && what_side == BLACK)) {
        weight = - 10;
    }
    
    for (unsigned int i = 0; i < validmoves.size(); i++) {
        Board *temp_board = current_board->copy();
        temp_board->doMove(validmoves[i], what_side);
        value = temp_board->count(my_side) - temp_board->count(opponent_side);
        Move * temp = new Move(validmoves[i]->getX(), validmoves[i]->getY());
        if (temp->is_corner()) {
            value = value + weight;
        }

        // Case when corner = (x + 1, y)
        temp->setX(temp->getX() + 1);
        if (temp->is_corner()) {
            value = value - weight;
        }
        // Case when corner = (x + 1, y - 1)
        temp->setY(temp->getY() - 1);
        if (temp->is_corner()) {
            value = value - weight;
        }
        // Case when corner = (x + 1, y + 1)
        temp->setY(temp->getY() + 2);
        if (temp->is_corner()) {
            value = value - weight;
        }
        // Case when corner = (x, y + 1)
        temp->setX(temp->getX() - 1);
        if (temp->is_corner()) {
            value = value - weight;
        }
        // Case when corner = (x - 1, y + 1)
        temp->setX(temp->getX() - 1);
        if (temp->is_corner()) {
            value = value - weight;
        }
        // Case when corner = (x - 1, y)
        temp->setY(temp->getY() - 1);
        if (temp->is_corner()) {
            value = value - weight;
        }
        // Case when corner = (x - 1, y - 1)
        temp->setY(temp->getY() - 1);
        if (temp->is_corner()) {
            value = value - weight;
        }
        // Case when corner = (x, y - 1)
        temp->setX(temp->getX() + 1);
        if (temp->is_corner()) {
            value = value - weight;
        }
         
        heuristic_values.push_back(value);
        delete temp;
        delete temp_board;
    }
    
    return heuristic_values;
}


vector<int> Player::minmax(vector<Move*> validmoves) {
    cerr << "[Inside Player minmax]\n";

    vector<int> heuristic_values = simple_heuristic(&board, validmoves, my_side);
    
    for (unsigned int i = 0; i < validmoves.size(); i++) {
        Board *temp_board = board.copy();
        temp_board->doMove(validmoves[i], my_side);
        vector<Move*> temp_validmoves =  temp_board->validMoves(opponent_side);
        if (!temp_validmoves.empty()) {
            vector<int> temp_heuristic = simple_heuristic(temp_board, temp_validmoves, opponent_side);
            int max_i = max_index(temp_heuristic);
            heuristic_values[i] = temp_heuristic[max_i];
        }
        
        // Clean up memory
        for (unsigned int j = 0; j < temp_validmoves.size(); j++) {
            delete temp_validmoves[j];
        }
        delete temp_board;
    }

    return heuristic_values;
}

void Player::set_board(Board new_board) {
    board = new_board;
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be NULL.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return NULL.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /* 
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */ 
    cerr << "[Inside Player::doMove]\n";
    vector<Move*> validmoves;
    
    board.doMove(opponentsMove, opponent_side);
    
    validmoves = board.validMoves(my_side);
        
    // Does a random move using validmoves
//    if (!validmoves.empty()) {
//        board.doMove(validmoves[0], my_side);
//        Move *newmove = new Move(validmoves[0]->getX(), validmoves[0]->getY());
//        
//        // Deallocates validmoves
//        for(unsigned int i = 0; i < validmoves.size(); i++) {
//            delete validmoves[i];
//        }
//        return newmove;
//    }
        
    // Does a move with the highest heuristic value
//    if (!validmoves.empty()) {
//        vector<int> heuristic_values = simple_heuristic(&board, validmoves, my_side);
//        int index = max_index(heuristic_values);
//        
//        Move *newmove = new Move(validmoves[index]->getX(), validmoves[index]->getY());
//        
//        for (unsigned int i = 0; i < validmoves.size(); i++) {
//            delete validmoves[i];
//        }
//        board.doMove(newmove, my_side);
//        return newmove;
//    }


    // Does a move with the highest heuristic value using minmax tree
    if (!validmoves.empty()) {
        int index;
        if (validmoves.size() == 1) {
            index = 0;
        }
        else {
            vector<int> heuristic_values = minmax(validmoves);
            index = max_index(heuristic_values);
        }
        
        Move *newmove = new Move(validmoves[index]->getX(), validmoves[index]->getY());
        
        for (unsigned int i = 0; i < validmoves.size(); i++) {
            delete validmoves[i];
        }
        board.doMove(newmove, my_side);
        return newmove;
    }

    return NULL;
}
