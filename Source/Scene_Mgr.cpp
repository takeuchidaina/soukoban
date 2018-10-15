#include "DxLib.h"
#include "Scene_Mgr.h"
#include "Player.h"
#include "StartMenu.h"
#include "Box.h"
#include "MAP.h"
#include "UI.h"
#include "Result.h"


static E_Scene Sceneflag = E_Scene_StartMenu;		//今のシーン
static E_Scene n_Sceneflag = E_Scene_None;			//次のシーン

static void Scene_Mgr_Init_Module(E_Scene scene);	//指定モジュールを初期化する
static void Scene_Mgr_End_Module(E_Scene scene);	//指定モジュールの終了処理を行う


//init
void Scene_Mgr_Init() {
	Scene_Mgr_Init_Module(Sceneflag);
}


//Update
void Scene_Mgr_Dpct() {
	if (n_Sceneflag != E_Scene_None) {		//次のシーンがセットされていたら
		Scene_Mgr_End_Module(Sceneflag);	//現在のシーンの終了処理を実行
		Sceneflag = n_Sceneflag;			//次のシーンを現在のシーンにセット
		n_Sceneflag = E_Scene_None;			//次のシーン情報をクリア
		Scene_Mgr_Init_Module(Sceneflag);	//現在のシーンを初期化
	}


	switch (Sceneflag) {
	case E_Scene_StartMenu:
		//スタートメニュー
		StartMenu_Dpct();
		break;
	case E_Scene_Game:
		//ゲーム画面
		MAP_Dpct();
		UI_Dpct();
		Player_Dpct();
		Box_Dpct();

		break;
	case E_Scene_Result:
		Result_Dpct();
		break;
	case E_Scene_GameMenu:
		//ゲームメニュー
		break;
	}
}


//Drow
void Scene_Mgr_Draw() {
	switch (Sceneflag) {
	case E_Scene_StartMenu:
		//スタートメニュー
		StartMenu_Draw();
		DrawFormatString(0, 00, GetColor(255, 255, 255), "スタートメニュー");
		break;
	case E_Scene_Game:
		//ゲーム画面
		MAP_Draw();
		Player_Draw();
		Box_Draw();
		UI_Draw();

		DrawFormatString(0, 00, GetColor(255, 255, 255), "ゲーム画面");

		break;
	case E_Scene_Result:
		Result_Draw();
		break;
	case E_Scene_GameMenu:
		//ゲームメニュー
		DrawFormatString(0, 00, GetColor(255, 255, 255), "ゲームメニュー");
		break;
	}
}

//End
void Scene_Mgr_End() {
	Scene_Mgr_End_Module(Sceneflag);
}

//シーン変更
void Scene_Mgr_ChangeScene(E_Scene NextScene) {
	n_Sceneflag = NextScene;
}

//指定モジュールの初期化をする
static void Scene_Mgr_Init_Module(E_Scene scene) {
	switch (Sceneflag) {
	case E_Scene_StartMenu:
		//スタートメニュー
		StartMenu_Init();
		break;
	case E_Scene_Game:
		//ゲーム画面
		MAP_Init();
		Player_Init();
		Box_Init();
		UI_Init();

		break;
	case E_Scene_Result:
		Result_Init();
		break;
	case E_Scene_GameMenu:
		//ゲームメニュー
		break;
	}

}

//指定モジュールの終了処理を行う
static void Scene_Mgr_End_Module(E_Scene scene) {
	switch (Sceneflag) {
	case E_Scene_StartMenu:
		//スタートメニュー
		StartMenu_End();
		break;
	case E_Scene_Game:
		//ゲーム画面
		MAP_End();
		Player_End();
		Box_End();
		UI_End();

		break;
	case E_Scene_Result:
		Result_End();
		break;
	case E_Scene_GameMenu:
		//ゲームメニュー
		break;
	}

}
