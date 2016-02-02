//
//  Board.h
//  Chess
//
//  Created by mustafa tok on 29.11.2011.
//

#ifndef Chess_Board_h
#define Chess_Board_h
#include <list>
#include "Header.h"
#include "Component.h"
#include "Iterators.h"
class Board {
public:
    
    RowForwardIterator* CreateRowForwardIterator(int x, int y);
    RowBackwardIterator* CreateRowBackwardIterator(int x, int y);
    ColumnUpwardIterator* CreateColumnUpwardIterator(int x, int y);
    ColumnDownwardIterator* CreateColumnDownwardIterator(int x, int y);
    CrossRightUpwardIterator* CreateCrossRightUpwardIterator(int x, int y);
    CrossLeftUpwardIterator* CreateCrossLeftUpwardIterator(int x, int y);
    CrossRightDownwardIterator* CreateCrossRightDownwardIterator(int x, int y);
    CrossLeftDownwardIterator* CreateCrossLeftDownwardIterator(int x, int y);
        
    Board();
    ~Board();
    void draw();
    bool controlAndMoveComponent(Point &p1, Point &p2);
    void moveComponent(Point &p1, Point &p2);
    void swap(Component* *x, Component* *y);
    Component* getComponent(int x, int y);
    void incrementValue(int byx);
    void decrementValue(int byx);
    bool isFinished();
    Board* clone();
    Board(Board const& object);
    BoardQueue* successor(int TURN);
    int getValue();
    int getLevel();
    void resetLevel();
    void incrementLevel();

private:
    Component** * board;
    void makeFinished();
    bool finished;
    int value;
    int level;
};

class BoardQueue{
public:
    void enqueue(Board* x);
    Board* dequeue();
    void merge(BoardQueue & bq);
    bool isEmpty();
    ~BoardQueue();
private:
    list<Board*> elems;
};

#endif
