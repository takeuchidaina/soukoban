#ifndef INCLUDED_MAP
#define INCLUDED_MAP


#define MAP_SIZE	64			// �}�b�v�`�b�v��̃h�b�g�T�C�Y
#define MAP_WIDTH	10			// �}�b�v�̕�
#define MAP_HEIGHT	8			// �}�b�v�̏c����

#define MAP_MAX 3

extern int MAP_Init();
extern int MAP_Dpct();
extern int MAP_Draw();
extern int MAP_End();

int MAP_Data(int, int);   //�}�b�v�̔z��  Map_data[][]

int MAP_Player_Pos_Init_x();   //�v���C���[�̏���x���W
int MAP_Player_Pos_Init_y();   //�v���C���[�̏���y���W
int MAP_Box_Count_Init();      //Box�̌�
int MAP_Box_Pos_Init_x(int);      //Box�̏���X���W
int MAP_Box_Pos_Init_y(int);	   //Box�̏���Y���W

int MAP_GetHandleflag();
void MAP_SetHandleflag(int);

#endif
