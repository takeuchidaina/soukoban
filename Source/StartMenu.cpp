
#include "StartMenu.h"
#include "Dxlib.h"
#include "Keyboard.h"
#include "Scene_Mgr.h"

MenuElement_t MenuElement[3] = {
{ 100, 100, "ゲームスタート" }, // タグの中身の順番で格納される。xに100が、yに100が、nameに"ゲームスタート"が
{ 100, 200, "ステージセレクト" },
{ 100, 300, "ゲーム終了" },
};

static int SelectNum;	//選択してる番号

int StartMenu_Init() {
	//ここで初期化をする
	
	 SelectNum = 0; // 現在の選択番号
	
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
			MenuElement[i].x = 80; // 座標を80にする
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
		else {                     // 今処理しているのが、選択番号以外なら
			MenuElement[i].x = 100;// 座標を100にする
		}
	}
	return 0;
	}

int StartMenu_Draw() {
	//ここで描写
	//こっちも毎フレーム呼ばれますが計算とは別に書きます


	for (int i = 0; i<3; i++) { // メニュー項目を描画
		DrawFormatString(MenuElement[i].x, MenuElement[i].y, GetColor(255, 255, 255), MenuElement[i].name);
	}

	return 0;
}

int StartMenu_End() {
	//NoScript

	return 0;
}
