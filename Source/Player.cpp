#include "DxLib.h"
#include "Player.h"
#include "Keyboard.h"
#include "MAP.h"
#include "Box.h"
#include "UI.h"


/**********************************�@�ϐ��錾�@******************************************/

//Player

	//Player�̈ʒu
	S_Player Player;     //Player�̍\����(�w�b�_�[�t�@�C���ɂč쐬)

	//�ړ�
	bool Move_Flg;       //����Ǘ�
	int count_x;         //�}�b�v�T�C�Y���J�E���g ��
	int count_y;         //�}�b�v�T�C�Y���J�E���g ��

	//����
	E_Drct Drct;     //�����̊Ǘ�

	//�摜
	int None_Num;        //�摜�̃X�^���o�C���(�Î~���)
	int Gyallaly[12];    //�v���C���[�摜�̕ϐ�(�����12�����Ȃ̂�12)
	bool Player_Image;   //�摜�̏���(�A�j���[�V����)

	//����߂�
	bool Back_Flg;   //Back_Move�t���O
	int Argument_Check;  //�����Ɗ֐��̊Ǘ����s��


//Box

	//Box�̍��W
	
	int Box_x;       // x ���W
	int Box_y;       // y ���W
	int Box_nx;      //���� x ���W
	int Box_ny;      //���� y ���W
	
	//S_Box Box[5];

	//�ړ���̔��f
	int Judge_x;     //Box�̉��̈ړ���𔻒f����
	int Judge_y;     //Box�̏c�̈ړ���𔻒f����

	//���Ǘ�
	int Box_Max;  //Box�̍ő吔


/**********************************�@������(���)�@******************************************/
int Player_Init()
{
 //Player

	//Player�̈ʒu(MAP���)
	Player.x = MAP_Player_Pos_Init_x();
	Player.y = MAP_Player_Pos_Init_y();

	//�ړ�
	Move_Flg = false;   //�����Ă��Ȃ�
	count_x = 0;
	count_y = 0;

	//����
	Drct = E_Drct_None;  //����:����

	//�摜
	Gyallaly[12] = {};
	LoadDivGraph("Images/Player.png", 12, 3, 4, 64, 64, Gyallaly);  //�z��uGyallaly�v�։摜������
			//LoadDivGraph("File/name.",�摜�̕�����,���̖���,�c�̖���,�摜�̃T�C�Yx,�摜�̃T�C�Yy,�z��)
	None_Num = 7;    //�X�^���o�C��Ԃ̌����Ă�����𐳖ʂւ��邽�߂̉摜�ԍ�7
	Player_Image = 0;

	//����߂�
	Back_Flg = false;    //�L�[���͂���Ă��Ȃ�
	Argument_Check = 0;  //�v���C���[���{�b�N�X���������Ȃ�


 //Box

	//���W
	
	Box_x = 0;
	Box_y = 0;
	Box_nx = 0;
	Box_ny = 0;
	

	//�ړ�
	Judge_x = 0;
	Judge_y = 0;

	//���Ǘ�
	Box_Max = MAP_Box_Count_Init();

	return 0;
}


