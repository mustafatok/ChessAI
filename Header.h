//
//  Header.h
//  Chess
//
//  Created by mustafa tok on 03.12.2011.
//

#ifndef Chess_Header_h
#define Chess_Header_h

#define BLACK 0
#define WHITE 1
#define SIZE 8
#define INFINITY 999

#define EMPTYMOVE 1
#define CANTMOVE 0
#define ENEMYMOVE -1

class BoardQueue;
class Board;
class Component;
class AbstractIterator;
class Point;
class RowForwardIterator;
class RowBackwardIterator;
class ColumnUpwardIterator;
class ColumnDownwardIterator;
class CrossForwardIterator;
class CrossBackwardIterator;
class CrossRightUpwardIterator;
class CrossLeftUpwardIterator;
class CrossRightDownwardIterator;
class CrossLeftDownwardIterator;
using namespace std;

#endif
