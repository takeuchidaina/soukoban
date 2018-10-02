#pragma once

typedef struct {	//構造体

	int x;  //x座標
	int y;  //y座標

} S_Box;

extern int Box_Init();
extern int Box_Dpct();
extern int Box_Draw();
extern int Box_End(); 

extern int Box_Bectl();
extern int Box_Pos();
extern int Box_Move();

extern int Box_Dbug();