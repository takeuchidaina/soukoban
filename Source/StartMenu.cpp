
#include "StartMenu.h"
#include "Dxlib.h"
#include "Keyboard.h"
#include "Scene_Mgr.h"

MenuElement_t MenuElement[3] = {
{ 40, 200}, // �^�O�̒��g�̏��ԂŊi�[�����Bx��100���Ay��100��
{ 60, 300},
{ 50, 400},
};

Image_t Image;

static int SelectNum;	//�I�����Ă�ԍ�

int StartMenu_Init() {
	//�����ŏ�����������
	
	 SelectNum = 0; // ���݂̑I��ԍ�
	 Image.Title = LoadGraph("Images/Title.png");
	 Image.Start = LoadGraph("Images/Start.png");
	 Image.Stage = LoadGraph("Images/MAP.png");
	 Image.End = LoadGraph("Images/End.png");

	 Image.On_Start = LoadGraph("Images/OnStart.png");
	 Image.On_Stage = LoadGraph("Images/OnMAP.png");
	 Image.On_End = LoadGraph("Images/OnEnd.png");

	 Image.BG = LoadGraph("Images/BackGround.png");
	
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
			//MenuElement[i].x = 80; // ���W��80�ɂ���
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
	}
	return 0;
	}

int StartMenu_Draw() {
	//�����ŕ`��
	//�����������t���[���Ă΂�܂����v�Z�Ƃ͕ʂɏ����܂�
	DrawGraph(0, 0, Image.BG, TRUE);
	DrawGraph(50, 50, Image.Title, TRUE);
	DrawFormatString(500, 700, GetColor(255, 0, 0), "SelectNum:%d", SelectNum);
	switch (SelectNum)
	{
	case 0:
		DrawGraph(MenuElement[0].x, MenuElement[0].y, Image.On_Start, TRUE);
		DrawGraph(MenuElement[1].x, MenuElement[1].y, Image.Stage, TRUE);
		DrawGraph(MenuElement[2].x, MenuElement[2].y, Image.End, TRUE);
		break;
	case 1:
	case -1:
		DrawGraph(MenuElement[0].x, MenuElement[0].y, Image.Start, TRUE);
		DrawGraph(MenuElement[1].x, MenuElement[1].y, Image.On_Stage, TRUE);
		DrawGraph(MenuElement[2].x, MenuElement[2].y, Image.End, TRUE);
		break;
	case 2:
	case -2:
		DrawGraph(MenuElement[0].x, MenuElement[0].y, Image.Start, TRUE);
		DrawGraph(MenuElement[1].x, MenuElement[1].y, Image.Stage, TRUE);
		DrawGraph(MenuElement[2].x, MenuElement[2].y, Image.On_End, TRUE);
		break;

	}

	return 0;
}

int StartMenu_End() {
	//NoScript

	return 0;
}
