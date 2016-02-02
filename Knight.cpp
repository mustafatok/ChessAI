//
//  Knight.cpp
//  Chess
//
//  Created by mustafa tok on 12.12.2011.
//

#include <iostream>
#include "Component.h"

void Knight::draw(){
    if(this->isBlack())
        cout << "n";
    else
        cout << "N";
}
int Knight::canmove(Point &p1, Point &p2){
    
    int dx = p2.getX() - p1.getX(); 
    int dy = p2.getY() - p1.getY();
    
    if(dx == -1 && dy == -2){}
    else if(dx == -1 && dy == 2){}
    else if(dx == 1 && dy == -2){}
    else if(dx == 1 && dy == 2){}
    else if(dx == -2 && dy == -1){}
    else if(dx == -2 && dy == 1){}
    else if(dx == 2 && dy == -1){}
    else if(dx == 2 && dy == 1){}
    else{ 
        return CANTMOVE;
    }
    
    Component* source = this;
    Component* target;
    
    target = parent->getComponent(p2.getX(), p2.getY());
    
    if(target != NULL){
        if(target->isSameColor(source)){
            return CANTMOVE;
        }else{
            return ENEMYMOVE;
        }
    }else{
        return EMPTYMOVE;
    }
    
    return CANTMOVE;
}
BoardQueue* Knight::successor(Point &p){
    BoardQueue *q = new BoardQueue();
    
    int x = p.getX();
    int y = p.getY();
    Component* com;
    if(x - 2 >= 0){
        if(y - 1 >= 0){
            com = parent->getComponent(x-2, y-1);
            if(!this->isSameColor(com)){
                Point tp(x-2, y-1);
                Board *b = parent->clone();
                b->moveComponent(p, tp);
                q->enqueue(b);
            }
        }
        if(y+1 < SIZE){
            com = parent->getComponent(x-2, y+1);
            if(!this->isSameColor(com)){
                Point tp(x-2, y+1);
                Board *b = parent->clone();
                b->moveComponent(p, tp);
                q->enqueue(b);
            }
        }
    }
    if(x - 1 >= 0){
        if(y - 2 >= 0){
            
            com = parent->getComponent(x-1, y-2);
            if(!this->isSameColor(com)){
                Point tp(x-1, y-2);
                Board *b = parent->clone();
                b->moveComponent(p, tp);
                q->enqueue(b);
            }
        }
        if(y+2 < SIZE){
            
            com = parent->getComponent(x-1, y+2);
            if(!this->isSameColor(com)){
                Point tp(x-1, y+2);
                Board *b = parent->clone();
                b->moveComponent(p, tp);
                q->enqueue(b);
            }
        }
    }
    if(x + 1 < SIZE){
        if(y - 2 >= 0){
            
            com = parent->getComponent(x+1, y-2);
            if(!this->isSameColor(com)){
                Point tp(x+1, y-2);
                Board *b = parent->clone();
                b->moveComponent(p, tp);
                q->enqueue(b);
            }
        }
        if(y+2 < SIZE){
            
            com = parent->getComponent(x+1, y+2);
            if(!this->isSameColor(com)){
                Point tp(x+1, y+2);
                Board *b = parent->clone();
                b->moveComponent(p, tp);
                q->enqueue(b);
            }
        }
    }
    if(x + 2 < SIZE){
        if(y - 1 >= 0){
            
            com = parent->getComponent(x+2, y-1);
            if(!this->isSameColor(com)){
                Point tp(x+2, y-1);
                Board *b = parent->clone();
                b->moveComponent(p, tp);
                q->enqueue(b);
            }}
        if(y+1 < SIZE){
            
            com = parent->getComponent(x+2, y+1);
            if(!this->isSameColor(com)){
                Point tp(x+2, y+1);
                Board *b = parent->clone();
                b->moveComponent(p, tp);
                q->enqueue(b);
            }
        }
    }
    return q;
}
Component* Knight::clone(Board* parent){
    Knight *newClone = new Knight(parent, color);
    if(this->isTouched()){
        newClone->setTouched();
    }
    return newClone;
}
