#include "DxLib.h"
#include "UI.h"
#include "Keyboard.h"
#include "Player.h"
#include "Box.h"
#include "Scene_Mgr.h"


#define HISTORY_MAX 256

//�����ŕϐ���錾�iC++���g��Ȃ��̂ŃO���[�o���ϐ��j
static S_History History[HISTORY_MAX];
static int StepCount;


int UI_Init() {
	//�����ŏ�����������
//	memset( History , 0 , sizeof(History) );
	int StepCount = 0 ;
	for (int i = 0; i < HISTORY_MAX; i++) {
		History[i].Player_Drct = E_Drct_None;
		History[i].Box_Drct = E_Drct_None;
		History[i].Boxnum = -1;
	}
	return 0;
}

int UI_Dpct() {
	//�����Ōv�Z
	//Dqct�͖��t���[���Ă΂��
	if (Keyboard_Get(KEY_INPUT_BACK) == 1 && Player_Move_Flg() != true) {
		if (StepCount > 0) {
			//�v���C���[�ƃ{�b�N�X�𓮂����֐�
			Player_Back_Move(History[StepCount].Player_Drct);
			if (History[StepCount].Box_Drct != E_Drct_None){
				Box_Back_Move(History[StepCount].Box_Drct, History[StepCount].Boxnum);
			}
			StepCount--;
			History[StepCount].Player_Drct = E_Drct_None;
			History[StepCount].Box_Drct = E_Drct_None;
		}
	}
	
	if (Box_Clear() == true) {
		//Scene_Mgr_ChangeScene(E_Scene_result);
		DrawFormatString(200, 440, GetColor(255, 0, 0), "�N���A");
	}
	return 0;
}

int UI_Draw() {
	//�����ŕ`��
	//�����������t���[���Ă΂�܂����v�Z�Ƃ͕ʂɏ����܂�
	DrawFormatString(0, 440, GetColor(255, 0, 0), "����:%d", StepCount);
	if (Box_Clear() == true) {
		//Scene_Mgr_ChangeScene(E_Scene_result);
		DrawFormatString(200, 440, GetColor(255, 0, 0), "�N���A");
	}

	return 0;
}

//�v���C���[����
int UI_Player_Move_History(E_Drct Drct) {
	History[StepCount].Player_Drct = Drct;
	return 0;
}

//�{�b�N�X����
int UI_Box_Move_History(E_Drct Drct,int num) {
	History[StepCount].Box_Drct = Drct;
	History[StepCount].Boxnum = num;
	return 0;
}

//�����J�E���g�ǉ�
int UI_StepCount_MoveOn() {
	StepCount++;
	return 0;
}


int UI_End() {
	//����
	return 0;
}