//
//  Pawn.cpp
//  Chess
//
//  Created by mustafa tok on 12.12.2011.
//

#include <iostream>
#include "Component.h"

void Pawn::draw(){
    if(this->isBlack())
        cout << "p";
    else
        cout << "P";
}

int Pawn::canmove(Point &p1, Point &p2){
    
    int dx; 
    int dy; 
    
    if(this->isWhite()){
        dx = p1.getX() - p2.getX();
        dy = p2.getY() - p1.getY();
    }else{
        dx = p2.getX() - p1.getX();
        dy = p1.getY() - p2.getY();
    }
    
    if(p2.getX() < 0 || p2.getY() < 0 || p2.getX() >= SIZE || p2.getY() >= SIZE){
        return CANTMOVE;
    }
    if(dx == 1){
        
    }else if(dx == 2){
        if(this->isTouched())
            return CANTMOVE;
        if(this->isBlack())
            if(parent->getComponent(p2.getX()-1, p2.getY())!=NULL){
                return CANTMOVE;
            }
            else if(this->isWhite())
                if(parent->getComponent(p2.getX()+1, p2.getY())!=NULL){
                    return CANTMOVE;
                }
    }else{
        return CANTMOVE;
    }
    
    Component* source = this;
    Component* target;
    
    target = parent->getComponent(p2.getX(), p2.getY());
    
    if(dy == 0){
        if(target != NULL){
            return CANTMOVE;
        }else{
            return EMPTYMOVE;
        }
    }else if((dy == 1 || dy == -1) && dx == 1){
        if(target != NULL){
            if(target->isSameColor(source)){
                return CANTMOVE;
            }else{
                return ENEMYMOVE;
            }
        }else{
            return CANTMOVE;
        }
    } 
    
    return CANTMOVE;
    
}
BoardQueue* Pawn::successor(Point &p){
    BoardQueue *q = new BoardQueue();
    Point* np[4];
    if(this->isWhite()){
        np[0] = new Point(p.getX()-2,p.getY());
        np[1] = new Point(p.getX()-1,p.getY());
        np[2] = new Point(p.getX()-1,p.getY()-1);
        np[3] = new Point(p.getX()-1,p.getY()+1);
    }else if(this->isBlack()){
        np[0] = new Point(p.getX()+2,p.getY());
        np[1] = new Point(p.getX()+1,p.getY());
        np[2] = new Point(p.getX()+1,p.getY()-1);
        np[3] = new Point(p.getX()+1,p.getY()+1);
    }else{
        return NULL;
    }
    for(int i = 0; i < 4; i++){
        if(this->canmove(p, *(np[i]))!=CANTMOVE){
            Board *b = parent->clone();
            b->moveComponent(p, *(np[i]));
            q->enqueue(b);
        }
        
        delete np[i];//checkkkk
    }
    return q;
}

Component* Pawn::clone(Board* parent){
    Pawn *newPawn = new Pawn(parent, color);
    if(this->isTouched()){
        newPawn->setTouched();
    }
    return newPawn;
}
