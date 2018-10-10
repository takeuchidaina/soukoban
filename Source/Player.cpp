#include "DxLib.h"
#include "Player.h"
#include "Keyboard.h"
#include "MAP.h"
#include "Box.h"
#include "UI.h"

typedef enum
{

	E_Object_Wall,      //�s���Ȃ��ꏊ
	E_Object_Load,      //������ꏊ
	E_Object_Goal,      //�S�[��

}E_Object;


/**********************************�@�ϐ��錾�@******************************************/
//����
E_Drct Drct;   //�����̊Ǘ�
int i;         //for���p


//Player
S_Player Player;     //Player�̍\����(�w�b�_�[�t�@�C���ɂč쐬)
int None_Num;        //�摜�̃X�^���o�C���(�Î~���)
int Gyallaly[12];    //�v���C���[�摜�̕ϐ�(�����12�����Ȃ̂�12)
int Drct_Count;
int count_x;         //�}�b�v�T�C�Y���J�E���g������� x
int count_y;         //�}�b�v�T�C�Y���J�E���g������� y
bool Move_Flg;       //����Ǘ�
bool Up_Flg;         //�オ�����ꂽ��(������count�̊Ǘ����s��)
bool Down_Flg;       //���������ꂽ��(������count�̊Ǘ����s��)
bool Right_Flg;      //�E�������ꂽ��(������count�̊Ǘ����s��)
bool Left_Flg;       //���������ꂽ��(������count�̊Ǘ����s��)
bool Back_Flg;       //Back_Move�t���O
bool Player_Image;   //�摜�̏���(�A�j���[�V����)
bool Check_Flg;      //�m�F�p

//Box
int Box_x;
int Box_y;
int Box_nx;         //Box�̉��� x ���W
int Box_ny;         //Box�̉��� y ���W
int Judge_x;        //Box�̈ړ���𔻒f���� x
int Judge_y;        //Box�̈ړ���𔻒f���� y
int Box_Element;    //Box�̗v�f��


//Player�̏�����
int Player_Init()
{
	//�v���C���[��x/y���W������������(�l��MAP.h���)
	Player.x = MAP_Player_Pos_Init_x();  //�v���C���[�̏����� x
	Player.y = MAP_Player_Pos_Init_y();  //�v���C���[�̏����� y
	Drct = E_Drct_None;                  //�����̏�����
	LoadDivGraph("gazou/Player.png", 12, 3, 4, 64, 64, Gyallaly);  	//�摜�̓ǂݍ���

	i=0;                   //for���p
	Drct_Count = 0;

	//Player
	S_Player Player;         //Player�̍\����(�w�b�_�[�t�@�C���ɂč쐬)
	None_Num = 7;        //�摜�̃X�^���o�C���(�Î~���)
	Gyallaly[12];        //�v���C���[�摜�̕ϐ�(�����12�����Ȃ̂�12)
	count_x = 0;         //�}�b�v�T�C�Y���J�E���g������� x
	count_y = 0;         //�}�b�v�T�C�Y���J�E���g������� y
	Move_Flg = false;   //����Ǘ�
	Up_Flg = false;     //�オ�����ꂽ��(������count�̊Ǘ����s��)
	Down_Flg = false;   //���������ꂽ��(������count�̊Ǘ����s��)
	Right_Flg = false;  //�E�������ꂽ��(������count�̊Ǘ����s��)
	Left_Flg = false;   //���������ꂽ��(������count�̊Ǘ����s��)
	Back_Flg = false;   //Back_Move�t���O
	Player_Image = 0;   //�摜�̏���(�A�j���[�V����)
	Check_Flg = false;  //�m�F�p

	//Box
	Box_x = 0;
	Box_y = 0;
	Box_nx = 0;         //Box�̉��� x ���W
	Box_ny = 0;         //Box�̉��� y ���W
	Judge_x = 0;        //Box�̈ړ���𔻒f���� x
	Judge_y = 0;        //Box�̈ړ���𔻒f���� y
	Box_Element;        //Box�̗v�f��

	return 0;
}


