
#include "MAPSelect.h"
#include "Dxlib.h"
#include "Keyboard.h"
#include "Scene_Mgr.h"
#include "StartMenu.h"
#include "MAP.h"

static int y = 100;

MenuElement_t MAPSelectMenuElement[] = {
{ 30,   0, 1 }, // タグの中身の順番で格納される。xに100が、yに100が、nameに"ゲームスタート"が
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


static int SelectNum;	//選択してる番号
//int MAPNumber[9];
char MAPNumStr[256];


int MAPSelect_Init() {
	//ここで初期化をする

	SelectNum = 0; // 現在の選択番号
	MAPSelectImage.MAP = LoadGraph("Images/MAP.png");
	MAPSelectImage.On_MAP = LoadGraph("Images/OnMAP.png");
	MAPSelectImage.Back = LoadGraph("Images/Back.png");
	MAPSelectImage.On_Back = LoadGraph("Images/OnBack.png");
	LoadDivGraph("Images/Number.png", 10, 10, 1, MAP_SIZE, MAP_SIZE, MAPSelectImage.Number);
	LoadDivGraph("Images/OnNumber.png", 10, 10, 1, MAP_SIZE, MAP_SIZE, MAPSelectImage.On_Number);

	return 0;
}

int MAPSelect_Dpct() {
	//ここで計算
	//Dqctは毎フレーム呼ばれる

	if (Keyboard_Get(KEY_INPUT_UP) == 1) {
		// 現在の選択項目を一つ上にずらす
		SelectNum = (SelectNum + (sizeof(MAPSelectMenuElement) / sizeof*(MAPSelectMenuElement))-1) % (sizeof(MAPSelectMenuElement) / sizeof*(MAPSelectMenuElement));	
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


			//文化祭バグ用にMAP選べないようにしています
			if (i != 7 && i != 8 && i != 9) 
			{



				if (Keyboard_Get(KEY_INPUT_SPACE) == 1) {	//座標が80になっている項目でスペースキーを押すと
															//その項目の中に入る
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
	//ここで描写
	//こっちも毎フレーム呼ばれますが計算とは別に書きます

	// メニュー項目を描画
	for (int i = 0; i<sizeof(MAPSelectMenuElement) / sizeof*(MAPSelectMenuElement); i++) 
	{ 
		//変換
		snprintf(MAPNumStr, 256, "%d", MAPSelectMenuElement[i].num);

		//選択されていない項目
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
				//何故か表示されない
				//他の画像なら表示される 　画像はファイルにある　ファイル名は間違えていない　(要塞確認)
				DrawGraph(MAPSelectMenuElement[i].x, MAPSelectMenuElement[i].y, MAPSelectImage.Back, TRUE);

			}

			//数字の処理(Number[]の中身を書く)
			if (MAPSelectMenuElement[i].num >= 0 && MAPSelectMenuElement[i].num <= 9)
			{
				DrawGraph(MAPSelectMenuElement[i].x + 192, MAPSelectMenuElement[i].y, MAPSelectImage.Number[MAPSelectMenuElement[i].num], TRUE);
			}
			else if(i == 9){
				DrawGraph(MAPSelectMenuElement[i].x + 192, MAPSelectMenuElement[i].y, MAPSelectImage.Number[1], TRUE);
				DrawGraph(MAPSelectMenuElement[i].x + 192+32, MAPSelectMenuElement[i].y, MAPSelectImage.Number[0], TRUE);
			}

		}
		//選択項目
		else if(i == SelectNum)
		{
			//MAPと数字の処理
			if (i < 10)
			{
				DrawGraph(MAPSelectMenuElement[i].x, MAPSelectMenuElement[i].y, MAPSelectImage.On_MAP, TRUE);

			}
			//Backの処理
			else
			{
				DrawGraph(MAPSelectMenuElement[i].x, MAPSelectMenuElement[i].y, MAPSelectImage.On_Back, TRUE);
			}

			//数字の処理(Number[]の中身を書く)
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
	//DrawFormatString(MAPSelectMenuElement[SelectNum].x-20, MAPSelectMenuElement[SelectNum].y, GetColor(255, 255, 255), "→");
	//DrawFormatString(0, 0, GetColor(255, 255, 255), "selectnum:%d", SelectNum);
	//DrawFormatString(0, 20, GetColor(255, 255, 255), "配列の数:%d", (sizeof(MAPSelectMenuElement) / sizeof*(MAPSelectMenuElement)));
	
	return 0;
}

int MAPSelect_End() {
	//NoScript

	return 0;
}
