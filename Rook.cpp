//
//  Rook.cpp
//  Chess
//
//  Created by mustafa tok on 12.12.2011.
//

#include <iostream>
#include "Component.h"
void Rook::draw(){
    if(this->isBlack())
        cout << "r";
    else
        cout << "R";
}

int Rook::canmove(Point &p1, Point &p2){
    
    int dx = p2.getX() - p1.getX(); 
    int dy = p2.getY() - p1.getY();
    
    if(dx != 0 && dy != 0){
        return CANTMOVE;
    }
    
    Component* source = this;
    Component* target;
    
    target = parent->getComponent(p2.getX(), p2.getY());
    
    AbstractIterator *iterator;
    
    int x = p1.getX();
    int y = p1.getY();
    
    if(dy == 0 && dx > 0){
        iterator = parent->CreateColumnDownwardIterator(x,y);
    }else if(dy == 0 && dx < 0){
        iterator = parent->CreateColumnUpwardIterator(x,y);
    }else if(dx == 0 && dy > 0){
        iterator = parent->CreateRowForwardIterator(x,y);
    }else if(dx == 0 && dy < 0){
        iterator = parent->CreateRowBackwardIterator(x,y);
    }
    else{ 
        return CANTMOVE;
    }
    
    for(iterator->First(); !iterator->isDone(); iterator->Next()){
        if(p2.getX() == iterator->CurrentPoint().getX() &&  p2.getY() == iterator->CurrentPoint().getY()){
            if(iterator->CurrentItem() == NULL){
                delete iterator;///////check
                return EMPTYMOVE; 
            }else if(!iterator->CurrentItem()->isSameColor(source)){
                delete iterator;///////check
                return ENEMYMOVE;
            }
            break;
        }
        if(iterator->CurrentItem() != NULL){
            delete iterator;///////check
            return CANTMOVE; 
        } 
    }
    delete iterator;///////check
    return CANTMOVE;
}

BoardQueue* Rook::successor(Point &p){
    BoardQueue *q = new BoardQueue();
    AbstractIterator *it[4] ;
    for(int i = 0; i < 4; i++){
        if(i == 0) it[0] = parent->CreateRowForwardIterator(p.getX(), p.getY());
        else if(i == 1) it[1] = parent->CreateRowBackwardIterator(p.getX(), p.getY());
        else if(i == 2) it[2] = parent->CreateColumnDownwardIterator(p.getX(), p.getY());
        else if(i == 3) it[3] = parent->CreateColumnUpwardIterator(p.getX(), p.getY());
        
        for(it[i]->First(); !it[i]->isDone(); it[i]->Next()){
            if(it[i]->CurrentItem() == NULL){
                Point tp = it[i]->CurrentPoint();
                Board *b = parent->clone();
                b->moveComponent(p, tp);
                q->enqueue(b);
            }else if(!this->isSameColor(it[i]->CurrentItem())){
                Point tp = it[i]->CurrentPoint();
                Board *b = parent->clone();
                b->moveComponent(p, tp);
                q->enqueue(b);
                break;
            }else{
                break;
            }
        }
        delete it[i];//////////check
        it[i] = NULL;/////////
    }
    return q;
}
Component* Rook::clone(Board* parent){
    Rook *newClone = new Rook(parent, color);
    if(this->isTouched()){
        newClone->setTouched();
    }
    return newClone;
}