//�v�Z(���t���[���Ă΂��)
int Player_Dpct()
{

	//�Î~��ԂȂ�L�[���͂��󂯕t����
	if (Move_Flg == false)
	{
		//�߂�{�^����������Ă��Ȃ��Ȃ�
		if (Back_Flg == false)
		{
			//���̕ϐ�ny/nx�̍��W�̍X�V
			Player.nx = Player.x;
			Player.ny = Player.y;
		}

	//�L�[���͏���

		//��
		if (Keyboard_Get(KEY_INPUT_UP) == 1)   //��
		{
			Player.ny--;    //�v���C���[�̉��̕ϐ�ny�̍��W��-1(-MAP_SIZE)�����
			Drct = E_Drct_Up;
		}
		//��
		if (Keyboard_Get(KEY_INPUT_LEFT) == 1)   //��
		{
			Player.nx--;      //�v���C���[�̉��̕ϐ�nx��x���W��-1(-MAP_SIZE)�����
			Drct = E_Drct_Left;
		}
		//��
		if (Keyboard_Get(KEY_INPUT_DOWN) == 1)   //��
		{
			Player.ny++;      //�v���C���[�̉��̕ϐ�ny��y���W��+1(+MAP_SIZE)�����
			Drct = E_Drct_Down;
		}
		//�E
		if (Keyboard_Get(KEY_INPUT_RIGHT) == 1)   //��
		{
			Player.nx++;       //�v���C���[�̉��̕ϐ�nx��x���W��+1(+MAP_SIZE)�����
			Drct = E_Drct_Right;
		}


	}

	//�v���C���[�̈ړ���ɉ������邩�̔��f
	if (Drct != E_Drct_None)  //�L�[�����͂���Ă���Ȃ�
	{
		Player_Move_Check();
	}
		

	//�v���C���[���ړ�������
	if (Move_Flg == true)	//�ړ��悪�ǂ���Ȃ��Ȃ�true�ɂȂ��Ă���
	{
		Player_Move();
	}



	return 0;
}


int Player_Move_Check()
{
	//��

		//�ړ���ɕǂ� �Ȃ� �Ȃ�
		if (MAP_Data(Player.nx, Player.ny) == E_Object_Load || MAP_Data(Player.nx, Player.ny) == E_Object_Goal)
		{
			Move_Flg = true;  //Move_Flg��true�@����ɂ�蓮���Ă���Ƃ�������ɂȂ�
		}

		//�ړ���ɕǂ� ���� �Ȃ�
		if (MAP_Data(Player.nx, Player.ny) == E_Object_Wall)
		{
			//�ǂȂ瓮�삳���Ȃ�
			Player.ny = Player.ny;
			Player.nx = Player.nx;

			//�e�L�[�t���O��false�@>>  �L�[���͂��ł���悤�ɂȂ�
			Drct = E_Drct_None;
		}

	//Box


//	for(i=0;i<Box_Element;i++)  //�����̂��
//	{
		Box_Pos(&Box_x, &Box_y, Box_Element);

		if (Player.nx == Box_x && Player.ny == Box_y)
		{
			//Box - Player = 1or-1 ������@Box�ɑ�����Box�̎��̍��W���o��B
			Judge_x = Player.nx - Player.x;
			Judge_y = Player.ny - Player.y;

			//���̕ϐ�(nx�Eny)�ɑ��
			Box_nx = Box_x + Judge_x;
			Box_ny = Box_y + Judge_y;

			//�����A�����ꂽ�����ɕǂ��@�Ȃ��@�Ȃ�
			if (MAP_Data(Box_nx, Box_ny) == E_Object_Load || MAP_Data(Box_nx, Box_ny) == E_Object_Goal)
			{
				Box_Move(Drct, Box_Element);
				UI_Box_Move_History(Drct, Box_Element);			
			}
			//�����A�����ꂽ�����ɕǂ��@����@�Ȃ�
			if (MAP_Data(Box_nx, Box_ny) == E_Object_Wall)
			{
				Player.nx = Player.nx;
				Player.ny = Player.ny;
				Move_Flg = false;
				Drct = E_Drct_None;
			}
		}
//	}

	return 0;
}


int Player_Move()
{

		//���͂��ꂽ�L�[�̕����ɂ��킹��count�� + �� - �����
	switch (Drct)
	{
		//��
	case E_Drct_Up:
		count_y--;
		break;
		//��
	case E_Drct_Left:
		count_x--;
		break;
		//��
	case E_Drct_Down:
		count_y++;
		break;
		//�E
	case E_Drct_Right:
		count_x++;
		break;
	}


	//�����Ax�Ey�̃J�E���g���}64�Ȃ�
	if (count_x >= MAP_SIZE || count_y <= -MAP_SIZE || count_x <= -MAP_SIZE || count_y >= MAP_SIZE)
	{
		//�v���C���[�̍��W�ɉ��̍��W��������  >>  �`��̍ۂɎg���̂�x��y
		Player.y = Player.ny;
		Player.x = Player.nx;

		//�J�E���g�̏�����  �e�t���O��false(0)
		count_x = 0;
		count_y = 0;
		Move_Flg = false;
		Drct = E_Drct_None;

	}

	return 0;
}

int Player_Back_Argument()
{
	if (Back_Flg == false)
	{
		UI_Player_Move_History(Drct);   //�v���C���[�̌�����n��

		UI_StepCount_MoveOn();   //�X�e�b�v�J�E���g�𑝂₷
	}
	else
	{
		Back_Flg = false;
	}

	Drct_Count = 0;

	return 0;
}

