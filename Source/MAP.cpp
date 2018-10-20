// �}�b�v�\����{
#include "DxLib.h"
#include "MAP.h"
#include "Box.h"
#include "Player.h"

int FileHandle, y;
static int i = 0, j = 0;
char buf[256];
char c1, c2;				//MAP��Player,Box�Ɏg��char
int MAP[MAP_HEIGHT][MAP_WIDTH];  //�}�b�v
int px, py;					//�󂯎��v���C���[�̕ϐ�
int Box_Count;				//�󂯎��Box�̕ϐ�;
static int Box_Pos_x[5];		//�󂯎��Box��x���W�ϐ�
static int Box_Pos_y[5];		//�󂯎��Box��y���W�ϐ�
int lflag;

int ImageWall = 0;
int ImageLoad = 0;
int ImageGoal = 0;

char MAPHandle[256];
int Handleflag = 1;


//5��define��const�Œ�`���ׂ�
//�ނ���\���̂����ʂ��ׂ�


//�v���C���[�̏���x���W���󂯎��
int MAP_Player_Pos_Init_x(){

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

//Box�̏���X���W
int MAP_Box_Pos_Init_x(int num) {

	return Box_Pos_x[num];
}

//Box�̏���Y���W
int MAP_Box_Pos_Init_y(int num) {

	return Box_Pos_y[num];
}

//������
int MAP_Init() {
	memset(MAP, -1, sizeof(MAP));
	px = px;			//�󂯎�����v���C���[��x���W��������
	py = py;			//�󂯎�����v���C���[��y���W��������
	Box_Count = 1;	//�󂯎����Box�̐��̏�����
//	Box_Pos_x = 5;	//�󂯎����Box��x���W�̏�����
//	Box_Pos_y = 5;	//�󂯎����Box��y���W�̏�����

	//�摜�̓ǂݍ���
	ImageWall = LoadGraph("Images/Wall.png");
	ImageLoad = LoadGraph("Images/Load.png");
	ImageGoal = LoadGraph("Images/Goal.png");

	strcpy(MAPHandle, "MAP/MAP_0");
	

	char Handletmp[256];
	char flagtmp[64];	//�ˊ� ���v�P�O�i�X�j�}�b�v�܂�
	flagtmp[0] = Handleflag + '0';
	flagtmp[1] = NULL;

	strcpy(Handletmp, MAPHandle);

	strcat(Handletmp, flagtmp);

	strcat(Handletmp, ".csv");

	// MAP�̓ǂݍ���
	FileHandle = FileRead_open( Handletmp );	// ��s�ǂݍ���
													// �t�@�C���̏I�[������܂ŕ\������
	if (FileHandle == -1) {

		DrawFormatString(100, 220, GetColor(255, 0, 0), "erararara");
		WaitKey();
	}

	while (FileRead_eof(FileHandle) == 0) {			// ��s�ǂݍ���

		//c1 = MAP��char
		c1 = FileRead_getc(FileHandle);		//1�����ǂݍ���
		if ('0' <= c1 && c1 <= '9') {		//����0�`9��������
			MAP[i][j] = c1 - '0';				//MAP�ɑ��
		}
		else if (c1 == ',') {				//����","��ǂݍ��񂾂�
			j++;							//�E�̐�����ǂݍ���
		}
		else if (c1 == '\n') {					//����"\n"��ǂݍ��񂾂�
			j = 0;							//�E�ɍs���̂���߂�
			i++;							//���̍s�ɍs��
		}
	}

	// �t�@�C�������
	FileRead_close(FileHandle);

	strcpy(Handletmp, MAPHandle);

	strcat(Handletmp, flagtmp);

	strcat(Handletmp, ".txt");


	
	// Player�̍��W�ǂݍ���
	FileHandle = FileRead_open( Handletmp );	//1�s�ǂݍ���
													// �t�@�C���̏I�[������܂ŕ\������
	if (FileHandle == -1) {

		DrawFormatString(100, 220, GetColor(255, 0, 0), "�G���[");
		WaitKey();
	}

	//c2 = Player��Box��char
	
	c2 = FileRead_getc(FileHandle);		//1�����ǂݍ���	
	px = c2 - '0';				    //Player��X���W�ɑ��
	
	FileRead_getc(FileHandle);

	c2 = FileRead_getc(FileHandle);						//�E�̐�����ǂݍ���
	py = c2 - '0';

	FileRead_getc(FileHandle);

	
	Box_Count = 0;

	
	while (1) {
		FileRead_getc(FileHandle);
		if (c2 == EOF)break;
		c2 = FileRead_getc(FileHandle);
		if (c2 == EOF)break;
		Box_Pos_x[Box_Count] = c2 - '0';;
		
		FileRead_getc(FileHandle);
		if (c2 == EOF)break;
		c2 = FileRead_getc(FileHandle);
		if (c2 == EOF)break;
		Box_Pos_y[Box_Count] = c2 - '0';;
		FileRead_getc(FileHandle);
		if (c2 == EOF)break;
		Box_Count++;
	}
	
	
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
			if (MAP[i][j] == E_Object_Wall)
			{
				//DrawBox(j * MAP_SIZE, i * MAP_SIZE,j * MAP_SIZE + MAP_SIZE, i * MAP_SIZE + MAP_SIZE,GetColor(0, 230, 0), TRUE);

				DrawGraph(j * MAP_SIZE, i * MAP_SIZE, ImageWall, TRUE);

			}
			if (MAP[i][j] == E_Object_Load)
			{
				//DrawBox(j * MAP_SIZE, i * MAP_SIZE,j * MAP_SIZE + MAP_SIZE, i * MAP_SIZE + MAP_SIZE,GetColor(122, 255, 122), TRUE);
			
				DrawGraph(j * MAP_SIZE, i * MAP_SIZE, ImageLoad, TRUE);
				
			}
			if (MAP[i][j] == E_Object_Goal)
			{
				//DrawBox(j * MAP_SIZE, i * MAP_SIZE,j * MAP_SIZE + MAP_SIZE, i * MAP_SIZE + MAP_SIZE,GetColor(122, 122, 255), TRUE);

				DrawGraph(j * MAP_SIZE, i * MAP_SIZE, ImageGoal, TRUE);
			}
		}
	}
	//DrawFormatString(100, 200, GetColor(255, 0, 0), "MAP Draw�����Ă���");
	return 0;
}


void MAP_SetHandleflag(int num) {
	Handleflag = num;
}

int MAP_GetHandleflag() {
	return Handleflag;
}

//�I��
int MAP_End() {
	return 0;
}