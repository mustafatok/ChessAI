//
//  Iterators.h
//  Chess
//
//  Created by mustafa tok on 29.11.2011.
//

#ifndef Chess_Iterators_h
#define Chess_Iterators_h
#include "Header.h"
#include "Board.h"
#include "Component.h"

class AbstractIterator{
public:
    virtual void First() = 0;
    virtual void Next() = 0;
    virtual bool isDone() = 0;
    virtual Component* CurrentItem();
    Point CurrentPoint();
protected:
    AbstractIterator(Component* **board, int x, int y){
        this->board = board;
        firstx = x;
        firsty = y;
    }
    Component* **board;
    int x;//Row
    int y;//Column
    int firstx;
    int firsty;
    
};

class RowForwardIterator : public AbstractIterator{
public:
    RowForwardIterator(Component* **board, int x, int y):AbstractIterator(board, x, y){}
    ~RowForwardIterator(){}
    void First(){
        this->x = firstx;
        this->y = firsty + 1;
    }
    void Next(){
        if(!isDone())
            y++;
    }
    bool isDone(){
        return y >= SIZE;
    }
};
class RowBackwardIterator : public AbstractIterator{
public:
    RowBackwardIterator(Component* **board, int x, int y):AbstractIterator(board, x, y){}
    ~RowBackwardIterator(){}
    void First(){
        this->x = firstx;
        this->y = firsty - 1;
    }
    void Next(){
        if(!isDone())
            y--;
    }
    bool isDone(){
        return y < 0;
    }
};
class ColumnDownwardIterator : public AbstractIterator{
public:
    ColumnDownwardIterator(Component* **board, int x, int y):AbstractIterator(board, x, y){}
    ~ColumnDownwardIterator(){}
    void First(){
        this->x = firstx + 1;
        this->y = firsty;
    }
    void Next(){
        if(!isDone())
            x++;
    }
    bool isDone(){
        return x >= SIZE;
    }
};
class ColumnUpwardIterator : public AbstractIterator{
public:
    ColumnUpwardIterator(Component* **board, int x, int y):AbstractIterator(board, x, y){}
    ~ColumnUpwardIterator(){}
    void First(){
        this->x = firstx - 1;
        this->y = firsty;
    }
    void Next(){
        if(!isDone())
            x--;
    }
    bool isDone(){
        return x < 0;
    }
};
class CrossRightUpwardIterator : public AbstractIterator{
public:
    CrossRightUpwardIterator(Component* **board, int x, int y):AbstractIterator(board, x, y){}
    ~CrossRightUpwardIterator(){}
    void First(){
        this->x = firstx - 1;
        this->y = firsty + 1;
    }
    void Next(){
        if(!isDone()){
            x--;
            y++;
        }
    }
    bool isDone(){
        return (x < 0) || (y >= SIZE);
    }
};
class CrossLeftUpwardIterator : public AbstractIterator{
public:
    CrossLeftUpwardIterator(Component* **board, int x, int y):AbstractIterator(board, x, y){}
    ~CrossLeftUpwardIterator(){}
    
    void First(){
        this->x = firstx - 1;
        this->y = firsty - 1;
    }
    void Next(){
        if(!isDone()){
            x--;
            y--;
        }
    }
    bool isDone(){
        return (x < 0) || (y < 0);
    }
};
class CrossLeftDownwardIterator : public AbstractIterator{
public:
    CrossLeftDownwardIterator(Component* **board, int x, int y):AbstractIterator(board, x, y){}
    ~CrossLeftDownwardIterator(){}
    void First(){
        this->x = firstx + 1;
        this->y = firsty - 1;
    }
    void Next(){
        if(!isDone()){
            x++;
            y--;
        }
    }
    bool isDone(){
        return (x >= SIZE) || (y < 0);
    }
};
class CrossRightDownwardIterator : public AbstractIterator{
public:
    CrossRightDownwardIterator(Component* **board, int x, int y):AbstractIterator(board, x, y){}
    ~CrossRightDownwardIterator(){}
    void First(){
        this->x = firstx + 1;
        this->y = firsty + 1;
    }
    void Next(){
        if(!isDone()){
            x++;
            y++;
        }
    }
    bool isDone(){
        return (x >= SIZE) || (y >= SIZE);
    }
};



#endif
