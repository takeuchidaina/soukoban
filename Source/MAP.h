#pragma once

#define MAP_SIZE	64			// マップチップ一つのドットサイズ
#define MAP_WIDTH	10			// マップの幅
#define MAP_HEIGHT	8			// マップの縦長さ

extern int MAP_Init();
extern int MAP_Dpct();
extern int MAP_Draw();
extern int MAP_End();

int Map_Data(int, int);   //マップの配列  Map_data[][]

int Map_Player_Pos_Init_x();   //プレイヤーの初期x座標
int Map_Player_Pos_Init_y();   //プレイヤーの初期y座標
int Map_Box_Count_Init();     //Boxの個数
//int Map_Box_Pos_Init();     //Boxの初期座標
