
#include "GameMenu.h"
#include "Dxlib.h"
#include "Keyboard.h"
#include "Scene_Mgr.h"
#include "StartMenu.h"


MenuElement_t MenuElement[3] = {
	{ 100, 100, "続行" }, // タグの中身の順番で格納される。xに100が、yに100が、nameに"ゲームスタート"が
{ 100, 200, "やり直し" },
{ 100, 300, "ゲーム終了" },
};


//ここで変数を宣言（C++を使わないのでグローバル変数）


int Template_Init() {
	//ここで初期化をする
	return 0;
}

int Template_Dpct() {
	//ここで計算
	//Dqctは毎フレーム呼ばれる
	return 0;
}

int Template_Draw() {
	//ここで描写
	//こっちも毎フレーム呼ばれますが計算とは別に書きます

	return 0;
}

int Template_End() {
	//ここで終了処理
	return 0;
}