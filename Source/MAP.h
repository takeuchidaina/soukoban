#pragma once

#define MAP_SIZE	64			// �}�b�v�`�b�v��̃h�b�g�T�C�Y
#define MAP_WIDTH	10			// �}�b�v�̕�
#define MAP_HEIGHT	8			// �}�b�v�̏c����

extern int MAP_Init();
extern int MAP_Dpct();
extern int MAP_Draw();
extern int MAP_End();

int Map_Data(int, int);   //�}�b�v�̔z��  Map_data[][]

int Map_Player_Pos_Init_x();   //�v���C���[�̏���x���W
int Map_Player_Pos_Init_y();   //�v���C���[�̏���y���W
int Map_Box_Count_Init();     //Box�̌�
//int Map_Box_Pos_Init();     //Box�̏������W
