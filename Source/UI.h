#pragma once

#ifndef INCLUDE_UI
#define INCLUDE_UI
#include "Player.h"
#endif

//UI�n�֐����g���ׂ̃v���g�^�C�v�錾
extern int UI_Init();
extern int UI_Dpct();
extern int UI_Draw();
extern int UI_End();

//�v���C���[�E���𓮂����Ƃ��ɌĂяo��
extern int UI_Player_Move_History(E_Drct Drct);
extern int UI_Box_Move_History(E_Drct Drct,int num);
extern int UI_StepCount_MoveOn();

//�����J�E���g�̒�
int UI_StepCount();


//����ۑ��p�\����
typedef struct {
	E_Drct Player_Drct;
	E_Drct Box_Drct;
	int Boxnum;
}S_History;
