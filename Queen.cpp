//
//  Queen.cpp
//  Chess
//
//  Created by mustafa tok on 12.12.2011.
//

#include <iostream>
#include "Component.h"


void Queen::draw(){
    if(this->isBlack())
        cout << "q";
    else
        cout << "Q";}
int Queen::canmove(Point &p1, Point &p2){
    
    int dx = p2.getX() - p1.getX(); 
    int dy = p2.getY() - p1.getY();
    if(dx != dy && dx != -dy && dx != 0 && dy != 0){ 
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
    }else if(dy == 0 && dx > 0){
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
        //cout << iterator->CurrentItem() << " x : " <<  iterator->CurrentPoint().getX()<< " y : " << iterator->CurrentPoint().getY()<<endl;
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


BoardQueue* Queen::successor(Point &p){
    BoardQueue *q = new BoardQueue();
    AbstractIterator *it[8] ;
    it[0] = parent->CreateCrossLeftDownwardIterator(p.getX(), p.getY());
    it[1] = parent->CreateCrossRightDownwardIterator(p.getX(), p.getY());
    it[2] = parent->CreateCrossLeftUpwardIterator(p.getX(), p.getY());
    it[3] = parent->CreateCrossRightUpwardIterator(p.getX(), p.getY());
    it[4] = parent->CreateRowForwardIterator(p.getX(), p.getY());
    it[5] = parent->CreateRowBackwardIterator(p.getX(), p.getY());
    it[6] = parent->CreateColumnDownwardIterator(p.getX(), p.getY());
    it[7] = parent->CreateColumnUpwardIterator(p.getX(), p.getY());
    
    for(int i = 0; i < 8; i++){
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
        delete it[i];
        it[i] = NULL;//////////checkkkkkkk
    }

    return q;
}

Component* Queen::clone(Board* parent){
    Queen *newClone = new Queen(parent, color);
    if(this->isTouched()){
        newClone->setTouched();
    }
    return newClone;
}
