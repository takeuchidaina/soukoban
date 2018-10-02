#pragma once

typedef struct {	//\‘¢‘Ì

	int x;  //xÀ•W
	int y;  //yÀ•W

} S_Box;

extern int Box_Init();
extern int Box_Dpct();
extern int Box_Draw();
extern int Box_End(); 

extern int Box_Bectl();
extern int Box_Pos();
extern int Box_Move();

extern int Box_Dbug();