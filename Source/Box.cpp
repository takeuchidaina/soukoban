#include "Dxlib.h"
#include "Box.h"
#include "Player.h"
#include "MAP.h"
#include "Keyboard.h"

#define OFF 0		//FALSE
#define ON 1		//TRUE
#define LOAD 1		//��
#define WALL 0		//��

static int  i;   //for�Ŏg���悤
int  yousosuu;	 //Box�̌�
int  goal;
int  moveNumber;	//�����Ă锠�̃i���o�[
S_Box box[5];    //�\����
E_Drct Box_Drct;          //�����̊Ǘ�
int Box_Move_Flg = OFF;		//�����������Ȃ���
int Box_Count_x = 0;	//�k���k��������
int Box_Count_y = 0;   // �k���k��������
int Handle;				//// �f�[�^�n���h���i�[�p�ϐ�
int Box_Clear_Flg = OFF;		//�{�b�N�X���S�[���̍��W�ƈ�v���Ă��邩�ǂ����̃t���O
int Box_Back_Flg;			//�{�b�N�X�̍��W����O�ɖ߂�

int Box_Up_Flg = OFF;  //�オ�����ꂽ��(������count�̊Ǘ����s��)
int Box_Down_Flg = OFF;  //���������ꂽ��(������count�̊Ǘ����s��)
int Box_Right_Flg = OFF;  //�E�������ꂽ��(������count�̊Ǘ����s��)
int Box_Left_Flg = OFF;  //���������ꂽ��(������count�̊Ǘ����s��)

int Box_Pos(int *x, int *y, int num) {
	//�{�b�N�X�̈ʒu���}�b�v����Ⴄ

	*x = box[num].x;                             
	*y = box[num].y;

	return 0;
}

bool Box_Clear() {
	Box_Clear_Flg = ON;
	//������CLEAR�t���O��ON�ɂ���
	for (i = 0;i < yousosuu;i++) {
		if (MAP_Data(box[i].x, box[i].y) != 2) {
			Box_Clear_Flg = OFF;
			//������CLEAR�t���O��OFF�ɂ���
		}
	}
	return Box_Clear_Flg;
	//return CLEAR�t���O;	
}

int Box_Move(E_Drct Drct, int num) {
	//�v���C���[����{�b�N�X�ɂ����֓����Ƃ����֐������炤   

	moveNumber = num;
	
	box[num].bx = box[num].x;		//�{�b�N�X�̏���x���W������x���W�Ɉڂ�
	box[num].by = box[num].y;		//�{�b�N�X�̏���y���W������y���W�Ɉڂ�

	switch (Drct) {

	case E_Drct_Up:
			box[num].bx += 0;		//����x���W�𓮂���
			box[num].by += -1;		//����y���W�𓮂���
			Box_Up_Flg = ON;		
			break;
		
	case E_Drct_Right:
			box[num].bx += +1;		//����x���W�𓮂���
			box[num].by += 0;		//����y���W�𓮂���
			Box_Right_Flg = ON;
			break;
		
	case E_Drct_Down:
			box[num].bx += 0;		//����x���W�𓮂���
			box[num].by += +1;		//����y���W�𓮂���
			Box_Down_Flg = ON;
			break;
		
	case E_Drct_Left:
			box[num].bx += -1;		//����x���W�𓮂���
			box[num].by += 0;		//����y���W�𓮂���
			Box_Left_Flg = ON;
			break;
	};

	return 0;
}

int Box_Bectl(int *x, int *y, int num) {
	//���������̃x�N�g���i�����j�����炤
/*
	num = ;

	*x = box[num].x = ;
	*y = box[num].y = ;
*/
	return 0;
}

int Box_Init() {
	//�����ŏ�����������
	
	Handle = LoadGraph("Images/Box.png"); // �摜�����[�h

	yousosuu =  MAP_Box_Count_Init();
	
	
	for (i = 0;i < yousosuu;i++) {
		box[i].x = MAP_Box_Pos_Init_x(i);
		box[i].y = MAP_Box_Pos_Init_y(i);
	}
	return 0;
}

/*
int Box_Dbug() {		//����Box_Move()���ĂԂ��߂����̊֐�

	if (Box_Move_Flg == OFF) {
		//��
		if (Keyboard_Get(KEY_INPUT_UP) == 1)   //���������ꂽ��
		{
			Box_Move(E_Drct_Up, 0);
		}
		//��
		if (Keyboard_Get(KEY_INPUT_RIGHT) == 1)   //���������ꂽ��
		{
			Box_Move(E_Drct_Right, 0);
		}
		//��
		if (Keyboard_Get(KEY_INPUT_DOWN) == 1)   //���������ꂽ��
		{
			Box_Move(E_Drct_Down, 0);
		}
		//�E
		if (Keyboard_Get(KEY_INPUT_LEFT) == 1)   //���������ꂽ��
		{
			Box_Move(E_Drct_Left, 0);
		}
	}
	return 0;
}
*/

