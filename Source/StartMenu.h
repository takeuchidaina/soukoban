#pragma once

typedef struct {	//�\����
	int x, y;  //���W�̕ϐ�
} MenuElement_t;

//�摜�p�̍\����
typedef struct {
	int Title;
	int Start;
	int On_Start;
	int Stage;
	int On_Stage;
	int End;
	int On_End;
	int BG;
} Image_t;

extern int StartMenu_Init();
extern int StartMenu_Dpct();
extern int StartMenu_Draw();
extern int StartMenu_End();