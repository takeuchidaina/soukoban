#ifndef INCLUDE_BOX
#define INCLUDE_BOX
#include "Player.h"

typedef struct {	//構造体

	int x;  //boxのx座標
	int y;  //boxのy座標
	int bx;  //boxの仮のx座標
	int by;  //boxの仮のy座標
} S_Box;

extern int Box_Init();
extern int Box_Dpct();
extern int Box_Draw();
extern int Box_End(); 

extern int Box_Bectl(int*,int*,int);
extern int Box_Pos(int*, int* , int);
extern int Box_Move(E_Drct , int);
extern bool Box_Clear();
extern int Box_Back_Move(E_Drct , int);
extern int Box_Dbug();		//ボックスがヌルヌル動くかのチェックをする関数

#endif