//�o�b�N�X�y�[�X�������ꂽ��߂�
int Player_Back_Move(E_Drct Old_Drct) {
	//�t���O��true���ƃJ�E���g�����
	Move_Flg = true;

	//�����𔽓]������
	Drct = (E_Drct)((Old_Drct + 2) % 4);


	//�����ɍ��킹�Ĉړ�����
	switch (Drct) 
	{
		//��
	case E_Drct_Up:
		Player.ny += -1;
		break;
		//��
	case E_Drct_Left:
		Player.nx += -1;
		break;
		//��
	case E_Drct_Down:
		Player.ny += 1;
		break;
		//�E
	case E_Drct_Right:
		Player.nx += 1;
		break;
	}

	//�t���O��true���ƁAPlayer��nx/ny���W��x/y���������Ȃ�
	Back_Flg = true;




	return 0;
}

//�`��(���t���[���Ă΂��)
int Player_Draw()
{
	/*MAP_SIZE�������邱�Ƃɂ���ă}�X�̈ړ�������1�}�X�Ȃ�+1�������64�����Ƃ����悤�Ɋy�ɂȂ�*/
	/*LoadDivGraph("File/name.",�摜�̕�����,���̖���,�c�̖���,�摜�̃T�C�Yx,�摜�̃T�C�Yy,�z��)*/

	//�L�[���͂���ĂȂ��ꍇ�̉摜
	if (Drct == E_Drct_None)
	{
		DrawGraph(Player.x * MAP_SIZE + count_x, Player.y * MAP_SIZE + count_y, Gyallaly[None_Num], TRUE);
	}


	//�����AMove_Flg��ON�Ȃ�(Move_Flg�͈ړ��悪�ǂ���Ȃ��Ȃ�ON�ɂȂ��Ă���)
	if (Move_Flg == true)
	{

		//�㉺
		if (Drct == E_Drct_Up || Drct == E_Drct_Down)
		{
			Player_Image = count_y / 8 % 3;   //�摜�̃A�j���[�V�����p�̕ϐ� y
		}
		//���E
		if (Drct == E_Drct_Right || Drct == E_Drct_Left)
		{
			Player_Image = count_x / 8 % 3;   //�摜�̃A�j���[�V�����p�̕ϐ� x
		}

		//��
		if (Drct == E_Drct_Up)
		{
			DrawGraph(Player.x * MAP_SIZE + count_x, Player.y * MAP_SIZE + count_y, Gyallaly[0 + Player_Image], TRUE);
			None_Num = 1;
		}
		//��
		if (Drct == E_Drct_Left)
		{
			DrawGraph(Player.x * MAP_SIZE + count_x, Player.y * MAP_SIZE + count_y, Gyallaly[9 + Player_Image], TRUE);
			None_Num = 10;
		}
		//��
		if (Drct == E_Drct_Down)
		{
			DrawGraph(Player.x * MAP_SIZE + count_x, Player.y * MAP_SIZE + count_y, Gyallaly[6 + Player_Image], TRUE);
			None_Num = 7;
		}
		//�E
		if (Drct == E_Drct_Right)
		{
			DrawGraph(Player.x * MAP_SIZE + count_x, Player.y * MAP_SIZE + count_y, Gyallaly[3 + Player_Image], TRUE);
			None_Num = 4;
		}

	}


	//�m�F�p�[�e�ϐ�(��ɍ폜)
#ifdef _DEBUG

	DrawFormatString(70, 20, GetColor(255, 0, 0), "0:�� 1:�E 2:�� 3:�� 4:�ʏ�");
	DrawFormatString(320, 20, GetColor(255, 0, 0), "����:%d", Drct);
	DrawFormatString(420, 20, GetColor(255, 0, 0), "MoveFlg:%d", Move_Flg);
	DrawFormatString(70, 40, GetColor(255, 0, 0), "��:%d", Box_Element);
	DrawFormatString(70, 60, GetColor(255, 0, 0), "back_flg:%d", Back_Flg);

	//DrawFormatString(130, 40, GetColor(255, 0, 0), "box��x���W:%d", Box_x);
	//DrawFormatString(250, 40, GetColor(255, 0, 0), "box��y���W:%d", Box_y);
	//DrawFormatString(200, 400, GetColor(255, 0, 0), "(�ڐG)Check_Flg:%d", Check_Flg);
#endif

	return 0;
}

//BackSpeace�ƃL�[����𓯎��ɂł��Ȃ��悤�ɂ��邽�߂�Move_Flg��n��
int Player_Move_Flg() {
	//0 �� 1
	return Move_Flg;

}

int Player_End()
{
	//No Script
	return 0;
}