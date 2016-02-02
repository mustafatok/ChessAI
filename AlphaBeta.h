//
//  AlphaBeta.h
//  Chess
//
//  Created by mustafa tok on 10.12.2011.
//

#ifndef Chess_AlphaBeta_h
#define Chess_AlphaBeta_h
#include "Header.h"

int MaxValuePruning(Board* state, int turn, int alpha, int beta, int level, clock_t st);
int MinValuePruning(Board* state, int turn, int alpha, int beta, int level, clock_t st);
Board* PruningDecision(Board* board, int turn, int level, clock_t st);

Board* PruningDecisionW(Board* board, int turn, int level, clock_t st);

bool CutOffTest1(Board* state, int level, clock_t st);

int Max1(int x,int y);
int Min1(int x, int y);
int changeTurn1(int turn);
#endif
