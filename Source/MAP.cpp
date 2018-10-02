// マップ表示基本
#include "DxLib.h"
#include "MAP.h"
#include "Box.h"
#include "Player.h"
#define file_name "MAP_01.csv"
#define full_path file_path file_name


int FileHandle, y;
static int i = 0, j = 0;
char buf[256];
char c;
int MAP[MAP_HEIGHT][MAP_WIDTH];  //マップ
int px, py;			//受け取るプレイヤーの変数
int Box_Count;		//受け取るBoxの変数;
static int Box_Pos_x;		//受け取るBoxのx座標変数
static int Box_Pos_y;		//受け取るBoxのy座標変数
int lflag;



//プレイヤーの初期x座標を受け取る
int MAP_Player_Pos_Init_x() {

	return px;		//初期化したプレイヤーのx座標を戻す

}


//プレイヤーの初期y座標を受け取る
int MAP_Player_Pos_Init_y() {

	return py;		//初期化したプレイヤーのy座標を戻す

}

//MAPの座標
int MAP_Data(int x, int y) {

	return MAP[y][x];
}


//Boxの個数を受け取る
int MAP_Box_Count_Init() {

	return Box_Count;

}

//Boxの初期座標
int MAP_Box_Pos_Init_x(int num) {	

	return Box_Pos_x;

}

int MAP_Box_Pos_Init_y(int num) {

	return Box_Pos_y;

}

//初期化
int MAP_Init() {
	memset(MAP, -1, sizeof(MAP));
	px = 1;			//受け取ったプレイヤーのx座標を初期化
	py = 1;			//受け取ったプレイヤーのy座標を初期化
	Box_Count = 1;	//受け取ったBoxの数の初期化
	Box_Pos_x = 5;	//受け取ったBoxのx座標の初期化
	Box_Pos_y = 5;	//受け取ったBoxのy座標の初期化

					// MAP.csv を開く
	FileHandle = FileRead_open("MAP/MAP_01.csv");	// 一行読み込み

												// ファイルの終端が来るまで表示する

	if (FileHandle == -1)
	{
		DrawFormatString(100, 220, GetColor(255, 0, 0), "erararara");
		WaitKey();
	}
	while (FileRead_eof(FileHandle) == 0)
	{
		// 一行読み込み
		//FileRead_gets(String, 256, FileHandle);


		c = FileRead_getc(FileHandle);		//1文字読み込む
		if ('0' <= c && c <= '9') {		//もし0～9だったら
			MAP[i][j] = c - '0';				//MAPに代入
		}
		else if (c == ',') {				//もし","を読み込んだら
			j++;							//右の数字を読み込む
		}
		else if (c == '\n') {					//もし"\n"を読み込んだら
			j = 0;							//右に行くのをやめる
			i++;							//次の行に行く
		}
	}

	/*
		for (i = 0; i < MAP_HEIGHT; i++) {			//iが10になるまで足す
			for (j = 0; j < MAP_WIDTH; j++) {		//jが10になるまで足す
				if (MAP[i][j] != -1) {		//もしMAPが-1と等しくなかったら
					DrawFormatString(j * 10, i * 20, GetColor(255, 255, 255), "%d", MAP[i][j]);
				}	//
			}
			
	}
	*/

	// ファイルを閉じる
	FileRead_close(FileHandle);

	return 0;

}


//計算
int MAP_Dpct() {
	//Dpctは毎フレーム呼ばれる

	return 0;
}


//描写
int MAP_Draw() {
	//こっちも毎フレーム呼ばれるが計算とは別に書きます

	// マップを描く
	for (i = 0; i < MAP_HEIGHT; i++)
	{
		for (j = 0; j < MAP_WIDTH; j++)
		{
			if (MAP[i][j] == 0)
			{
				DrawBox(j * MAP_SIZE, i * MAP_SIZE,
					j * MAP_SIZE + MAP_SIZE, i * MAP_SIZE + MAP_SIZE,
					GetColor(0, 230, 0), TRUE);
			}
			if (MAP[i][j] == 1)
			{
				DrawBox(j * MAP_SIZE, i * MAP_SIZE,
					j * MAP_SIZE + MAP_SIZE, i * MAP_SIZE + MAP_SIZE,
					GetColor(122, 255, 122), TRUE);
				
			}
		}
	}
	//DrawFormatString(100, 200, GetColor(255, 0, 0), "MAP Draw動いてるよん");
	return 0;
}


//終了
int MAP_End() {
	return 0;
}