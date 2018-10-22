
#include "MAPSelect.h"
#include "Dxlib.h"
#include "Keyboard.h"
#include "Scene_Mgr.h"
#include "StartMenu.h"
#include "MAP.h"

static int y = 100;

MenuElement_t MAPSelectMenuElement[] = {
{ 100, 100, "MAP1" }, // �^�O�̒��g�̏��ԂŊi�[�����Bx��100���Ay��100���Aname��"�Q�[���X�^�[�g"��
{ 100, 150, "MAP2" },
{ 100, 200, "MAP3" },
{ 100, 250, "MAP4" },
{ 100, 300, "MAP5" },
{ 300, 100, "MAP6" },
{ 300, 150, "MAP7" },
{ 300, 200, "MAP8" },
{ 300, 250, "MAP9" },
{ 300, 300, "MAP10" },
{ 300, 350, "�߂�" },

};

static int SelectNum;	//�I�����Ă�ԍ�

int MAPSelect_Init() {
	//�����ŏ�����������

	SelectNum = 0; // ���݂̑I��ԍ�

	return 0;
}

int MAPSelect_Dpct() {
	//�����Ōv�Z
	//Dqct�͖��t���[���Ă΂��

	if (Keyboard_Get(KEY_INPUT_UP) == 1) {
		SelectNum = (SelectNum + (sizeof(MAPSelectMenuElement) / sizeof*(MAPSelectMenuElement))-1) % (sizeof(MAPSelectMenuElement) / sizeof*(MAPSelectMenuElement));	// ���݂̑I�����ڂ����ɂ��炷
	}
	if (SelectNum == -1) {
		SelectNum = (sizeof(MAPSelectMenuElement) / sizeof*(MAPSelectMenuElement)) - 1;
	}

	if (Keyboard_Get(KEY_INPUT_DOWN) == 1) {
		SelectNum = (SelectNum + 1) % (sizeof(MAPSelectMenuElement) / sizeof*(MAPSelectMenuElement));	// ���݂̑I�����ڂ�����ɂ��炷
	}

	if (Keyboard_Get(KEY_INPUT_RIGHT) == 1 || Keyboard_Get(KEY_INPUT_LEFT) == 1) {
		if (SelectNum < (sizeof(MAPSelectMenuElement) / sizeof*(MAPSelectMenuElement)) / 2) {
			SelectNum += (sizeof(MAPSelectMenuElement) / sizeof*(MAPSelectMenuElement)) / 2;
		}
		else if (SelectNum < (sizeof(MAPSelectMenuElement) / sizeof*(MAPSelectMenuElement)) - 1) {
			SelectNum -= (sizeof(MAPSelectMenuElement) / sizeof*(MAPSelectMenuElement)) / 2;
		}
		else {
		}
	}
	/*
	if (Keyboard_Get(KEY_INPUT_LEFT) == 1) {
		if (SelectNum < (sizeof(MAPSelectMenuElement) / sizeof*(MAPSelectMenuElement)) - 1) {
			SelectNum += (sizeof(MAPSelectMenuElement) / sizeof*(MAPSelectMenuElement)) / 2;
		}
		else if (SelectNum < (sizeof(MAPSelectMenuElement) / sizeof*(MAPSelectMenuElement)) / 2) {
			SelectNum += (sizeof(MAPSelectMenuElement) / sizeof*(MAPSelectMenuElement)) / 2;
		}
		else {
		}
	}
	*/



	for (int i = 0; i < sizeof(MAPSelectMenuElement) / sizeof*(MAPSelectMenuElement); i++) {              // ���j���[���ڐ��ł���5���[�v����
		if (i == SelectNum) {          // ���������Ă���̂��A�I��ԍ��Ɠ����v�f�Ȃ�
		//	MAPSelectMenuElement[i].x = 80; // ���W��80�ɂ���
			if (Keyboard_Get(KEY_INPUT_SPACE) == 1) {	//���W��80�ɂȂ��Ă��鍀�ڂŃX�y�[�X�L�[��������
														//���̍��ڂ̒��ɓ���
				switch (i) {

				case (sizeof(MAPSelectMenuElement) / sizeof*(MAPSelectMenuElement))-1 :
					Scene_Mgr_ChangeScene(E_Scene_StartMenu);
					break;
				default:
					MAP_SetHandleflag(i + 1);
					Scene_Mgr_ChangeScene(E_Scene_Game);
					break;
				}
			}
		}
		else {                     // ���������Ă���̂��A�I��ԍ��ȊO�Ȃ�
		//	MAPSelectMenuElement[i].x = 100;// ���W��100�ɂ���
		}
	}
	return 0;
}

int MAPSelect_Draw() {
	//�����ŕ`��
	//�����������t���[���Ă΂�܂����v�Z�Ƃ͕ʂɏ����܂�


	for (int i = 0; i<sizeof(MAPSelectMenuElement) / sizeof*(MAPSelectMenuElement); i++) { // ���j���[���ڂ�`��
		DrawFormatString(MAPSelectMenuElement[i].x, MAPSelectMenuElement[i].y, GetColor(255, 255, 255), MAPSelectMenuElement[i].name);
	}
	DrawFormatString(MAPSelectMenuElement[SelectNum].x-20, MAPSelectMenuElement[SelectNum].y, GetColor(255, 255, 255), "��");
	DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", SelectNum);
	DrawFormatString(0, 20, GetColor(255, 255, 255), "%d", (sizeof(MAPSelectMenuElement) / sizeof*(MAPSelectMenuElement)));
	

	return 0;
}

int MAPSelect_End() {
	//NoScript

	return 0;
}
