//
//  Component.cpp
//  Chess
//
//  Created by mustafa tok on 29.11.2011.
//

#include <iostream>
#include "Component.h"
#include "Iterators.h"

using namespace std;

Component::Component(Board* board, int color){
    this->color = color;
    this->parent = board;
    this->touched = false;
}
bool Component::isWhite(){
    return (color == WHITE) ? true : false;
}
bool Component::isBlack(){
    return (color == BLACK) ? true : false;
}
bool Component::isSameColor(Component* x){
    if(x == NULL)
        return false;
    if(this->isBlack() && x->isBlack())
        return true;
    if(this->isWhite() && x->isWhite())
        return true;
    return false;
}
bool Component::isTouched(){
    return this->touched;
}
void Component::setTouched(){
    this->touched = true;
}
int Component::getValue(){
    return value;
}
