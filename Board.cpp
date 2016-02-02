//
//  Board.cpp
//  Chess
//
//  Created by mustafa tok on 29.11.2011.
//

#include <iostream>
#include "Board.h"
using namespace std;

RowForwardIterator* Board::CreateRowForwardIterator(int x, int y){
    return new RowForwardIterator(this->board, x, y);
}
RowBackwardIterator* Board::CreateRowBackwardIterator(int x, int y){
    return new RowBackwardIterator(this->board, x, y);
}
ColumnUpwardIterator* Board::CreateColumnUpwardIterator(int x, int y){
    return new ColumnUpwardIterator(this->board, x, y);
}
ColumnDownwardIterator* Board::CreateColumnDownwardIterator(int x, int y){
    return new ColumnDownwardIterator(this->board, x, y);
}
CrossRightUpwardIterator* Board::CreateCrossRightUpwardIterator(int x, int y){
    return new CrossRightUpwardIterator(this->board, x, y);
}
CrossLeftUpwardIterator* Board::CreateCrossLeftUpwardIterator(int x, int y){
    return new CrossLeftUpwardIterator(this->board, x, y);
}
CrossLeftDownwardIterator* Board::CreateCrossLeftDownwardIterator(int x, int y){
    return new CrossLeftDownwardIterator(this->board, x, y);
}
CrossRightDownwardIterator* Board::CreateCrossRightDownwardIterator(int x, int y){
    return new CrossRightDownwardIterator(this->board, x, y);
}
Board::Board(){
    
    // Board Initialize
    board = new Component**[SIZE];
    for(int i = 0; i < SIZE; i++){
        board[i] = new Component*[SIZE];
    }
    
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            board[i][j] = NULL;
        }
    }
    
    for(int i = 0; i < SIZE; i++){
        board[1][i] = new Pawn(this, BLACK);
        board[6][i] = new Pawn(this, WHITE);
    }
    
    board[0][0] = new Rook(this, BLACK);
    board[0][7] = new Rook(this, BLACK);
    board[7][0] = new Rook(this, WHITE);
    board[7][7] = new Rook(this, WHITE);
    
    board[0][1] = new Knight(this, BLACK);
    board[0][6] = new Knight(this, BLACK);
    board[7][1] = new Knight(this, WHITE);
    board[7][6] = new Knight(this, WHITE);
    
    board[0][2] = new Bishop(this, BLACK);
    board[0][5] = new Bishop(this, BLACK);
    board[7][2] = new Bishop(this, WHITE);
    board[7][5] = new Bishop(this, WHITE);
    
    board[0][3] = new Queen(this, BLACK);
    board[7][3] = new Queen(this, WHITE);
    
    board[0][4] = new King(this, BLACK);
    board[7][4] = new King(this, WHITE);
    
    value = 0;
    level = 0;
    finished = false;
}
Board::~Board(){
    
    for(int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            if(board[i][j]!=NULL){
                delete board[i][j];
                board[i][j] = NULL;
            }
            
        }
        delete board[i];
        board[i] = NULL;
    }
    delete board;
    board = NULL;
}
void Board::draw(){
    cout << "Value : " << this->value << endl;
    cout << "   ";
    for(int i = 0; i < SIZE; i++){
        cout << i << ". ";
    }
    cout << endl;
    for(int i = 0; i < SIZE; i++){
        cout << i << ". ";
        for(int j = 0; j < SIZE; j++){
            if(board[i][j] != NULL){
                board[i][j]->draw();
            }else{
                cout << " ";
            }
            cout << "  ";
        } 
        cout << endl;
    }
    cout << endl;
}
bool Board::isFinished(){
    return finished;
}
void Board::makeFinished(){
    finished = true;
}
bool Board::controlAndMoveComponent(Point &p1, Point &p2){
    if(this->isFinished())
        return false;
    Component* source;
    Component* target;
    int _oldx = p1.getX();
    int _oldy = p1.getY();
    int _newx = p2.getX();
    int _newy = p2.getY();
    source = this->getComponent(_oldx,_oldy);
    target = this->getComponent(_newx,_newy);
    if(source == NULL) return false;
    int result = source->canmove(p1, p2);
    if(result == CANTMOVE)
        return false;
    else if(result == ENEMYMOVE){
        //Component *& x = board[_newx][_newy];
        //delete x;
        int compvalue = board[_newx][_newy]->getValue();
        if(compvalue == INFINITY)
            this->makeFinished();
        if(board[_newx][_newy]->isWhite()){
            this->incrementValue(compvalue);
        }else{
            this->decrementValue(compvalue);
        }
        delete board[_newx][_newy];
        board[_newx][_newy] = NULL;
        
    }
    source->setTouched();
    swap(&(board[_oldx][_oldy]), &(board[_newx][_newy]));
    
    return true;
}
void Board::moveComponent(Point &p1, Point &p2){
    if(this->isFinished())
        return;
    Component* source;
    Component* target;
    int _oldx = p1.getX();
    int _oldy = p1.getY();
    int _newx = p2.getX();
    int _newy = p2.getY();
    source = this->getComponent(_oldx,_oldy);
    target = this->getComponent(_newx,_newy);
    if(source == NULL) return;
    
    if(target!=NULL){
        int compvalue = board[_newx][_newy]->getValue();
        if(compvalue == INFINITY)
            this->makeFinished();
        if(board[_newx][_newy]->isWhite()){
            this->incrementValue(compvalue);
        }else{
            this->decrementValue(compvalue);
        }
        delete board[_newx][_newy];
        board[_newx][_newy] = NULL;
        
    }
    source->setTouched();
    swap(&(board[_oldx][_oldy]), &(board[_newx][_newy]));
    
}
Board::Board(Board const& object){
    //Board();
    // Board Initialize
    board = new Component**[SIZE];
    for(int i = 0; i < SIZE; i++){
        board[i] = new Component*[SIZE];
    }
    for(int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            if(object.board[i][j]!=NULL){
                this->board[i][j] = object.board[i][j]->clone(this);
            }else{
                this->board[i][j] = NULL;
            }
            
        }
    }
    value = object.value;
    this->level = object.level;
    this->finished = object.finished;
}
Board* Board::clone(){
    Board *newBoard = new Board(*this);
    newBoard->incrementLevel();
    return newBoard;
}
void Board::incrementValue(int byx){
    this->value += byx;
}
void Board::decrementValue(int byx){
    this->value -= byx;
}
void Board::swap(Component* *x, Component* *y){
    Component* tmp;
    tmp = *x;
    *x = *y;
    *y = tmp;
}
Component* Board::getComponent(int x, int y){
    if(x >= SIZE || y >= SIZE) return NULL;
    if(x < 0 || y < 0) return NULL;
    return board[x][y];
}
int Board::getValue(){
    return this->value;
}
int Board::getLevel(){
    return this->level;
}
void Board::resetLevel(){
    this->level = 0;
}
void Board::incrementLevel(){
    this->level++;
}
BoardQueue* Board::successor(int TURN){
    BoardQueue *q = new BoardQueue();
    AbstractIterator *it;
    for(int i = 0; i < SIZE; i++){
        it = CreateRowForwardIterator(i, -1);
        for(it->First(); !it->isDone(); it->Next()){
            Point p = it->CurrentPoint();
            if(it->CurrentItem()!=NULL){
                if((TURN==BLACK && it->CurrentItem()->isBlack()) || (TURN==WHITE && it->CurrentItem()->isWhite())){
                    BoardQueue* tmp = it->CurrentItem()->successor(p);
                    if(tmp!= NULL)
                        q->merge(*tmp);
                    delete tmp;//checkkkkk
                }
            }
        }
        delete it;
    }
    return q;
}
void BoardQueue::enqueue(Board *x){
    elems.push_back(x);
}
Board* BoardQueue::dequeue(){
    Board* tmp = elems.front();
    elems.pop_front();
    return tmp;
}
void BoardQueue::merge(BoardQueue & bq){
    this->elems.merge(bq.elems);
}
bool BoardQueue::isEmpty(){
    return this->elems.empty();
}
BoardQueue::~BoardQueue(){
    elems.clear();
}
