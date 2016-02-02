//
//  MiniMax.h
//  Chess
//
//  Created by mustafa tok on 10.12.2011.
//

#ifndef Chess_MiniMax_h
#define Chess_MiniMax_h
#include "Header.h"
#include "Board.h"



int MaxValue(Board* state, int turn, clock_t st);
int MinValue(Board* state, int turn, clock_t st);
Board* MinimaxDecision(Board* board, int turn, clock_t st);

bool CutOffTest(Board* state, clock_t st);
int Max(int x,int y);

#endif
