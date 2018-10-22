
#include "StartMenu.h"
#include "Dxlib.h"
#include "Keyboard.h"
#include "Scene_Mgr.h"

MenuElement_t MenuElement[3] = {
{ 40, 200}, // タグの中身の順番で格納される。xに100が、yに100が
{ 60, 300},
{ 50, 400},
};

Image_t Image;

static int SelectNum;	//選択してる番号

int StartMenu_Init() {
	//ここで初期化をする
	
	 SelectNum = 0; // 現在の選択番号
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
	//ここで計算
	//Dqctは毎フレーム呼ばれる

	if (Keyboard_Get(KEY_INPUT_UP) == 1) {
		SelectNum = (SelectNum+ sizeof(MenuElement)/sizeof*(MenuElement)-1) % 3;	// 現在の選択項目を一つ上にずらす
	}

	if (Keyboard_Get(KEY_INPUT_DOWN) == 1) {
		SelectNum = (SelectNum + 1) % 3;	// 現在の選択項目を一つ下にずらす
	}
	for (int i = 0; i<3; i++) {              // メニュー項目数である5個ループ処理
		if (i == SelectNum) {          // 今処理しているのが、選択番号と同じ要素なら
			//MenuElement[i].x = 80; // 座標を80にする
			if (Keyboard_Get(KEY_INPUT_SPACE) == 1) {	//座標が80になっている項目でスペースキーを押すと
			//その項目の中に入る
				switch (i) {
					case 0:
						Scene_Mgr_ChangeScene(E_Scene_Game);
						break;
					case 1:
						Scene_Mgr_ChangeScene(E_Scene_MAPSelect);
						break;
					case 2:
						Scene_Mgr_End();
						DxLib_End(); // DXライブラリ終了処理
						exit(0);
						break;
				}
			}
		}
	}
	return 0;
	}

int StartMenu_Draw() {
	//ここで描写
	//こっちも毎フレーム呼ばれますが計算とは別に書きます
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
