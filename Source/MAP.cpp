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
char c1, c2;				//MAPとPlayer,Boxに使うchar
int MAP[MAP_HEIGHT][MAP_WIDTH];  //マップ
int px, py;					//受け取るプレイヤーの変数
int Box_Count;				//受け取るBoxの変数;
static int Box_Pos_x[5];		//受け取るBoxのx座標変数
static int Box_Pos_y[5];		//受け取るBoxのy座標変数
int lflag;
//5はdefineかconstで定義すべき
//むしろ構造体を共通すべき


//プレイヤーの初期x座標を受け取る
int MAP_Player_Pos_Init_x(){

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

//Boxの初期X座標
int MAP_Box_Pos_Init_x(int num) {

	return Box_Pos_x[num];
}

//Boxの初期Y座標
int MAP_Box_Pos_Init_y(int num) {

	return Box_Pos_y[num];
}

//初期化
int MAP_Init() {
	memset(MAP, -1, sizeof(MAP));
	px = px;			//受け取ったプレイヤーのx座標を初期化
	py = py;			//受け取ったプレイヤーのy座標を初期化
	Box_Count = 1;	//受け取ったBoxの数の初期化
//	Box_Pos_x = 5;	//受け取ったBoxのx座標の初期化
//	Box_Pos_y = 5;	//受け取ったBoxのy座標の初期化

	// MAPの読み込み
	FileHandle = FileRead_open("MAP/MAP_01.csv");	// 一行読み込み
													// ファイルの終端が来るまで表示する
	if (FileHandle == -1) {

		DrawFormatString(100, 220, GetColor(255, 0, 0), "erararara");
		WaitKey();
	}

	while (FileRead_eof(FileHandle) == 0) {			// 一行読み込み

		//c1 = MAPのchar
		c1 = FileRead_getc(FileHandle);		//1文字読み込む
		if ('0' <= c1 && c1 <= '9') {		//もし0～9だったら
			MAP[i][j] = c1 - '0';				//MAPに代入
		}
		else if (c1 == ',') {				//もし","を読み込んだら
			j++;							//右の数字を読み込む
		}
		else if (c1 == '\n') {					//もし"\n"を読み込んだら
			j = 0;							//右に行くのをやめる
			i++;							//次の行に行く
		}
	}

	// ファイルを閉じる
	FileRead_close(FileHandle);

	
	// Playerの座標読み込み
	FileHandle = FileRead_open("MAP/MAP_01.txt");	//1行読み込み
													// ファイルの終端が来るまで表示する
	if (FileHandle == -1) {

		DrawFormatString(100, 220, GetColor(255, 0, 0), "エラー");
		WaitKey();
	}

	//c2 = PlayerとBoxのchar
	
	c2 = FileRead_getc(FileHandle);		//1文字読み込む	
	px = c2 - '0';				    //PlayerのX座標に代入
	
	FileRead_getc(FileHandle);

	c2 = FileRead_getc(FileHandle);						//右の数字を読み込む
	py = c2 - '0';

	FileRead_getc(FileHandle);

	
	Box_Count = 0;

	
	while (1) {
		FileRead_getc(FileHandle);
		if (c2 == EOF)break;
		c2 = FileRead_getc(FileHandle);
		if (c2 == EOF)break;
		Box_Pos_x[Box_Count] = c2 - '0';;
		
		FileRead_getc(FileHandle);
		if (c2 == EOF)break;
		c2 = FileRead_getc(FileHandle);
		if (c2 == EOF)break;
		Box_Pos_y[Box_Count] = c2 - '0';;
		FileRead_getc(FileHandle);
		if (c2 == EOF)break;
		Box_Count++;
	}
	
	
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