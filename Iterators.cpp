//
//  Iterators.cpp
//  Chess
//
//  Created by mustafa tok on 03.12.2011.
//

#include <iostream>
#include "Iterators.h"

Point AbstractIterator::CurrentPoint(){
    Point p(x,y);
    return p;
}
Component* AbstractIterator::CurrentItem(){
    return board[x][y];
}