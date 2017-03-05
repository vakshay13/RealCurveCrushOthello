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
    Move(){
        this->x = 0;
        this->y = 0;
    }
    ~Move() {}

    int getX() { return x; }
    int getY() { return y; }

    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
};

class scoredMove {
public:
    int score;
    Move move;
    scoredMove(int sc, Move mov){
        score = sc;
        move.x = mov.x;
        move.y = mov.y;
    }
    scoredMove(){
        score = 0;
        move.x = 0;
        move.y = 0;
    }
};

#endif
