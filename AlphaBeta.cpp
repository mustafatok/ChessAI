//
//  AlphaBeta.cpp
//  Chess
//
//  Created by mustafa tok on 10.12.2011.
//

#include <iostream>
#include "AlphaBeta.h"

#include "Board.h"
bool CutOffTest1(Board* state, int level, clock_t st){
    clock_t ft = clock();
    float diff = ((float)ft - (float)st) / 1000000.0F;

    if(state->getLevel()==level || state->isFinished() || diff > 99.9){
        return true;
    }
    return false;
}
int Max1(int x,int y){
    return (x > y)? x : y;
}
int Min1(int x, int y){
    return (x < y)? x : y;
}
int changeTurn1(int turn){
    if(turn == BLACK)
        return WHITE;
    else
        return BLACK;
}
inline int MaxValuePruning(Board* state, int turn, int alpha, int beta, int level, clock_t st){
    if(CutOffTest1(state, level, st)){
        return state->getValue();
    }
    
    BoardQueue *q;
    q = state->successor(turn);
    
    while(!q->isEmpty()){
        Board* s = q->dequeue();
        alpha = Max1(alpha, MinValuePruning(s,changeTurn1(turn), alpha, beta, level, st));
        delete s;
        if(alpha >= beta){
            while(!q->isEmpty()){
                Board* s = q->dequeue();
                delete s;
            }
            delete q;
            return beta;
        }
    }
    delete q;
    return alpha;
}
inline int MinValuePruning(Board* state, int turn, int alpha, int beta, int level, clock_t st){
    if(CutOffTest1(state, level, st)){        
        return state->getValue();
    }
    
    BoardQueue *q;
    q = state->successor(turn);
    //    cout << endl;
    while(!q->isEmpty()){
        Board* s = q->dequeue();
        beta = Min1(beta, MaxValuePruning(s,changeTurn1(turn), alpha, beta, level, st));
        delete s;
        if(beta <= alpha){
            while(!q->isEmpty()){
                Board* s = q->dequeue();
                delete s;
            }
            delete q;
            return alpha;
        }
        //        cout << "Minimum : " << beta;
        //        s->draw();
    }

    delete q;
    return beta;
}

Board* PruningDecision(Board* board, int turn, int level, clock_t st){
    if(board->isFinished())
        return board;
    BoardQueue *q;
    q = board->successor(turn);
    cout << endl;
    
    Board* tmpboard = board;
    int tmpvalue = -99999;
    int min;
    
    while(!q->isEmpty()){
        Board* b = q->dequeue();
        min = MinValuePruning(b, changeTurn1(turn), -99999, +99999, level,  st);
        if(min > tmpvalue){
            
            tmpvalue = min;
            if(tmpboard != board){
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
    
    delete q;
    return tmpboard;
}
Board* PruningDecisionW(Board* board, int turn, int level, clock_t st){
    if(board->isFinished())
        return board;
    BoardQueue *q;
    q = board->successor(turn);
    cout << endl;
    
    Board* tmpboard = board;
    int tmpvalue = +99999;
    int max;
    
    while(!q->isEmpty()){
        Board* b = q->dequeue();
        max = MaxValuePruning(b, changeTurn1(turn), -99999, +99999, level, st);
        if(max < tmpvalue){
            tmpvalue = max;
            if(tmpboard != board){
                Board* tmmp = tmpboard;
                tmpboard = b;
                delete tmmp; 
            }else{
                tmpboard = b;
            }

        }else{
            delete b;/////// Burayı control et
        }
    }
    delete q;
    tmpboard->resetLevel();
    cout << "Min : " << tmpvalue << endl;
    return tmpboard;
}