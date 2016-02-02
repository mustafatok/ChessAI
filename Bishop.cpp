//
//  Bishop.cpp
//  Chess
//
//  Created by mustafa tok on 12.12.2011.
//

#include <iostream>
#include "Component.h"


void Bishop::draw(){
    if(this->isBlack())
        cout << "b";
    else
        cout << "B";}
int Bishop::canmove(Point &p1, Point &p2){
    
    int dx = p2.getX() - p1.getX(); 
    int dy = p2.getY() - p1.getY();
    if(dx != dy && dx != -dy){ 
        return CANTMOVE;
    }
    
    
    Component* source = this;
    Component* target;
    
    target = parent->getComponent(p2.getX(), p2.getY());
    
    AbstractIterator *iterator;
    
    int x = p1.getX();
    int y = p1.getY();
    
    if(dx < 0 && dy > 0){
        iterator = parent->CreateCrossRightUpwardIterator(x, y);
    }else if(dx > 0 && dy > 0){
        iterator = parent->CreateCrossRightDownwardIterator(x, y);
    }else if(dx < 0 && dy < 0){
        iterator = parent->CreateCrossLeftUpwardIterator(x, y);
    }else if(dx > 0 && dy < 0){
        iterator = parent->CreateCrossLeftDownwardIterator(x, y);
    }else{ 
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

BoardQueue* Bishop::successor(Point &p){
    BoardQueue *q = new BoardQueue();
    AbstractIterator *it[4] ;
    
    it[0] = parent->CreateCrossLeftDownwardIterator(p.getX(), p.getY());
    it[1] = parent->CreateCrossRightDownwardIterator(p.getX(), p.getY());
    it[2] = parent->CreateCrossLeftUpwardIterator(p.getX(), p.getY());
    it[3] = parent->CreateCrossRightUpwardIterator(p.getX(), p.getY());
    
    for(int i = 0; i < 4; i++){
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
Component* Bishop::clone(Board* parent){
    Bishop *newClone = new Bishop(parent, color);
    if(this->isTouched()){
        newClone->setTouched();
    }
    return newClone;
}
