// �}�b�v�\����{
#include "DxLib.h"
#include "MAP.h"
#include "Box.h"
#include "Player.h"


FILE *fp;
static int i, j = 0;
char buf[256];
int map[10][10];
int px, py;
int Boxcnt;
S_Box Box;


// �}�b�v�f�[�^
int MapData[MAP_HEIGHT][MAP_WIDTH] =

{ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 1, 0, 1, 1, 1, 1, 1, 1, 0 },
{ 0, 1, 0, 1, 1, 0, 0, 0, 1, 0 },
{ 0, 1, 1, 1, 1, 0, 0, 0, 1, 0 },
{ 0, 1, 0, 1, 0, 0, 0, 0, 1, 0 },
{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };


/*
// �}�b�v�̃f�[�^
void Map_Data(int *Map, int MAP_W, int MAP_H) {

	fp = fopen("test.txt", "r"); 	//�e�L�X�g�t�@�C�����J��

}
*/

int Map_Data(int x, int y) {
	return MapData[y][x];
}

//�v���C���[�̏���x���W���󂯎��
int Map_Player_Pos_Init_x() {

	return px;

}

//�v���C���[�̏���y���W���󂯎��
int Map_Player_Pos_Init_y() {

	return py;

}

//Box�̌����󂯎��
int Map_Box_Count_Init() {

	return Boxcnt;

}

	int MAP_Init() {

		//�����ŏ�����������
		px = 1;
	    py = 1;

		Boxcnt = 1;
		return 0;
	}

	int MAP_Dpct() {
		//�����Ōv�Z
		//Dqct�͖��t���[���Ă΂��

		return 0;
	}

	int MAP_Draw() {
		//�����ŕ`��
		//�����������t���[���Ă΂�܂����v�Z�Ƃ͕ʂɏ����܂�

		// �}�b�v��`��
		for (i = 0; i < MAP_HEIGHT; i++)
		{
			for (j = 0; j < MAP_WIDTH; j++)
			{
				if (MapData[i][j] == 1)
				{
					DrawBox(j * MAP_SIZE, i * MAP_SIZE,
						j * MAP_SIZE + MAP_SIZE, i * MAP_SIZE + MAP_SIZE,
						GetColor(255, 255, 255), TRUE);
				}
			}
		}

		return 0;
	}

	int MAP_End() {
		//����
		return 0;
	}