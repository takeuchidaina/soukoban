#pragma once

typedef struct {	//構造体
	int x, y;  //座標の変数
} MenuElement_t;

//画像用の構造体
typedef struct {
	int Title;
	int Start;
	int On_Start;
	int Stage;
	int On_Stage;
	int End;
	int On_End;
	int BG;
} Image_t;

extern int StartMenu_Init();
extern int StartMenu_Dpct();
extern int StartMenu_Draw();
extern int StartMenu_End();