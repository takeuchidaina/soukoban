#include "DxLib.h"
#include "UI.h"
#include "Keyboard.h"
#include "Player.h"
#include "Box.h"
#include "Scene_Mgr.h"


#define HISTORY_MAX 256

//ここで変数を宣言（C++を使わないのでグローバル変数）
S_History History[HISTORY_MAX];
int StepCount;


int UI_Init() {
	//ここで初期化をする
	memset( History , 0 , sizeof(History) );
	StepCount = 0 ;
	for (int i = 0; i < HISTORY_MAX; i++) {
		History[i].Player_Drct = E_Drct_None;
		History[i].Box_Drct = E_Drct_None;
		History[i].Boxnum = -1;
	}
	return 0;
}

int UI_Dpct() {
	//ここで計算
	//Dqctは毎フレーム呼ばれる
	if (Keyboard_Get(KEY_INPUT_BACK) == 1 && Player_Move_Flg() != true) {
		if (StepCount > 0) {
			//プレイヤーとボックスを動かす関数
			UI_Player_Move_History(E_Drct_None);
			History[StepCount].Box_Drct = E_Drct_None;
			StepCount--;
			Player_Back_Move(History[StepCount].Player_Drct);
			if (History[StepCount].Box_Drct != E_Drct_None){
				Box_Back_Move(History[StepCount].Box_Drct, History[StepCount].Boxnum);
			}
			
			History[StepCount].Player_Drct = E_Drct_None;
			History[StepCount].Box_Drct = E_Drct_None;
		}
	}
	
	if (Box_Clear() == true) {
		Scene_Mgr_ChangeScene(E_Scene_Result);
		DrawFormatString(200, 440, GetColor(255, 0, 0), "クリア");
	}
	return 0;
}

int UI_Draw() {
	//ここで描写
	//こっちも毎フレーム呼ばれますが計算とは別に書きます
	DrawFormatString(0, 440, GetColor(255, 0, 0), "歩数:%d", StepCount);
	if (Box_Clear() == true) {
		//Scene_Mgr_ChangeScene(E_Scene_result);
		DrawFormatString(200, 440, GetColor(255, 0, 0), "クリア");
	}

	for (int i = 0; i < 20; i++) {
		DrawFormatString(900, 0+i*20, GetColor(122, 122, 255), "Count:%d  PDrct:%d BDrct:%d", i, History[i].Player_Drct , History[i].Box_Drct);
	}


#ifdef _DEBUG

	DrawFormatString(700, 500, GetColor(122, 122, 255), "歩数:%d/向き:%d", StepCount, History[StepCount-1].Player_Drct);

#endif
	return 0;
}

//プレイヤー履歴
int UI_Player_Move_History(E_Drct Drct) {
	History[StepCount].Player_Drct = Drct;
	return 0;
}

//ボックス履歴
int UI_Box_Move_History(E_Drct Drct,int num) {
	History[StepCount].Box_Drct = Drct;
	History[StepCount].Boxnum = num;
	return 0;
}

//歩数カウント追加
int UI_StepCount_MoveOn() {
	StepCount++;
	return 0;
}

//歩数カウントの提示
int UI_StepCount() {
	return StepCount;
}


int UI_End() {
	//無し
	return 0;
}
