
#ifndef INCLUDE_PLAYER
#define INCLUDE_PLAYER

extern int Player_Init();
extern int Player_Dpct();
extern int Player_Draw();
extern int Player_End();
extern int Player_Move_Flg();
extern int Player_Push_Box(int *,int *,int);

extern int Player_Move_Check();
extern int Player_Move();


typedef struct {

	int x;  //�v���C���[��x���W
	int y;  //�v���C���[��y���W
	int nx;  //���̃v���C���[x���W
	int ny;  //���̃v���C���[y���W

}S_Player;

typedef enum {

	E_Drct_Up,     //��
	E_Drct_Right,  //�E
	E_Drct_Down,   //��
	E_Drct_Left,   //��

	E_Drct_None
} E_Drct;  //Drct = Direction(����)

extern int Player_Back_Move(E_Drct);

#endif