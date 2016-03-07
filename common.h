#ifndef __COMMON_H__
#define __COMMON_H__

enum Side { 
    WHITE, BLACK
};

class Move {
   
public:
    int x, y;
    Move(int x, int y) {
        this->x = x;
        this->y = y;        
    }
    ~Move() {}

    int getX() { return x; }
    int getY() { return y; }

    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
    
    bool is_corner() {
        if ((x == 0) && (y == 0)) { return 1; }
        if ((x == 0) && (y == 7)) { return 1; }
        if ((x == 7) && (y == 0)) { return 1; }
        if ((x == 7) && (y == 7)) { return 1; } 
        return 0;
    }
    
};

#endif
