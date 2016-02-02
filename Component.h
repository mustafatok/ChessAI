//
//  Component.h
//  Chess
//
//  Created by mustafa tok on 29.11.2011.
//


#ifndef Chess_Component_h
#define Chess_Component_h

#include "Board.h"
class Point{
public:
    void setX(int x){
        this->x = x;
    }
    void setY(int y){
        this->y = y;
    }
    int getX(){
        return this->x;
    }
    int getY(){
        return this->y;
    }
    void setPoint(int x, int y){
        this->x = x;
        this->y = y;
    }
    Point(int x, int y){
        this->x = x;
        this->y = y;
    }
    Point(){
        
    }
private:
    int x;
    int y;
};

class Component {
public:
    virtual void draw() = 0;
    virtual int canmove(Point &p1, Point &p2) = 0;
    virtual BoardQueue* successor(Point& p) = 0;
    
    Component(Board* board, int color);
    bool isWhite();
    bool isBlack();
    bool isSameColor(Component* x);
    bool isTouched();
    void setTouched();
    int getValue();
    virtual Component* clone(Board* parent) = 0;
protected:
    int value;
    int color;
    bool touched;
    Board *parent;    
};

class Pawn : public Component{
public:
    Pawn(Board* board, int color):Component(board, color){
        this->value = 1;
    }
    void draw();
    int canmove(Point &p1, Point &p2);
    BoardQueue* successor(Point &p);
    Component* clone(Board* parent);
private:
    
};
class Rook : public Component{
public:
    Rook(Board* board, int color):Component(board, color){
        this->value = 5;
    }
    void draw();
    int canmove(Point &p1, Point &p2);
    BoardQueue* successor(Point &p);
    Component* clone(Board* parent);

private:
    
};
class Knight : public Component{
public:
    Knight(Board* board, int color):Component(board, color){
        this->value = 3;
    }
    void draw();
    int canmove(Point &p1, Point &p2);
    BoardQueue* successor(Point &p);
    Component* clone(Board* parent);

private:
    
};
class Bishop : public Component{
public:
    Bishop(Board* board, int color):Component(board, color){
        this->value = 3;
    }
    void draw();
    int canmove(Point &p1, Point &p2);
    BoardQueue* successor(Point &p);
    Component* clone(Board* parent);

private:
    
};
class Queen : public Component{
public:
    Queen(Board* board, int color):Component(board, color){
        this->value = 9;
    }
    void draw();
    int canmove(Point &p1, Point &p2);
    BoardQueue* successor(Point &p);
    Component* clone(Board* parent);

private:
    
};
class King : public Component{
public:
    King(Board* board, int color):Component(board, color){
        this->value = INFINITY;
    }
    void draw();
    int canmove(Point &p1, Point &p2);
    BoardQueue* successor(Point &p);
    Component* clone(Board* parent);

private:

};
#endif
