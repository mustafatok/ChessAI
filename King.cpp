//
//  King.cpp
//  Chess
//
//  Created by mustafa tok on 12.12.2011.
//

#include <iostream>
#include "Component.h"
void King::draw(){
    if(this->isBlack())
        cout << "k";
    else
        cout << "K";
}
int King::canmove(Point &p1, Point &p2){
    
    int dx = p2.getX() - p1.getX(); 
    int dy = p2.getY() - p1.getY();
    if(p2.getX() < 0 || p2.getY() < 0 || p2.getX() >= SIZE || p2.getY() >= SIZE ){
        return CANTMOVE;
    }
    if(dx != 1 && dx != -1 && dy != 1 && dy != -1){
        return CANTMOVE;
    }
    
    Component* source = this;
    Component* target;
    
    target = parent->getComponent(p2.getX(), p2.getY());
    
    if(target != NULL){
        if(!target->isSameColor(source)){
            return ENEMYMOVE;
        }else{
            return CANTMOVE;
        }
    }else{
        return EMPTYMOVE;
    }
    
    return CANTMOVE;
    
}
/*
 inline bool inDanger(){
 return false;
 }*/
BoardQueue* King::successor(Point &p){
    
    BoardQueue *q = new BoardQueue();
    
    Point* np[8];
    np[0] = new Point(p.getX()-1,p.getY()-1);
    np[1] = new Point(p.getX()-1,p.getY());
    np[2] = new Point(p.getX()-1,p.getY()+1);
    np[3] = new Point(p.getX(),p.getY()-1);
    np[4] = new Point(p.getX(),p.getY()+1);
    np[5] = new Point(p.getX()+1,p.getY()-1);
    np[6] = new Point(p.getX()+1,p.getY());
    np[7] = new Point(p.getX()+1,p.getY()+1);
    
    for(int i = 0; i < 8; i++){
        if(this->canmove(p, *(np[i]))!=CANTMOVE){
            Board *b = parent->clone();
            b->moveComponent(p, *(np[i]));
            q->enqueue(b);
        }
        delete np[i];
    }
    return q;
}
Component* King::clone(Board* parent){
    King *newClone = new King(parent, color);
    if(this->isTouched()){
        newClone->setTouched();
    }
    return newClone;
}