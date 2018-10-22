#ifndef INCLUDED_MAP
#define INCLUDED_MAP


#define MAP_SIZE	64			// マップチップ一つのドットサイズ
#define MAP_WIDTH	10			// マップの幅
#define MAP_HEIGHT	8			// マップの縦長さ

#define MAP_MAX 3

extern int MAP_Init();
extern int MAP_Dpct();
extern int MAP_Draw();
extern int MAP_End();

int MAP_Data(int, int);   //マップの配列  Map_data[][]

int MAP_Player_Pos_Init_x();   //プレイヤーの初期x座標
int MAP_Player_Pos_Init_y();   //プレイヤーの初期y座標
int MAP_Box_Count_Init();      //Boxの個数
int MAP_Box_Pos_Init_x(int);      //Boxの初期X座標
int MAP_Box_Pos_Init_y(int);	   //Boxの初期Y座標

int MAP_GetHandleflag();
void MAP_SetHandleflag(int);

#endif
