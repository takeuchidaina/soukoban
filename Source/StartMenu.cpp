
#include "StartMenu.h"
#include "Dxlib.h"
#include "Keyboard.h"
#include "Scene_Mgr.h"

MenuElement_t MenuElement[3] = {
{ 100, 200 }, // �^�O�̒��g�̏��ԂŊi�[�����Bx��100���Ay��100���Aname��"�Q�[���X�^�[�g"��
{ 100, 300 },
{ 100, 400 }
};

static int SelectNum;	//�I�����Ă�ԍ�
int Title;
int Start;
int Stage;
int End;
int On_Start;
int On_Stage;
int On_End;

int StartMenu_Init() {
	//�����ŏ�����������
	
	 SelectNum = 0; // ���݂̑I��ԍ�
	 Title = LoadGraph("Images/Title.png");
	 Start = LoadGraph("Images/Start.png");
	 Stage = LoadGraph("Images/NextStage.png");
	 End = LoadGraph("Images/End.png");

	 On_Start = LoadGraph("Images/OnStart.png");
	 On_Stage = LoadGraph("Images/OnNextStage.png");
	 On_End = LoadGraph("Images/OnEnd.png");

	return 0;
}

int StartMenu_Dpct() {
	//�����Ōv�Z
	//Dqct�͖��t���[���Ă΂��

	if (Keyboard_Get(KEY_INPUT_UP) == 1) {
		SelectNum = (SelectNum - 1) % 3;	// ���݂̑I�����ڂ����ɂ��炷
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
						//�w���v���ĂȂ��A�w���v��ʍ���Ƃ�����̂��B�ނ���X�e�[�W�Z���N�g���B
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

	DrawGraph(100, 50, Title,TRUE);
	//DrawFormatString(500, 700 ,GetColor(255,0,0), "SelectNum:%d", SelectNum);
	switch (SelectNum)
	{
	case 0: 
		DrawGraph(MenuElement[0].x, MenuElement[0].y, On_Start, TRUE);
		DrawGraph(MenuElement[1].x, MenuElement[1].y, Stage, TRUE);
		DrawGraph(MenuElement[2].x, MenuElement[2].y, End, TRUE);
		break;
	case 1:
	case -1:
		DrawGraph(MenuElement[0].x, MenuElement[0].y, Start, TRUE);
		DrawGraph(MenuElement[1].x, MenuElement[1].y, On_Stage, TRUE);
		DrawGraph(MenuElement[2].x, MenuElement[2].y, End, TRUE);
		break;
	case 2:
	case -2:
		DrawGraph(MenuElement[0].x, MenuElement[0].y, Start, TRUE);
		DrawGraph(MenuElement[1].x, MenuElement[1].y, Stage, TRUE);
		DrawGraph(MenuElement[2].x, MenuElement[2].y, On_End, TRUE);
		break;

	}

	/*
	for (int i = 0; i<3; i++) { // ���j���[���ڂ�`��
		//DrawFormatString(MenuElement[i].x, MenuElement[i].y, GetColor(255, 255, 255), MenuElement[i].name);
	}
	*/
	return 0;
}

int StartMenu_End() {
	//NoScript

	return 0;
}
