
#include "MAPSelect.h"
#include "Dxlib.h"
#include "Keyboard.h"
#include "Scene_Mgr.h"
#include "StartMenu.h"
#include "MAP.h"

static int y = 100;

MenuElement_t MAPSelectMenuElement[] = {
{ 50, 0 }, // タグの中身の順番で格納される。xに100が、yに100が、nameに"ゲームスタート"が
{ 50, 100 },
{ 50, 200 },
{ 50, 300 },
{ 50, 400 },
{ 350, 0 },
{ 350, 100 },
{ 350, 200 },
{ 350, 300 },
{ 350, 400 },

};

Image_t MAPSelectImage;


static int SelectNum;	//選択してる番号


int MAPSelect_Init() {
	//ここで初期化をする

	SelectNum = 0; // 現在の選択番号
	MAPSelectImage.MAP = LoadGraph("Images/MAP.png");
	MAPSelectImage.On_MAP = LoadGraph("Images/OnMAP.png");

	return 0;
}

int MAPSelect_Dpct() {
	//ここで計算
	//Dqctは毎フレーム呼ばれる

	if (Keyboard_Get(KEY_INPUT_UP) == 1) {
		SelectNum = (SelectNum + (sizeof(MAPSelectMenuElement) / sizeof*(MAPSelectMenuElement))-1) % (sizeof(MAPSelectMenuElement) / sizeof*(MAPSelectMenuElement));	// 現在の選択項目を一つ上にずらす
	}
	if (SelectNum == -1) {
		SelectNum = (sizeof(MAPSelectMenuElement) / sizeof*(MAPSelectMenuElement)) - 1;
	}

	if (Keyboard_Get(KEY_INPUT_DOWN) == 1) {
		SelectNum = (SelectNum + 1) % (sizeof(MAPSelectMenuElement) / sizeof*(MAPSelectMenuElement));	// 現在の選択項目を一つ下にずらす
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



	for (int i = 0; i < sizeof(MAPSelectMenuElement) / sizeof*(MAPSelectMenuElement); i++) {              // メニュー項目数である5個ループ処理
		if (i == SelectNum) {          // 今処理しているのが、選択番号と同じ要素なら

			if (Keyboard_Get(KEY_INPUT_SPACE) == 1) {	//座標が80になっている項目でスペースキーを押すと
														//その項目の中に入る
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
	}
	return 0;
}

int MAPSelect_Draw() {
	//ここで描写
	//こっちも毎フレーム呼ばれますが計算とは別に書きます


	for (int i = 0; i<sizeof(MAPSelectMenuElement) / sizeof*(MAPSelectMenuElement); i++) { // メニュー項目を描画
		if (i != SelectNum)
		{
			DrawGraph(MAPSelectMenuElement[i].x, MAPSelectMenuElement[i].y, MAPSelectImage.MAP, TRUE);
		}
		else
		{
			DrawGraph(MAPSelectMenuElement[i].x, MAPSelectMenuElement[i].y, MAPSelectImage.On_MAP, TRUE);
		}
	}
	DrawFormatString(MAPSelectMenuElement[SelectNum].x-20, MAPSelectMenuElement[SelectNum].y, GetColor(255, 255, 255), "→");
	DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", SelectNum);
	DrawFormatString(0, 20, GetColor(255, 255, 255), "%d", (sizeof(MAPSelectMenuElement) / sizeof*(MAPSelectMenuElement)));
	

	return 0;
}

int MAPSelect_End() {
	//NoScript

	return 0;
}
