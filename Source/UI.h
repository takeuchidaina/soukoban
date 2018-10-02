#pragma once

#ifndef INCLUDE_UI
#define INCLUDE_UI
#include "Player.h"
#endif

//UI系関数を使う為のプロトタイプ宣言
extern int UI_Init();
extern int UI_Dpct();
extern int UI_Draw();
extern int UI_End();

//プレイヤー・箱を動かすときに呼び出す
extern int UI_Player_Move_History(E_Drct Drct);
extern int UI_Box_Move_History(E_Drct Drct,int num);
extern int UI_StepCount_MoveOn();


//履歴保存用構造体
typedef struct {
	E_Drct Player_Drct;
	E_Drct Box_Drct;
	int Boxnum;
}S_History;
