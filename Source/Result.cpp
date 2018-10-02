#include "DxLib.h"
#include "Result.h"
#include "UI.h"
#include "StartMenu.h"
#include "Keyboard.h"
#include "Scene_Mgr.h"


MenuElement_t ResultMenuElement[MENU_ELEMENT_MAX]{
	{100 , 200 , "���̃X�e�[�W��"},
	{100 , 300 , "�^�C�g���ɖ߂�"},
	{100 , 400 , "�Q�[�����I������"}
};


//�����ŕϐ���錾�iC++���g��Ȃ��̂ŃO���[�o���ϐ��j

static int step_count;
static int SelectNum;


int Result_Init() {
	//�����ŏ�����������
	step_count = UI_StepCount();
	SelectNum = 0;
	return 0;
}

int Result_Dpct() {
	//�����Ōv�Z
	//Dqct�͖��t���[���Ă΂��
	if (Keyboard_Get(KEY_INPUT_UP) == 1) {
		SelectNum = (SelectNum - 1) % 3;	// ���݂̑I�����ڂ����ɂ��炷
	}

	if (Keyboard_Get(KEY_INPUT_DOWN) == 1) {
		SelectNum = (SelectNum + 1) % 3;	// ���݂̑I�����ڂ�����ɂ��炷
	}
	for (int i = 0; i < MENU_ELEMENT_MAX; i++) {
		if (i == SelectNum) {          // ���������Ă���̂��A�I��ԍ��Ɠ����v�f�Ȃ�
			ResultMenuElement[i].x = 80; // ���W��80�ɂ���
			if (Keyboard_Get(KEY_INPUT_SPACE) == 1) {	//���W��80�ɂȂ��Ă��鍀�ڂŃX�y�[�X�L�[��������
														//���̍��ڂ̒��ɓ���
				switch (i) {
				case 1:
					Scene_Mgr_ChangeScene(E_Scene_StartMenu);
					break;
				case 2:
					Scene_Mgr_End();
					DxLib_End(); // DX���C�u�����I������
					exit(0);
					break;
				}
			}
		}
		else {                     // ���������Ă���̂��A�I��ԍ��ȊO�Ȃ�
			ResultMenuElement[i].x = 100;// ���W��100�ɂ���
		}
	}

	return 0;
}

int Result_Draw() {
	//�����ŕ`��
	//�����������t���[���Ă΂�܂����v�Z�Ƃ͕ʂɏ����܂�

	DrawFormatString(100,100, GetColor(255,255,255), "�������������� %d ���ł����I", step_count);

	return 0;
}

int Result_End() {
	//�����ŏI������
	return 0;
}