#ifndef INCLUDE_BOX
#define INCLUDE_BOX
#include "Player.h"

typedef struct {	//�\����

	int x;  //box��x���W
	int y;  //box��y���W
	int bx;  //box�̉���x���W
	int by;  //box�̉���y���W
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
extern int Box_Dbug();		//�{�b�N�X���k���k���������̃`�F�b�N������֐�

#endif