#include "DxLib.h"
#include "Player.h"
#include "Keyboard.h"
#include "MAP.h"
#include "Box.h"
#include "UI.h"

typedef enum 
{

	E_Object_Wall,                   //�s���Ȃ��ꏊ
	E_Object_Load,                   //������ꏊ
	E_Object_Box,                    //�{�b�N�X

}E_Object;


//�����ŕϐ���錾�iC++���g��Ȃ��̂ŃO���[�o���ϐ��j
S_Player Player;      //Player�̍\����(�w�b�_�[�t�@�C���ɂč쐬)
E_Drct Drct;          //�����̊Ǘ�
int count_x = 0;      //�}�b�v�T�C�Y���J�E���g���� x
int count_y = 0;      //�}�b�v�T�C�Y���J�E���g���� y
bool  Move_Flg  = false;  //����Ǘ�
bool Up_Flg    = false;  //�オ�����ꂽ��(������count�̊Ǘ����s��)
bool Down_Flg  = false;  //���������ꂽ��(������count�̊Ǘ����s��)
bool Right_Flg = false;  //�E�������ꂽ��(������count�̊Ǘ����s��)
bool Left_Flg  = false;  //���������ꂽ��(������count�̊Ǘ����s��)
int Gyallaly[12];       //�v���C���[�摜�̕ϐ�(�����12�����Ȃ̂�12)
static int i=0;         //���[�v�p
int Box_Cnt;
int Box_x = 3;
int Box_y = 3;

//������
int Player_Init() 
{
	/*�v���C���[��x/y���W������������(�l��MAP.h���)*/
	Player.x = Map_Player_Pos_Init_x();  //�v���C���[�̏����� x
	Player.y = Map_Player_Pos_Init_y();  //�v���C���[�̏����� y
	Box_Cnt = Map_Box_Count_Init();  //�{�b�N�X�̌�
	LoadDivGraph("gazou/PlayerTest.png", 12, 3, 4, 64, 64, Gyallaly);  	//�摜�̓ǂݍ���
	Drct = E_Drct_None;
	return 0;
}

//�v�Z(���t���[���Ă΂��)
int Player_Dpct() 
{

	/**********************************�@�㉺���E�@******************************************/
	//�����AMove_Flg��false(0)�Ȃ�L�[���͂��󂯕t����(�����Ă��Ȃ����)
	if (Move_Flg == false) 
	{
		/*���̕ϐ�nx�Ƀv���C���[��x���W������  >>  ny/nx�̍��W�̍X�V*/
		Player.nx = Player.x;
		Player.ny = Player.y;
		
		//��
		if (Keyboard_Get(KEY_INPUT_UP) == 1)   //���������ꂽ��
		{
			Player.ny--;    //�v���C���[�̉��̕ϐ�ny�̍��W��-1(-MAP_SIZE)�����
			Drct = E_Drct_Up;  //��̃L�[�������ꂽ
		}
		//��
		if (Keyboard_Get(KEY_INPUT_DOWN) == 1)   //���������ꂽ��
		{
			Player.ny++;      //�v���C���[�̉��̕ϐ�ny��y���W��+1(+MAP_SIZE)�����
			Drct = E_Drct_Down;  //���̃L�[�������ꂽ
		}
		//��
		if (Keyboard_Get(KEY_INPUT_LEFT) == 1)   //���������ꂽ��
		{
			Player.nx--;      //�v���C���[�̉��̕ϐ�nx��x���W��-1(-MAP_SIZE)�����
			Drct = E_Drct_Left;  //���̃L�[�������ꂽ
		}
		//�E
		if (Keyboard_Get(KEY_INPUT_RIGHT) == 1)   //���������ꂽ��
		{
			Player.nx++;       //�v���C���[�̉��̕ϐ�nx��x���W��+1(+MAP_SIZE)�����
			Drct = E_Drct_Right;  //�E�̃L�[�������ꂽ
		}
	}

	/*********************************�@�ړ�����(��)�@*****************************************/
	//�����A�㉺���E�ǂꂩ�̃L�[��������Ă���Ȃ�
	if (Drct != E_Drct_None)
	{
		//�����A�ړ��悪�ǂ���Ȃ��Ȃ�
		if (Map_Data(Player.nx, Player.ny) == E_Object_Load) 
		{
			Move_Flg = true;  //Move_Flg��true�@����ɂ�蓮���Ă���Ƃ�������ɂȂ�
		}

		//�����A�ړ��悪�ǂȂ�
		if (Map_Data(Player.nx, Player.ny) == E_Object_Wall)
		{
			/*�ǂȂ瓮�삳���Ȃ�(���L�̑�����͕�����₷���悤�ɏ����Ă��邾��)*/
			Player.ny = Player.ny;
			Player.nx = Player.nx;

			/*�e�L�[�t���O��false�@>>  �L�[���͂��ł���悤�ɂȂ�*/
			Drct = E_Drct_None;
		}

		//�����AMove_Flg��true�Ȃ�(Move_Flg�͈ړ��悪�ǂ���Ȃ��Ȃ�true�ɂȂ��Ă���)
		if (Move_Flg == true)
		{
			//�e�L�[��Flg�ɂ�肻�̕����ɂ��킹��count�� + �� - �����
			if (Drct == E_Drct_Up)
			{
				count_y--;   //y���W�� - �����
			}
			if (Drct == E_Drct_Down)
			{
				count_y++;   //y���W�� + �����
			}
			if (Drct == E_Drct_Left)
			{
				count_x--;   //x���W�� - �����
			}
			if (Drct == E_Drct_Right)
			{
				count_x++;   //x���W�� + �����
			}
		}

		//�����Ax/y�̃J�E���g���}64�Ȃ�
		if (count_x >= MAP_SIZE || count_y <= -MAP_SIZE || count_x <= -MAP_SIZE || count_y >= MAP_SIZE)
		{
			/*�v���C���[�̍��W�ɉ��̍��W��������  >>  �`��̍ۂɎg���̂�x��y*/
			Player.y = Player.ny;
			Player.x = Player.nx;


			/*�J�E���g�̏�����  �e�t���O��false(0)*/
			count_x = 0;
			count_y = 0;
			Move_Flg = false;
			Drct =  E_Drct_None;

		}
	}

	/************************************�@�ړ�����(Box)�@*****************************************/

	//if (Map_Data(Player.nx, Player.ny) == Map_Data())
	//{

		//Box_Touch(ON);
	//}

	return 0;
}

