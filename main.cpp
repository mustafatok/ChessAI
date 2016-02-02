//
//  main.cpp
//  Chess
//
//  Created by mustafa tok on 26.11.2011.
//

#include <iostream>
#include "Board.h"
#include "Iterators.h"
#include "Component.h"
#include "AlphaBeta.h"
#include "MiniMax.h"


int main (int argc, const char * argv[])
{
    
    int choice,level;
    cout << "1. Minimax Algorithm" << endl;
    cout << "2. Alpha-Beta Pruning" << endl;
    cout << "3. Exit" << endl;
    cin >> choice;
    
    cout << "Enter a level : ";
    cin >> level;
    
    if(choice == 3){
        exit(0);
    }
    Board* chessboard = new Board();
    int turn = WHITE;
    chessboard->draw();
    
    while(1){
        if(chessboard->isFinished()) break;
        int x, y, z, t;
        Point p1,p2;
        cin >> x >> y >> z >> t;
        
        if(x == -1 || y == -1 || z == -1 || t == -1) break;
        
        if(x >=0 && y >= 0 && z >= 0 && t >= 0){
            p1.setX(x);
            p1.setY(y);
            p2.setX(z);
            p2.setY(t);
            if(chessboard->getComponent(x, y)->isWhite() && turn == WHITE){
                if(chessboard->controlAndMoveComponent(p1,p2))
                    turn = BLACK;
            }else if(chessboard->getComponent(x, y)->isBlack() && turn == BLACK){
                if(chessboard->controlAndMoveComponent(p1,p2))
                    turn = WHITE;
            }
        }
        if(turn == BLACK){
            Board* tmp = chessboard;
            clock_t t1,t2;
            chessboard->draw();
            t1 = clock();

            if(choice == 1){
                chessboard = MinimaxDecision(chessboard, BLACK, t1);
            }else if(choice == 2){
                chessboard = PruningDecision(chessboard, BLACK, level, t1);

            }
            
            t2 = clock();
            cout << ((float)t2 - (float)t1) / 1000000.0F << "Seconds" << endl;

            
            /*
            while (!chessboard->isFinished()) {
                chessboard = PruningDecision(chessboard, BLACK, t1);
                chessboard->draw();
                if(chessboard->isFinished()){
                    cout<<"Black Wins"<<endl;
                    break;
                }
                chessboard = PruningDecisionW(chessboard, WHITE , t1);
                chessboard->draw();
                if(chessboard->isFinished())
                    cout<<"White Wins"<<endl;
                 
            }*/
             
            delete tmp;
            turn = WHITE;
        }
        chessboard->draw();
        
        
    }
    return 0;
}

