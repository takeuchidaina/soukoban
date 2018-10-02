#include "Dxlib.h"
#include "Box.h"
#include "Player.h"
#include "MAP.h"
#include "Keyboard.h"

#define OFF 0		//FALSE
#define ON 1		//TRUE
#define LOAD 1		//��
#define WALL 0		//��



static int  i;   //for
int  yousosuu;	 //Box�̌�
S_Box box[5];    //�\����
int Box_Move_Flg = OFF;		//�����������Ȃ���
int Box_Count_x = 0;	//�k���k��������
int Box_Count_y = 0;// �k���k��������
int Handle;				//// �f�[�^�n���h���i�[�p�ϐ�

int Box_Up_Flg = OFF;  //�オ�����ꂽ��(������count�̊Ǘ����s��)
int Box_Down_Flg = OFF;  //���������ꂽ��(������count�̊Ǘ����s��)
int Box_Right_Flg = OFF;  //�E�������ꂽ��(������count�̊Ǘ����s��)
int Box_Left_Flg = OFF;  //���������ꂽ��(������count�̊Ǘ����s��)

int Box_Pos(int*x, int*y, int num) {
	//�{�b�N�X�̈ʒu���}�b�v����Ⴄ

	*x = box[num].x;                             
	*y = box[num].y;

	return 0;
}

int Box_Move(E_Drct drct, int num) {
	//�v���C���[����{�b�N�X�ɂ����֓����Ƃ����֐������炤                                                               

	switch (drct) {

	case E_Drct_Up:
			//box[num].x += 0;
			box[num].y += -1;
			break;
		
	case E_Drct_Right:
			box[num].x += 1;
			//box[num].y += 0;
			break;
		
	case E_Drct_Down:
			//box[num].x += 0;
			box[num].y += 1;
			break;
		
	case E_Drct_Left:
			box[num].x += -1;
			//box[num].y += 0;
			break;
	};

	return 0;
}

/*int Box_Bectl(int *x, int *y, int num) {
	//���������̃x�N�g���i�����j�����炤

	num = ;

	*x = box[num].x = ;
	*y = box[num].y = ;

	return 0;
}*/

int Box_Init() {
	//�����ŏ�����������
	
	yousosuu =  Map_Box_Count_Init();
	
	for (i = 0;i < yousosuu;i++) {
		//Map_Box_Pos_Init(box[i], i);    //�Ȃɂ�����

		/*�{�b�N�X�ƕǂ̓����蔻��*/
		if (Map_Data(box[i].y, box[i].x) == LOAD) {
			Box_Move_Flg = ON;
		}
		if (Map_Data(box[i].y, box[i].x) == WALL) {
			box[i].y = box[i].x;
			box[i].x = box[i].y;
			Box_Move_Flg = OFF;
		}
	}
	return 0;
}

int Box_Dbug() {

	if (Box_Move_Flg == OFF) {
		//��
		if (Keyboard_Get(KEY_INPUT_UP) == 1)   //���������ꂽ��
		{
			Box_Up_Flg = ON;
			Box_Move(E_Drct_Up, 0);
		}
		//��
		if (Keyboard_Get(KEY_INPUT_RIGHT) == 1)   //���������ꂽ��
		{
			Box_Move(E_Drct_Right, 0);
			Box_Right_Flg = ON;
		}
		//��
		if (Keyboard_Get(KEY_INPUT_DOWN) == 1)   //���������ꂽ��
		{
			Box_Move(E_Drct_Down, 0);
			Box_Down_Flg = ON;
		}
		//�E
		if (Keyboard_Get(KEY_INPUT_LEFT) == 1)   //���������ꂽ��
		{
			Box_Move(E_Drct_Left, 0);
			Box_Left_Flg = ON;
		}
	}
	return 0;
}

int Box_Dpct() {
	//�����Ōv�Z
	//Dqct�͖��t���[���Ă΂��
	if (Box_Up_Flg == ON || Box_Right_Flg == ON || Box_Down_Flg == ON || Box_Left_Flg == ON) {
		
			/*�{�b�N�X���k���k������������*/
			if (Box_Up_Flg == ON) {
				Box_Count_y--;		//y���W��-�����
			}

			if (Box_Right_Flg == ON) {
				Box_Count_x++;		//x���W��+�����
			}

			if (Box_Down_Flg == ON) {
				Box_Count_y++;		//y���W��+�����
			}

			if (Box_Left_Flg == ON) {
				Box_Count_x--;		//x���W��-�����
			}
		
		
		if (Box_Count_y <= -MAP_SIZE || Box_Count_x >= MAP_SIZE || Box_Count_y >= MAP_SIZE || Box_Count_x <= -MAP_SIZE)
		{
			/*�v���C���[�̍��W�ɉ��̍��W��������  >>  �`��̍ۂɎg���̂�x��y
			Player.y = Player.ny;
			Player.x = Player.nx;*/

			/*�J�E���g�̏�����  �e�t���O��OFF(0)*/
	        Box_Count_x = 0;
			Box_Count_y = 0;
			Box_Up_Flg = OFF;
			Box_Right_Flg = OFF;
			Box_Down_Flg = OFF;
			Box_Left_Flg = OFF;
		}
	}
	return 0;
}

int Box_Draw() {
	//�����ŕ`��
	//�����������t���[���Ă΂�܂����v�Z�Ƃ͕ʂɏ����܂�

	Handle = LoadGraph("gazou/block.png"); // �摜�����[�h

	for (i = 0;i < yousosuu;i++) {
			DrawGraph(box[i].x * MAP_SIZE + Box_Count_x, box[i].y * MAP_SIZE + Box_Count_y, Handle, TRUE); // �f�[�^�n���h�����g���ĉ摜��`��
		}
	
	//�m�F�p�[�e�ϐ�(��ɍ폜)
	/*-DrawFormatString(0, 20, GetColor(255, 0, 0), "x���W:%d", box[0].x);
	DrawFormatString(80, 20, GetColor(255, 0, 0), "y���W:%d", box[0].y);
	DrawFormatString(0, 40, GetColor(255, 0, 0), "MoveFlg:%d", Box_Move_Flg);
	DrawFormatString(150, 20, GetColor(255, 0, 0), "x�J�E���g:%d", Box_Count_x);
	DrawFormatString(250, 20, GetColor(255, 0, 0), "y�J�E���g:%d", Box_Count_y);*/

	return 0;
}



int Box_End() {
	//����
	return 0;
}