int Box_Dpct() {		//box�̈ړ��̌v�Z�����Ă���
	//�����Ōv�Z
	//Dqct�͖��t���[���Ă΂��
	if (Box_Up_Flg == ON || Box_Right_Flg == ON || Box_Down_Flg == ON || Box_Left_Flg == ON) {		//�����ꂩ��Box_Flg��ON�ɂȂ��Ă����
		
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
		
		if (Box_Count_y <= -MAP_SIZE+1 || Box_Count_x >= MAP_SIZE-1 || Box_Count_y >= MAP_SIZE-1 || Box_Count_x <= -MAP_SIZE+1)		//count��64�𒴂�����~�߂�
			//if (Box_Count_x >= MAP_SIZE || Box_bCount_y <= -MAP_SIZE || Box_Count_x <= -MAP_SIZE || Box_Count_y >= MAP_SIZE)
		{
			
			box[moveNumber].y = box[moveNumber].by;		//Box_Move�œ�����������x���W��box��x���W�ɖ߂�
			box[moveNumber].x = box[moveNumber].bx;		//Box_Move�œ�����������y���W��box��y���W�ɖ߂�

			/* �e�t���O��OFF(0)�ɂ���*/
	        Box_Count_x = 0;
			Box_Count_y = 0;
			Box_Up_Flg = OFF;
			Box_Right_Flg = OFF;
			Box_Down_Flg = OFF;
			Box_Left_Flg = OFF;
			moveNumber = -1;
		}
	}
	return 0;
}

//�o�b�N�X�y�[�X�������ꂽ��߂� 
int Box_Back_Move(E_Drct Old_Drct , int num) {   

//	yousosuu = MAP_Box_Count_Init();

	moveNumber = num;


	Old_Drct = (E_Drct)((Old_Drct + 2) % 4);

	box[num].bx = box[num].x;		//�{�b�N�X�̏���x���W������x���W�Ɉڂ�
	box[num].by = box[num].y;		//�{�b�N�X�̏���y���W������y���W�Ɉڂ�

	switch (Old_Drct) {

	case E_Drct_Up:
		box[num].bx += 0;		//����x���W�𓮂���
		box[num].by += -1;		//����y���W�𓮂���
		Box_Up_Flg = ON;
		break;

	case E_Drct_Right:
		box[num].bx += +1;		//����x���W�𓮂���
		box[num].by += 0;		//����y���W�𓮂���
		Box_Right_Flg = ON;
		break;

	case E_Drct_Down:
		box[num].bx += 0;		//����x���W�𓮂���
		box[num].by += +1;		//����y���W�𓮂���
		Box_Down_Flg = ON;
		break;

	case E_Drct_Left:
		box[num].bx += -1;		//����x���W�𓮂���
		box[num].by += 0;		//����y���W�𓮂���
		Box_Left_Flg = ON;
		break;
	};

  return 0;

}

int Box_Draw() {
	//�����ŕ`��
	//�����������t���[���Ă΂�܂����v�Z�Ƃ͕ʂɏ����܂�

	yousosuu = MAP_Box_Count_Init();

	for (i = 0; i < yousosuu; i++) {
		if (i != moveNumber) {
			DrawGraph(box[i].x * MAP_SIZE , box[i].y * MAP_SIZE , Handle, TRUE); // �f�[�^�n���h�����g���ĉ摜��`��
					//(box��x���W * map_size(64) + count.x(1�}�X�j, box��y���W * map_size(64) + count.y(1�}�X�j)
		}
		else {
			DrawGraph(box[i].x * MAP_SIZE + Box_Count_x, box[i].y * MAP_SIZE + Box_Count_y, Handle, TRUE); // �f�[�^�n���h�����g���ĉ摜��`��
		}
	}

	//DrawFormatString(250, 80, GetColor(255, 0, 0), "box[0].bx:%d", box[0].bx);
	
	return 0;
}

int Box_End() {
	//����
	return 0;
}

/*box�̈ړ��菇*/

/*
1. box���������A�t���O����������B
2. �{�b�N�X�̕`�ʂ����̃}�X�Ɉړ�����B
3. �{�b�N�X�̕`�ʂ����̃}�X�Ɉړ�������A�{�b�N�X�̍��W�����̎~�܂����n�_�ɂȂ�B�@
		�� �Q�[����ʂł̓{�b�N�X���~�܂��Ă���{�b�N�X�̍��W�����������ƂɂȂ�B�@
*/