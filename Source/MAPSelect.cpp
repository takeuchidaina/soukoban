
#include "MAPSelect.h"
#include "Dxlib.h"
#include "Keyboard.h"
#include "Scene_Mgr.h"
#include "StartMenu.h"
#include "MAP.h"

static int y = 100;

MenuElement_t MAPSelectMenuElement[] = {
{ 100, 100, "MAP1" }, // タグの中身の順番で格納される。xに100が、yに100が、nameに"ゲームスタート"が
{ 100, 150, "MAP2" },
{ 100, 200, "MAP3" },
{ 100, 250, "MAP4" },
{ 100, 300, "MAP5" },
{ 300, 100, "MAP6" },
{ 300, 150, "MAP7" },
{ 300, 200, "MAP8" },
{ 300, 250, "MAP9" },
{ 300, 300, "MAP10" },
{ 300, 350, "戻る" },

};

static int SelectNum;	//選択してる番号

int MAPSelect_Init() {
	//ここで初期化をする

	SelectNum = 0; // 現在の選択番号

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
		//	MAPSelectMenuElement[i].x = 80; // 座標を80にする
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
		else {                     // 今処理しているのが、選択番号以外なら
		//	MAPSelectMenuElement[i].x = 100;// 座標を100にする
		}
	}
	return 0;
}

int MAPSelect_Draw() {
	//ここで描写
	//こっちも毎フレーム呼ばれますが計算とは別に書きます


	for (int i = 0; i<sizeof(MAPSelectMenuElement) / sizeof*(MAPSelectMenuElement); i++) { // メニュー項目を描画
		DrawFormatString(MAPSelectMenuElement[i].x, MAPSelectMenuElement[i].y, GetColor(255, 255, 255), MAPSelectMenuElement[i].name);
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
