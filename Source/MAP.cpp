// マップ表示基本
#include "DxLib.h"
#include "MAP.h"
#include "Box.h"
#include "Player.h"


FILE *fp;
static int i, j = 0;
char buf[256];
int map[10][10];
int px, py;
int Boxcnt;
S_Box Box;


// マップデータ
int MapData[MAP_HEIGHT][MAP_WIDTH] =

{ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 1, 0, 1, 1, 1, 1, 1, 1, 0 },
{ 0, 1, 0, 1, 1, 0, 0, 0, 1, 0 },
{ 0, 1, 1, 1, 1, 0, 0, 0, 1, 0 },
{ 0, 1, 0, 1, 0, 0, 0, 0, 1, 0 },
{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };


/*
// マップのデータ
void Map_Data(int *Map, int MAP_W, int MAP_H) {

	fp = fopen("test.txt", "r"); 	//テキストファイルを開く

}
*/

int Map_Data(int x, int y) {
	return MapData[y][x];
}

//プレイヤーの初期x座標を受け取る
int Map_Player_Pos_Init_x() {

	return px;

}

//プレイヤーの初期y座標を受け取る
int Map_Player_Pos_Init_y() {

	return py;

}

//Boxの個数を受け取る
int Map_Box_Count_Init() {

	return Boxcnt;

}

	int MAP_Init() {

		//ここで初期化をする
		px = 1;
	    py = 1;

		Boxcnt = 1;
		return 0;
	}

	int MAP_Dpct() {
		//ここで計算
		//Dqctは毎フレーム呼ばれる

		return 0;
	}

	int MAP_Draw() {
		//ここで描写
		//こっちも毎フレーム呼ばれますが計算とは別に書きます

		// マップを描く
		for (i = 0; i < MAP_HEIGHT; i++)
		{
			for (j = 0; j < MAP_WIDTH; j++)
			{
				if (MapData[i][j] == 1)
				{
					DrawBox(j * MAP_SIZE, i * MAP_SIZE,
						j * MAP_SIZE + MAP_SIZE, i * MAP_SIZE + MAP_SIZE,
						GetColor(255, 255, 255), TRUE);
				}
			}
		}

		return 0;
	}

	int MAP_End() {
		//無し
		return 0;
	}