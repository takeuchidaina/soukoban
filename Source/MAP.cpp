// �}�b�v�\����{
#include "DxLib.h"
#include "MAP.h"
#include "Box.h"
#include "Player.h"
#define file_name "MAP_01.csv"
#define full_path file_path file_name


int FileHandle, y;
static int i = 0, j = 0;
char buf[256];
char c;
int MAP[MAP_HEIGHT][MAP_WIDTH];  //�}�b�v
int px, py;			//�󂯎��v���C���[�̕ϐ�
int Box_Count;		//�󂯎��Box�̕ϐ�;
static int Box_Pos_x;		//�󂯎��Box��x���W�ϐ�
static int Box_Pos_y;		//�󂯎��Box��y���W�ϐ�
int lflag;



//�v���C���[�̏���x���W���󂯎��
int MAP_Player_Pos_Init_x() {

	return px;		//�����������v���C���[��x���W��߂�

}


//�v���C���[�̏���y���W���󂯎��
int MAP_Player_Pos_Init_y() {

	return py;		//�����������v���C���[��y���W��߂�

}

//MAP�̍��W
int MAP_Data(int x, int y) {

	return MAP[y][x];
}


//Box�̌����󂯎��
int MAP_Box_Count_Init() {

	return Box_Count;

}

//Box�̏������W
int MAP_Box_Pos_Init_x(int num) {	

	return Box_Pos_x;

}

int MAP_Box_Pos_Init_y(int num) {

	return Box_Pos_y;

}

//������
int MAP_Init() {
	memset(MAP, -1, sizeof(MAP));
	px = 1;			//�󂯎�����v���C���[��x���W��������
	py = 1;			//�󂯎�����v���C���[��y���W��������
	Box_Count = 1;	//�󂯎����Box�̐��̏�����
	Box_Pos_x = 5;	//�󂯎����Box��x���W�̏�����
	Box_Pos_y = 5;	//�󂯎����Box��y���W�̏�����

					// MAP.csv ���J��
	FileHandle = FileRead_open("MAP/MAP_01.csv");	// ��s�ǂݍ���

												// �t�@�C���̏I�[������܂ŕ\������

	if (FileHandle == -1)
	{
		DrawFormatString(100, 220, GetColor(255, 0, 0), "erararara");
		WaitKey();
	}
	while (FileRead_eof(FileHandle) == 0)
	{
		// ��s�ǂݍ���
		//FileRead_gets(String, 256, FileHandle);


		c = FileRead_getc(FileHandle);		//1�����ǂݍ���
		if ('0' <= c && c <= '9') {		//����0�`9��������
			MAP[i][j] = c - '0';				//MAP�ɑ��
		}
		else if (c == ',') {				//����","��ǂݍ��񂾂�
			j++;							//�E�̐�����ǂݍ���
		}
		else if (c == '\n') {					//����"\n"��ǂݍ��񂾂�
			j = 0;							//�E�ɍs���̂���߂�
			i++;							//���̍s�ɍs��
		}
	}

	/*
		for (i = 0; i < MAP_HEIGHT; i++) {			//i��10�ɂȂ�܂ő���
			for (j = 0; j < MAP_WIDTH; j++) {		//j��10�ɂȂ�܂ő���
				if (MAP[i][j] != -1) {		//����MAP��-1�Ɠ������Ȃ�������
					DrawFormatString(j * 10, i * 20, GetColor(255, 255, 255), "%d", MAP[i][j]);
				}	//
			}
			
	}
	*/

	// �t�@�C�������
	FileRead_close(FileHandle);

	return 0;

}


//�v�Z
int MAP_Dpct() {
	//Dpct�͖��t���[���Ă΂��

	return 0;
}


//�`��
int MAP_Draw() {
	//�����������t���[���Ă΂�邪�v�Z�Ƃ͕ʂɏ����܂�

	// �}�b�v��`��
	for (i = 0; i < MAP_HEIGHT; i++)
	{
		for (j = 0; j < MAP_WIDTH; j++)
		{
			if (MAP[i][j] == 0)
			{
				DrawBox(j * MAP_SIZE, i * MAP_SIZE,
					j * MAP_SIZE + MAP_SIZE, i * MAP_SIZE + MAP_SIZE,
					GetColor(0, 230, 0), TRUE);
			}
			if (MAP[i][j] == 1)
			{
				DrawBox(j * MAP_SIZE, i * MAP_SIZE,
					j * MAP_SIZE + MAP_SIZE, i * MAP_SIZE + MAP_SIZE,
					GetColor(122, 255, 122), TRUE);
				
			}
		}
	}
	//DrawFormatString(100, 200, GetColor(255, 0, 0), "MAP Draw�����Ă���");
	return 0;
}


//�I��
int MAP_End() {
	return 0;
}