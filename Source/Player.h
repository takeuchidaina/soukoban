
#ifndef INCLUDE_PLAYER
#define INCLUDE_PLAYER

extern int Player_Init();
extern int Player_Dpct();
extern int Player_Draw();
extern int Player_End();

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
	E_Drct_Left,    //��

	E_Drct_None
} E_Drct;  //Drct = Direction(����)

#endif