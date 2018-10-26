#pragma once

typedef struct {	//構造体
	int x, y,num;//座標の変数
} MenuElement_t;

//画像用の構造体
typedef struct {
	int Title;
	int Start;
	int On_Start;
	int MAP;
	int On_MAP;
	int End;
	int On_End;
	int BG;
	int Clear_RD;
	int Clear_YER;
	int Step;
	int Steped;
	int Number[10];
	int On_Number[10];
	int Back;
	int On_Back;
	int NextStage;
	int On_NextStage;

} Image_t;

extern int StartMenu_Init();
extern int StartMenu_Dpct();
extern int StartMenu_Draw();
extern int StartMenu_End();