/**********************************�@�v�Z(����) ******************************************/
int Player_Dpct()
{

	//�L�[���͏�����nx/ny�̍��W�X�V
	if (Move_Flg == false )  //�Î~��ԂȂ�L�[���͂��󂯕t����
	{
		//nx/ny�̍��W�X�V
		if (Back_Flg == false)  //BackSpace��������Ă��Ȃ��Ȃ�
		{
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
		if (Keyboard_Get(KEY_INPUT_LEFT) == 1)  //��
		{
			Player.nx--;      //�v���C���[�̉��̕ϐ�nx��x���W��-1(-MAP_SIZE)�����
			Drct = E_Drct_Left;
		}
		//��
		if (Keyboard_Get(KEY_INPUT_DOWN) == 1)  //��
		{
			Player.ny++;      //�v���C���[�̉��̕ϐ�ny��y���W��+1(+MAP_SIZE)�����
			Drct = E_Drct_Down;
		}
		//�E
		if (Keyboard_Get(KEY_INPUT_RIGHT) == 1) //��
		{
			Player.nx++;       //�v���C���[�̉��̕ϐ�nx��x���W��+1(+MAP_SIZE)�����
			Drct = E_Drct_Right;
		}

	}

	//�v���C���[�̈ړ���ɉ������邩�̔��f(�֐�:Player_Move_Check)
	if (Drct != E_Drct_None)  //�L�[�����͂���Ă���Ȃ�
	{
		Player_Move_Check();
	}
		
	//�v���C���[���ړ�������(�֐�:Player_Move)
	if (Move_Flg == true)	//�ړ��悪�ǂ���Ȃ��Ȃ�
	{
		Player_Move();
		Player_Back_Argument();
	}

	return 0;
}

/**********************************�@�ړ����f(����)�@******************************************/
int Player_Move_Check()
{
	//Player

		//�ړ��悪 �����S�[�� �Ȃ�@>>�@����
		if (MAP_Data(Player.nx, Player.ny) == E_Object_Load || MAP_Data(Player.nx, Player.ny) == E_Object_Goal)
		{
			Move_Flg = true;  //������(Player_Move���쓮)

			if (Argument_Check == 0)
			{
				UI_Player_Move_History(Drct);
				Argument_Check = 1;   //������������
			}
		}

		//�ړ��悪 �� �Ȃ�@>>�@�����Ȃ�
		if (MAP_Data(Player.nx, Player.ny) == E_Object_Wall)
		{
			//�e�L�[�t���O��false�@>>  �L�[���͂��ł���悤�ɂȂ�
			Move_Flg = false;
			Drct = E_Drct_None;
		}

	//Box

		for(int i=0;i<Box_Max;i++)  //�����̂��
		{
		    //���W�Ɖ��ڂ��̎擾(MAP���)
			Box_Pos(&Box_x, &Box_y, i);

			//�ړ��悪 Box �Ȃ�@>>�@Box�𓮂����邩���f
			if (Player.nx == Box_x && Player.ny == Box_y)
			{
				//Box - Player = 1or-1 ������@Box�ɑ�����Box�̎��̍��W���o��B
				Judge_x = Player.nx - Player.x;
				Judge_y = Player.ny - Player.y;

				//���̕ϐ�(nx/ny)�ɑ��
				Box_nx = Box_x + Judge_x;
				Box_ny = Box_y + Judge_y;
				for (int j = 0; j < Box_Max; j++)
				{
					int Temp_x = 0;
					int Temp_y = 0;
					Box_Pos(&Temp_x, &Temp_y, j);

				//�����ꂽ������ �����S�[�� �Ȃ�@>>�@Box�ֈ�����n��
				if ((MAP_Data(Box_nx, Box_ny) == E_Object_Load || MAP_Data(Box_nx, Box_ny) == E_Object_Goal) || (Box_nx == Temp_x && Box_ny == Temp_y))
				{
					//Box_Move(Drct, i);  //�����Ɖ��ڂ�Box��
					//UI_Box_Move_History(Drct, i);
				}



					if (i != j)
					{
						//�����ꂽ������ �� �Ȃ�@>>�@�����Ȃ�
						if (MAP_Data(Box_nx, Box_ny) == E_Object_Wall || (Box_nx  == Temp_x && Box_ny == Temp_y))
						{
							//�e�L�[�t���O��false�@>>  �L�[���͂��ł���悤�ɂȂ�
							Move_Flg = false;
							Drct = E_Drct_None;
						}
						else
						{
							Box_Move(Drct, i);  //�����Ɖ��ڂ�Box��
						UI_Box_Move_History(Drct, i);
						}
					}
				}
			}
     	}

	return 0;
}

/**********************************�@�ړ�(����:Dpct)�@******************************************/
int Player_Move()
{
	//���͂��ꂽ�L�[�̌����ɂ��킹��count_x/count_y�� + �� - �����
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


	//count_x/count_y�̂ǂꂩ�̃J�E���g���}64�Ȃ�@>>�@Player.x/y�̍��W�X�V�E�J�E���g�ƃt���O�̏�����
	if (count_x >= MAP_SIZE-1 || count_y <= -MAP_SIZE+1 || count_x <= -MAP_SIZE+1 || count_y >= MAP_SIZE-1)
	{
		//�v���C���[�̍��W�ɉ��̍��W�������č��W���X�V(�`��̍ۂɎg���̂�Player.x/.y)
		Player.y = Player.ny;
		Player.x = Player.nx;

		//�J�E���g�̏�����
		count_x = 0;
		count_y = 0;

		//�t���O�ƌ����̊Ǘ�
		Move_Flg = false;
		Drct = E_Drct_None;
		Argument_Check = 0;
	}

	return 0;
}

/**********************************�@����߂� �����n��(����)�@******************************************/
int Player_Back_Argument()
{
	//BackSpace��������Ă��Ȃ��Ȃ�(�v���C���[���i�񂾂�)�@>>�@�v���C���[�̌�����UI�֓n���E�����̑���
	if (Back_Flg == false)
	{
		if (Argument_Check == 1)
		{
			UI_StepCount_MoveOn();
			Argument_Check = 2;
		}
	}

	//Back_Flg��true�Ȃ�@>>�@Back_Flg ��false��
	else
	{
		//BackSpace��������Ă��Ȃ���Ԃ�
		Back_Flg = false;
	}

	return 0;
}

/**********************************�@����߂�(����:UI���)�@******************************************/
int Player_Back_Move(E_Drct Old_Drct) {

	//�t���O��true����Player��nx/ny���W��x/y���������Ȃ�
	Back_Flg = true;

	//�����𔽓]������
	Drct = (E_Drct)((Old_Drct + 2) % 4);

	Argument_Check = 4;

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

	return 0;
}

/**********************************�@�`��(����)�@******************************************/
int Player_Draw()
{
	//MAP_SIZE�������邱�Ƃɂ���ă}�X�̈ړ�������1�}�X�Ȃ�+1�������64�����Ƃ����悤�Ɋy�ɂȂ�

	//�L�[���͂���ĂȂ����̉摜�\��
	if (Drct == E_Drct_None)
	{
		DrawGraph(Player.x * MAP_SIZE + count_x, Player.y * MAP_SIZE + count_y, Gyallaly[None_Num], TRUE);
	}


	//�����Ă�悤�Ɍ�����p�ɉ摜��\������ENone_Num(�Î~��Ԏ��̌�������)�̍X�V
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


#ifdef _DEBUG

	DrawFormatString(700,  20, GetColor(255, 0, 0), "0:�� 1:�E 2:�� 3:�� 4:�ʏ�");
	DrawFormatString(700,  40, GetColor(255, 0, 0), "Drct:%d", Drct);
	DrawFormatString(700,  60, GetColor(255, 0, 0), "MoveFlg:%d", Move_Flg);

	DrawFormatString(700,  120, GetColor(255, 0, 0), "Box�̍ő��:%d", Box_Max);
	DrawFormatString(700, 160, GetColor(255, 0, 0), "Box_x:%d", Box_x);
	DrawFormatString(700, 180, GetColor(255, 0, 0), "Box_y:%d", Box_y);
	DrawFormatString(700, 200, GetColor(255, 0, 0), "Box_nx:%d", Box_nx);
	DrawFormatString(700, 220, GetColor(255, 0, 0), "Box_ny:%d", Box_ny);
	DrawFormatString(700, 240, GetColor(255, 0, 0), "Judge_x:%d", Judge_x);
	DrawFormatString(700, 260, GetColor(255, 0, 0), "Judge_y:%d", Judge_y);

	DrawFormatString(700, 300, GetColor(255, 0, 0), "Argument_Check:%d", Argument_Check);

#endif

	return 0;
}

/**********************************�@��������h�~(����:Dpct)�@******************************************/
int Player_Move_Flg() {
	//BackSpeace�ƃL�[����𓯎��ɂł��Ȃ��悤�ɂ��邽�߂�Move_Flg��n��

	return Move_Flg;

}

/**********************************�@�I��(���)�@******************************************/
int Player_End()
{
	//No Script
	return 0;
}