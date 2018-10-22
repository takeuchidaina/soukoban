#include "DxLib.h"
#include "Result.h"
#include "UI.h"
#include "StartMenu.h"
#include "Keyboard.h"
#include "Scene_Mgr.h"
#include "MAP.h"


MenuElement_t ResultMenuElement[MENU_ELEMENT_MAX]{
	{50 , 300 },
	{-90 , 350 },
	{50 , 400 }
};

Image_t ResultImage;


//�����ŕϐ���錾�iC++���g��Ȃ��̂ŃO���[�o���ϐ��j

static int step_count;
static int SelectNum;
static int Clear_Image_Count;
static int Clear_Image_Flg;


int Result_Init() {
	//�����ŏ�����������
	step_count = UI_StepCount();
	SelectNum = 0;

	ResultImage.Clear_RD = LoadGraph("Images/CLEAR_RD.png");
	ResultImage.Clear_YER = LoadGraph("Images/CLEAR_YER.png");
	ResultImage.Step = LoadGraph("Images/Step.png");
	ResultImage.Steped = LoadGraph("Images/Steped.png");
	ResultImage.Number = LoadGraph("Images/Number.png");
	ResultImage.Back = LoadGraph("Images/Back.png");
	ResultImage.On_Back = LoadGraph("Images/OnBack.png");
	ResultImage.NextStage = LoadGraph("Images/NextStage.png");
	ResultImage.On_NextStage = LoadGraph("Images/OnNextStage.png");
	ResultImage.End = LoadGraph("Images/End.png");
	ResultImage.On_End = LoadGraph("Images/OnEnd.png");

	static int Clear_Image_Count = 0;
	static int Clear_Image_Flg = 0;

	return 0;
}

int Result_Dpct() {
	//�����Ōv�Z
	//Dqct�͖��t���[���Ă΂��
	if (Keyboard_Get(KEY_INPUT_UP) == 1) {
		SelectNum = (SelectNum - 1) % 3;	// ���݂̑I�����ڂ����ɂ��炷
	}
	if (SelectNum == -1) {
		SelectNum = MENU_ELEMENT_MAX - 1;
	}

	if (Keyboard_Get(KEY_INPUT_DOWN) == 1) {
		SelectNum = (SelectNum + 1) % 3;	// ���݂̑I�����ڂ�����ɂ��炷
	}
	for (int i = 0; i < MENU_ELEMENT_MAX; i++) {
		if (i == SelectNum) {          // ���������Ă���̂��A�I��ԍ��Ɠ����v�f�Ȃ�
			if (Keyboard_Get(KEY_INPUT_SPACE) == 1) {	//���W��80�ɂȂ��Ă��鍀�ڂŃX�y�[�X�L�[��������
														//���̍��ڂ̒��ɓ���
				int tmp;
				switch (i) {
				case 0:
					//���̃X�e�[�W��
					tmp = MAP_GetHandleflag();
					if (tmp == MAP_MAX) {
						Scene_Mgr_ChangeScene(E_Scene_StartMenu);
					}
					else {
						MAP_SetHandleflag(tmp + 1);
						Scene_Mgr_ChangeScene(E_Scene_Game);
					}
					break;
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

	}

	//�N���A�̓_�ő��x
	if (Clear_Image_Flg != true)
	{
		Clear_Image_Count++;
		if (Clear_Image_Count >= 75) {
			Clear_Image_Flg = true;
		}
	}
	else
	{
		Clear_Image_Count--;
		if (Clear_Image_Count <= 0) {
			Clear_Image_Flg = false;
		}
	}

	return 0;
}

int Result_Draw() {
	//�����ŕ`��
	//�����������t���[���Ă΂�܂����v�Z�Ƃ͕ʂɏ����܂�

	//CLEAR
	if (Clear_Image_Flg != true)
	{
		DrawGraph(20,20, ResultImage.Clear_RD, TRUE);  //�ԐF
	}
	else
	{
		DrawGraph(20,20, ResultImage.Clear_YER, TRUE);  //���F
	}

	//������������
	DrawGraph(50, 100, ResultImage.Step, TRUE);
	DrawGraph(150, 200, ResultImage.Steped, TRUE);

	switch (SelectNum)
	{
	case 0:
		DrawGraph(ResultMenuElement[0].x, ResultMenuElement[0].y, ResultImage.On_NextStage, TRUE);
		DrawGraph(ResultMenuElement[1].x, ResultMenuElement[1].y, ResultImage.Back, TRUE);
		DrawGraph(ResultMenuElement[2].x, ResultMenuElement[2].y, ResultImage.End, TRUE);

		break;
	case 1:
		DrawGraph(ResultMenuElement[0].x, ResultMenuElement[0].y, ResultImage.NextStage, TRUE);
		DrawGraph(ResultMenuElement[1].x, ResultMenuElement[1].y, ResultImage.On_Back, TRUE);
		DrawGraph(ResultMenuElement[2].x, ResultMenuElement[2].y, ResultImage.End, TRUE);

		break;
	case 2:
		DrawGraph(ResultMenuElement[0].x, ResultMenuElement[0].y, ResultImage.NextStage, TRUE);
		DrawGraph(ResultMenuElement[1].x, ResultMenuElement[1].y, ResultImage.Back, TRUE);
		DrawGraph(ResultMenuElement[2].x, ResultMenuElement[2].y, ResultImage.On_End, TRUE);
		break;

	}

	return 0;
}

int Result_End() {
	//�����ŏI������
	return 0;
}