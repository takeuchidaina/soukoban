
#include "StartMenu.h"
#include "Dxlib.h"
#include "Keyboard.h"
#include "Scene_Mgr.h"

MenuElement_t MenuElement[3] = {
{ 100, 100, "�Q�[���X�^�[�g" }, // �^�O�̒��g�̏��ԂŊi�[�����Bx��100���Ay��100���Aname��"�Q�[���X�^�[�g"��
{ 100, 200, "�X�e�[�W�Z���N�g" },
{ 100, 300, "�Q�[���I��" },
};

static int SelectNum;	//�I�����Ă�ԍ�

int StartMenu_Init() {
	//�����ŏ�����������
	
	 SelectNum = 0; // ���݂̑I��ԍ�
	
	return 0;
}

int StartMenu_Dpct() {
	//�����Ōv�Z
	//Dqct�͖��t���[���Ă΂��

	if (Keyboard_Get(KEY_INPUT_UP) == 1) {
		SelectNum = (SelectNum+ sizeof(MenuElement)/sizeof*(MenuElement)-1) % 3;	// ���݂̑I�����ڂ����ɂ��炷
	}

	if (Keyboard_Get(KEY_INPUT_DOWN) == 1) {
		SelectNum = (SelectNum + 1) % 3;	// ���݂̑I�����ڂ�����ɂ��炷
	}
	for (int i = 0; i<3; i++) {              // ���j���[���ڐ��ł���5���[�v����
		if (i == SelectNum) {          // ���������Ă���̂��A�I��ԍ��Ɠ����v�f�Ȃ�
			MenuElement[i].x = 80; // ���W��80�ɂ���
			if (Keyboard_Get(KEY_INPUT_SPACE) == 1) {	//���W��80�ɂȂ��Ă��鍀�ڂŃX�y�[�X�L�[��������
			//���̍��ڂ̒��ɓ���
				switch (i) {
					case 0:
						Scene_Mgr_ChangeScene(E_Scene_Game);
						break;
					case 1:
						Scene_Mgr_ChangeScene(E_Scene_MAPSelect);
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
			MenuElement[i].x = 100;// ���W��100�ɂ���
		}
	}
	return 0;
	}

int StartMenu_Draw() {
	//�����ŕ`��
	//�����������t���[���Ă΂�܂����v�Z�Ƃ͕ʂɏ����܂�


	for (int i = 0; i<3; i++) { // ���j���[���ڂ�`��
		DrawFormatString(MenuElement[i].x, MenuElement[i].y, GetColor(255, 255, 255), MenuElement[i].name);
	}

	return 0;
}

int StartMenu_End() {
	//NoScript

	return 0;
}
