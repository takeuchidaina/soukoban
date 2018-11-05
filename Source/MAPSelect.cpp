
#include "MAPSelect.h"
#include "Dxlib.h"
#include "Keyboard.h"
#include "Scene_Mgr.h"
#include "StartMenu.h"
#include "MAP.h"

static int y = 100;

MenuElement_t MAPSelectMenuElement[] = {
{ 30,   0, 1 }, // �^�O�̒��g�̏��ԂŊi�[�����Bx��100���Ay��100���Aname��"�Q�[���X�^�[�g"��
{ 30,  80, 2 },
{ 30, 160, 3 },
{ 30, 240, 4 },
{ 30, 320, 5 },
{ 330,   0, 6 },
{ 330,  80, 7 },
{ 330, 160, 8 },
{ 330, 240, 9 },
{ 330, 320, 10 },
{ 180, 400,-1 }
};

Image_t MAPSelectImage;


static int SelectNum;	//�I�����Ă�ԍ�
//int MAPNumber[9];
char MAPNumStr[256];


int MAPSelect_Init() {
	//�����ŏ�����������

	SelectNum = 0; // ���݂̑I��ԍ�
	MAPSelectImage.MAP = LoadGraph("Images/MAP.png");
	MAPSelectImage.On_MAP = LoadGraph("Images/OnMAP.png");
	MAPSelectImage.Back = LoadGraph("Images/Back.png");
	MAPSelectImage.On_Back = LoadGraph("Images/OnBack.png");
	LoadDivGraph("Images/Number.png", 10, 10, 1, MAP_SIZE, MAP_SIZE, MAPSelectImage.Number);
	LoadDivGraph("Images/OnNumber.png", 10, 10, 1, MAP_SIZE, MAP_SIZE, MAPSelectImage.On_Number);

	return 0;
}

int MAPSelect_Dpct() {
	//�����Ōv�Z
	//Dqct�͖��t���[���Ă΂��

	if (Keyboard_Get(KEY_INPUT_UP) == 1) {
		// ���݂̑I�����ڂ����ɂ��炷
		SelectNum = (SelectNum + (sizeof(MAPSelectMenuElement) / sizeof*(MAPSelectMenuElement))-1) % (sizeof(MAPSelectMenuElement) / sizeof*(MAPSelectMenuElement));	
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


			//�����Ճo�O�p��MAP�I�ׂȂ��悤�ɂ��Ă��܂�
			if (i != 7 && i != 8 && i != 9) 
			{



				if (Keyboard_Get(KEY_INPUT_SPACE) == 1) {	//���W��80�ɂȂ��Ă��鍀�ڂŃX�y�[�X�L�[��������
															//���̍��ڂ̒��ɓ���
					switch (i) {

					case (sizeof(MAPSelectMenuElement) / sizeof*(MAPSelectMenuElement)) - 1:
						Scene_Mgr_ChangeScene(E_Scene_StartMenu);
						break;
					default:
						MAP_SetHandleflag(i + 1);
						Scene_Mgr_ChangeScene(E_Scene_Game);
						break;
					}
				}



			}
			else if(Keyboard_Get(KEY_INPUT_SPACE) == 1)
			{
				Scene_Mgr_ChangeScene(E_Scene_StartMenu);
			}
		}
	}


	return 0;
}

int MAPSelect_Draw() {
	//�����ŕ`��
	//�����������t���[���Ă΂�܂����v�Z�Ƃ͕ʂɏ����܂�

	// ���j���[���ڂ�`��
	for (int i = 0; i<sizeof(MAPSelectMenuElement) / sizeof*(MAPSelectMenuElement); i++) 
	{ 
		//�ϊ�
		snprintf(MAPNumStr, 256, "%d", MAPSelectMenuElement[i].num);

		//�I������Ă��Ȃ�����
		if (i != SelectNum )
		{
			//MAP
			if (i < 10)
			{
				DrawGraph(MAPSelectMenuElement[i].x, MAPSelectMenuElement[i].y, MAPSelectImage.MAP, TRUE);
			}
			//Back
			else
			{
				//���̂��\������Ȃ�
				//���̉摜�Ȃ�\������� �@�摜�̓t�@�C���ɂ���@�t�@�C�����͊ԈႦ�Ă��Ȃ��@(�v�Ǌm�F)
				DrawGraph(MAPSelectMenuElement[i].x, MAPSelectMenuElement[i].y, MAPSelectImage.Back, TRUE);

			}

			//�����̏���(Number[]�̒��g������)
			if (MAPSelectMenuElement[i].num >= 0 && MAPSelectMenuElement[i].num <= 9)
			{
				DrawGraph(MAPSelectMenuElement[i].x + 192, MAPSelectMenuElement[i].y, MAPSelectImage.Number[MAPSelectMenuElement[i].num], TRUE);
			}
			else if(i == 9){
				DrawGraph(MAPSelectMenuElement[i].x + 192, MAPSelectMenuElement[i].y, MAPSelectImage.Number[1], TRUE);
				DrawGraph(MAPSelectMenuElement[i].x + 192+32, MAPSelectMenuElement[i].y, MAPSelectImage.Number[0], TRUE);
			}

		}
		//�I������
		else if(i == SelectNum)
		{
			//MAP�Ɛ����̏���
			if (i < 10)
			{
				DrawGraph(MAPSelectMenuElement[i].x, MAPSelectMenuElement[i].y, MAPSelectImage.On_MAP, TRUE);

			}
			//Back�̏���
			else
			{
				DrawGraph(MAPSelectMenuElement[i].x, MAPSelectMenuElement[i].y, MAPSelectImage.On_Back, TRUE);
			}

			//�����̏���(Number[]�̒��g������)
			if (MAPSelectMenuElement[i].num >= 0 && MAPSelectMenuElement[i].num <= 9)
			{
				DrawGraph(MAPSelectMenuElement[i].x + 192, MAPSelectMenuElement[i].y, MAPSelectImage.On_Number[MAPSelectMenuElement[i].num], TRUE);
			}
			else if(i == 9)
			{
				DrawGraph(MAPSelectMenuElement[i].x + 192, MAPSelectMenuElement[i].y, MAPSelectImage.On_Number[1], TRUE);
				DrawGraph(MAPSelectMenuElement[i].x + 192 + 32, MAPSelectMenuElement[i].y, MAPSelectImage.On_Number[0], TRUE);
			}


		}
	}
	//DrawFormatString(MAPSelectMenuElement[SelectNum].x-20, MAPSelectMenuElement[SelectNum].y, GetColor(255, 255, 255), "��");
	//DrawFormatString(0, 0, GetColor(255, 255, 255), "selectnum:%d", SelectNum);
	//DrawFormatString(0, 20, GetColor(255, 255, 255), "�z��̐�:%d", (sizeof(MAPSelectMenuElement) / sizeof*(MAPSelectMenuElement)));
	
	return 0;
}

int MAPSelect_End() {
	//NoScript

	return 0;
}
