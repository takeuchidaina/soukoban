#include "DxLib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Result.h"
#include "UI.h"
#include "StartMenu.h"
#include "Keyboard.h"
#include "Scene_Mgr.h"
#include "MAP.h"

MenuElement_t ResultMenuElement[MENU_ELEMENT_MAX]{
	{50 , 250 },
	{-90 ,330 },
	{50 , 410 }
};

Image_t ResultImage;


//ここで変数を宣言（C++を使わないのでグローバル変数）

static int step_count;
static int SelectNum;
static int Clear_Image_Count;
static int Clear_Image_Flg;
int Number[9];
char NumStr[256];
int Hosuu_x;


int Result_Init() {
	//ここで初期化をする
	step_count = UI_StepCount();
	SelectNum = 0;

	ResultImage.Clear_RD = LoadGraph("Images/CLEAR_RD.png");
	ResultImage.Clear_YER = LoadGraph("Images/CLEAR_YER.png");
	ResultImage.Step = LoadGraph("Images/Step.png");
	ResultImage.Steped = LoadGraph("Images/Steped.png");
	ResultImage.Back = LoadGraph("Images/Back.png");
	ResultImage.On_Back = LoadGraph("Images/OnBack.png");
	ResultImage.NextStage = LoadGraph("Images/NextStage.png");
	ResultImage.On_NextStage = LoadGraph("Images/OnNextStage.png");
	ResultImage.End = LoadGraph("Images/End.png");
	ResultImage.On_End = LoadGraph("Images/OnEnd.png");

	static int Clear_Image_Count = 0;
	static int Clear_Image_Flg = 0;

	Number[9] = LoadDivGraph("Images/OnNumber.png",10,10,1,MAP_SIZE,MAP_SIZE,Number);
	Hosuu_x = 0;

	return 0;
}

int Result_Dpct() {
	//ここで計算
	//Dqctは毎フレーム呼ばれる
	if (Keyboard_Get(KEY_INPUT_UP) == 1) {
		SelectNum = (SelectNum - 1) % 3;	// 現在の選択項目を一つ上にずらす
	}
	if (SelectNum == -1) {
		SelectNum = MENU_ELEMENT_MAX - 1;
	}

	if (Keyboard_Get(KEY_INPUT_DOWN) == 1) {
		SelectNum = (SelectNum + 1) % 3;	// 現在の選択項目を一つ下にずらす
	}
	for (int i = 0; i < MENU_ELEMENT_MAX; i++) {
		if (i == SelectNum) {          // 今処理しているのが、選択番号と同じ要素なら
			if (Keyboard_Get(KEY_INPUT_SPACE) == 1) {	//座標が80になっている項目でスペースキーを押すと
														//その項目の中に入る
				int tmp;
				switch (i) {
				case 0:
					//次のステージへ
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
					DxLib_End(); // DXライブラリ終了処理
					exit(0);
					break;
				}
			}
		}

	}

	//クリアの点滅速度
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

	//int型からchar型へ変換
	snprintf(NumStr,256, "%d", step_count);

	if (step_count < 10)
	{
		Hosuu_x = 380;
	}
	else if (step_count >= 10 && step_count <= 100)
	{
		Hosuu_x = 316;
	}
	else if (step_count >= 100)
	{
		Hosuu_x = 252;
	}

	return 0;
}

int Result_Draw() {
	//ここで描写
	//こっちも毎フレーム呼ばれますが計算とは別に書きます

	//CLEAR
	if (Clear_Image_Flg != true)
	{
		DrawGraph(20,20, ResultImage.Clear_RD, TRUE);  //赤色
	}
	else
	{
		DrawGraph(20,20, ResultImage.Clear_YER, TRUE);  //黄色
	}

	//かかった歩数
	DrawExtendGraph(150, 100,500,150, ResultImage.Step, TRUE);
	DrawExtendGraph(450, 170,600,220+1, ResultImage.Steped, TRUE);

	//歩数
	for (int i = 0; i < strlen(NumStr); i++)
	{
			DrawGraph(Hosuu_x - i * -MAP_SIZE, 150, Number[NumStr[i] - '0'], TRUE);
	}

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
	//ここで終了処理
	return 0;
}