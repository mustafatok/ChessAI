//
//  MiniMax.cpp
//  Chess
//
//  Created by mustafa tok on 10.12.2011.
//

#include <iostream>
#include "MiniMax.h"
#include "Board.h"

bool CutOffTest(Board* state, clock_t st){
    clock_t ft = clock();
    float diff = ((float)ft - (float)st) / 1000000.0F;

    if(state->getLevel()==4 || state->isFinished() || diff > 99){
        return true;
    }
    return false;
}
int Min(int x, int y);
int changeTurn(int turn);

int Max(int x,int y){
    return (x > y)? x : y;
}
int Min(int x, int y){
    return (x < y)? x : y;
}
int changeTurn(int turn){
    if(turn == BLACK)
        return WHITE;
    else
        return BLACK;
}
int MaxValue(Board* state, int turn, clock_t st){
    int alpha = -99999;
    if(CutOffTest(state, st)){
        return state->getValue();
    }
    
    BoardQueue *q;
    q = state->successor(turn);
    //    cout << endl;
    
    while(!q->isEmpty()){
        Board* s = q->dequeue();
        alpha = Max(alpha, MinValue(s,changeTurn(turn), st));
        delete s;
    }
    delete q;
    return alpha;
}
int MinValue(Board* state, int turn, clock_t st){
    int beta = 99999;
    if(CutOffTest(state, st)){        
        return state->getValue();
    }
    
    BoardQueue *q;
    q = state->successor(turn);
    //    cout << endl;
    while(!q->isEmpty()){
        Board* s = q->dequeue();
        beta = Min(beta, MaxValue(s,changeTurn(turn), st));
        delete s;
    }
    delete q;
    return beta;
}
Board* MinimaxDecision(Board* board, int turn, clock_t st){
    BoardQueue *q;
    q = board->successor(turn);
    cout << endl;
    
    Board* tmpboard = NULL;
    int tmpvalue = -99999;
    int min;
    
    while(!q->isEmpty()){
        Board* b = q->dequeue();
        min = MinValue(b, changeTurn(turn),st);
        if(min > tmpvalue){
            tmpvalue = min;
            if(tmpboard != NULL){
                Board* tmmp = tmpboard;
                tmpboard = b;
                delete tmmp;
            }else{
                tmpboard = b;
            }
        }else{
            delete b;/////// Burayı control et hacıııı
        }
    }
    tmpboard->resetLevel();
    cout << "Min : " << tmpvalue << endl;
    return tmpboard;
}