//�o�b�N�X�y�[�X�������ꂽ��߂�
int Player_Back_Move(E_Drct Old_Drct) {

	Drct = (E_Drct)((Old_Drct + 2) % 4);
	Move_Flg = true;
	Player.x = Player.nx;
	Player.y = Player.ny;

	return 0;
}

//�`��(���t���[���Ă΂��)
int Player_Draw() 
{

   /****************************************** Player ******************************************/
	/*MAP_SIZE�������邱�Ƃɂ���ă}�X�̈ړ�������1�}�X�Ȃ�+1�������64�����Ƃ����悤�Ɋy�ɂȂ�*/
	/*LoadDivGraph("File/name.",�摜�̕�����,���̖���,�c�̖���,�摜�̃T�C�Yx,�摜�̃T�C�Yy,�z��)*/



	//�L�[���͂���ĂȂ��ꍇ�̉摜(�r��)
	//if (Move_Flg == false) {

		DrawGraph(Player.x * MAP_SIZE + count_x, Player.y * MAP_SIZE + count_y, Gyallaly[0], TRUE); // x,y �̈ʒu�ɃL������`��
	//}

	//�����AMove_Flg��ON�Ȃ�(Move_Flg�͈ړ��悪�ǂ���Ȃ��Ȃ�ON�ɂȂ��Ă���)
	if (Move_Flg == true) 
	{
		//��
		if (Drct == E_Drct_Up)
		{
			DrawGraph(Player.x * MAP_SIZE + count_x, Player.y * MAP_SIZE + count_y, Gyallaly[0], TRUE);
		}
		//��
		if (Drct == E_Drct_Down)
		{
			DrawGraph(Player.x * MAP_SIZE + count_x, Player.y * MAP_SIZE + count_y, Gyallaly[6], TRUE);
		}
		//�E
		if (Drct == E_Drct_Right)
		{
			DrawGraph(Player.x * MAP_SIZE + count_x, Player.y * MAP_SIZE + count_y, Gyallaly[3], TRUE);
		}
		//��
		if (Drct == E_Drct_Left)
		{

			DrawGraph(Player.x * MAP_SIZE + count_x, Player.y * MAP_SIZE + count_y, Gyallaly[9], TRUE);
		}
	}
	
	/************************************�@�ړ�����(Box)�@*****************************************/
	DrawBox(Box_x*MAP_SIZE, Box_y*MAP_SIZE, Box_x*MAP_SIZE + MAP_SIZE, Box_y*MAP_SIZE + MAP_SIZE, GetColor(255, 0, 0), TRUE);


	//�m�F�p�[�e�ϐ�(��ɍ폜)
	DrawFormatString(0, 20, GetColor(255, 0, 0), "x���W:%d",Player.x);
	DrawFormatString(80,20, GetColor(255, 0, 0), "y���W:%d",Player.y);
	DrawFormatString(0, 40, GetColor(255, 0, 0), "MoveFlg:%d",Move_Flg);
	DrawFormatString(150, 20, GetColor(255, 0, 0), "x�J�E���g:%d", count_x);
	DrawFormatString(250, 20, GetColor(255, 0, 0), "y�J�E���g:%d", count_y);
	DrawFormatString(350, 20, GetColor(255, 0, 0), "��:%d", Box_Cnt);


	return 0;
}
int Player_End() 
{
	//No Script
	return 0;
}