#include "Dxlib.h"
#include "Box.h"
#include "Player.h"
#include "MAP.h"
#include "Keyboard.h"

#define OFF 0		//FALSE
#define ON 1		//TRUE
#define LOAD 1		//道
#define WALL 0		//壁

static int  i;   //forで使うよう
int  yousosuu;	 //Boxの個数
int  goal;
int  moveNumber;	//動いてる箱のナンバー
S_Box box[5];    //構造体
E_Drct Box_Drct;          //向きの管理
int Box_Move_Flg = OFF;		//動くか動かないか
int Box_Count_x = 0;	//ヌルヌル動かす
int Box_Count_y = 0;   // ヌルヌル動かす
int Handle;				//// データハンドル格納用変数
int Box_Clear_Flg = OFF;		//ボックスがゴールの座標と一致しているかどうかのフラグ
int Box_Back_Flg;			//ボックスの座標を一つ前に戻す

int Box_Up_Flg = OFF;  //上が押されたら(向きやcountの管理を行う)
int Box_Down_Flg = OFF;  //下が押されたら(向きやcountの管理を行う)
int Box_Right_Flg = OFF;  //右が押されたら(向きやcountの管理を行う)
int Box_Left_Flg = OFF;  //左が押されたら(向きやcountの管理を行う)

int Box_Pos(int *x, int *y, int num) {
	//ボックスの位置をマップから貰う

	*x = box[num].x;                             
	*y = box[num].y;

	return 0;
}

bool Box_Clear() {
	Box_Clear_Flg = ON;
	//ここでCLEARフラグをONにする
	for (i = 0;i < yousosuu;i++) {
		if (MAP_Data(box[i].x, box[i].y) != 2) {
			Box_Clear_Flg = OFF;
			//ここでCLEARフラグをOFFにする
		}
	}
	return Box_Clear_Flg;
	//return CLEARフラグ;	
}

int Box_Move(E_Drct Drct, int num) {
	//プレイヤーからボックスにここへ動けという関数をもらう   

	moveNumber = num;
	
	box[num].bx = box[num].x;		//ボックスの初期x座標を仮のx座標に移す
	box[num].by = box[num].y;		//ボックスの初期y座標を仮のy座標に移す

	switch (Drct) {

	case E_Drct_Up:
			box[num].bx += 0;		//仮のx座標を動かす
			box[num].by += -1;		//仮のy座標を動かす
			Box_Up_Flg = ON;		
			break;
		
	case E_Drct_Right:
			box[num].bx += +1;		//仮のx座標を動かす
			box[num].by += 0;		//仮のy座標を動かす
			Box_Right_Flg = ON;
			break;
		
	case E_Drct_Down:
			box[num].bx += 0;		//仮のx座標を動かす
			box[num].by += +1;		//仮のy座標を動かす
			Box_Down_Flg = ON;
			break;
		
	case E_Drct_Left:
			box[num].bx += -1;		//仮のx座標を動かす
			box[num].by += 0;		//仮のy座標を動かす
			Box_Left_Flg = ON;
			break;
	};

	return 0;
}

int Box_Bectl(int *x, int *y, int num) {
	//動いた時のベクトル（方向）をもらう
/*
	num = ;

	*x = box[num].x = ;
	*y = box[num].y = ;
*/
	return 0;
}

int Box_Init() {
	//ここで初期化をする
	
	Handle = LoadGraph("Images/Box.png"); // 画像をロード

	yousosuu =  MAP_Box_Count_Init();
	
	
	for (i = 0;i < yousosuu;i++) {
		box[i].x = MAP_Box_Pos_Init_x(i);
		box[i].y = MAP_Box_Pos_Init_y(i);
	}
	return 0;
}

/*
int Box_Dbug() {		//ただBox_Move()を呼ぶためだけの関数

	if (Box_Move_Flg == OFF) {
		//上
		if (Keyboard_Get(KEY_INPUT_UP) == 1)   //↑が押されたら
		{
			Box_Move(E_Drct_Up, 0);
		}
		//下
		if (Keyboard_Get(KEY_INPUT_RIGHT) == 1)   //↓が押されたら
		{
			Box_Move(E_Drct_Right, 0);
		}
		//左
		if (Keyboard_Get(KEY_INPUT_DOWN) == 1)   //←が押されたら
		{
			Box_Move(E_Drct_Down, 0);
		}
		//右
		if (Keyboard_Get(KEY_INPUT_LEFT) == 1)   //→が押されたら
		{
			Box_Move(E_Drct_Left, 0);
		}
	}
	return 0;
}
*/

int Box_Dpct() {		//boxの移動の計算をしている
	//ここで計算
	//Dqctは毎フレーム呼ばれる
	if (Box_Up_Flg == ON || Box_Right_Flg == ON || Box_Down_Flg == ON || Box_Left_Flg == ON) {		//いずれかのBox_FlgがONになっていれば
		
			/*ボックスをヌルヌル動かす処理*/
			if (Box_Up_Flg == ON) {
				Box_Count_y--;		//y座標が-される
			}

			if (Box_Right_Flg == ON) {
				Box_Count_x++;		//x座標が+される
			}

			if (Box_Down_Flg == ON) {
				Box_Count_y++;		//y座標が+される
			}

			if (Box_Left_Flg == ON) {
				Box_Count_x--;		//x座標が-される
			}
		
		if (Box_Count_y <= -MAP_SIZE+1 || Box_Count_x >= MAP_SIZE-1 || Box_Count_y >= MAP_SIZE-1 || Box_Count_x <= -MAP_SIZE+1)		//countが64を超えたら止める
			//if (Box_Count_x >= MAP_SIZE || Box_bCount_y <= -MAP_SIZE || Box_Count_x <= -MAP_SIZE || Box_Count_y >= MAP_SIZE)
		{
			
			box[moveNumber].y = box[moveNumber].by;		//Box_Moveで動かした仮のx座標をboxのx座標に戻す
			box[moveNumber].x = box[moveNumber].bx;		//Box_Moveで動かした仮のy座標をboxのy座標に戻す

			/* 各フラグをOFF(0)にする*/
	        Box_Count_x = 0;
			Box_Count_y = 0;
			Box_Up_Flg = OFF;
			Box_Right_Flg = OFF;
			Box_Down_Flg = OFF;
			Box_Left_Flg = OFF;
			moveNumber = -1;
		}
	}
	return 0;
}

//バックスペースが押されたら戻る 
int Box_Back_Move(E_Drct Old_Drct , int num) {   

//	yousosuu = MAP_Box_Count_Init();

	moveNumber = num;


	Old_Drct = (E_Drct)((Old_Drct + 2) % 4);

	box[num].bx = box[num].x;		//ボックスの初期x座標を仮のx座標に移す
	box[num].by = box[num].y;		//ボックスの初期y座標を仮のy座標に移す

	switch (Old_Drct) {

	case E_Drct_Up:
		box[num].bx += 0;		//仮のx座標を動かす
		box[num].by += -1;		//仮のy座標を動かす
		Box_Up_Flg = ON;
		break;

	case E_Drct_Right:
		box[num].bx += +1;		//仮のx座標を動かす
		box[num].by += 0;		//仮のy座標を動かす
		Box_Right_Flg = ON;
		break;

	case E_Drct_Down:
		box[num].bx += 0;		//仮のx座標を動かす
		box[num].by += +1;		//仮のy座標を動かす
		Box_Down_Flg = ON;
		break;

	case E_Drct_Left:
		box[num].bx += -1;		//仮のx座標を動かす
		box[num].by += 0;		//仮のy座標を動かす
		Box_Left_Flg = ON;
		break;
	};

  return 0;

}

int Box_Draw() {
	//ここで描写
	//こっちも毎フレーム呼ばれますが計算とは別に書きます

	yousosuu = MAP_Box_Count_Init();

	for (i = 0; i < yousosuu; i++) {
		if (i != moveNumber) {
			DrawGraph(box[i].x * MAP_SIZE , box[i].y * MAP_SIZE , Handle, TRUE); // データハンドルを使って画像を描画
					//(boxのx座標 * map_size(64) + count.x(1マス）, boxのy座標 * map_size(64) + count.y(1マス）)
		}
		else {
			DrawGraph(box[i].x * MAP_SIZE + Box_Count_x, box[i].y * MAP_SIZE + Box_Count_y, Handle, TRUE); // データハンドルを使って画像を描画
		}
	}

	//DrawFormatString(250, 80, GetColor(255, 0, 0), "box[0].bx:%d", box[0].bx);
	
	return 0;
}

int Box_End() {
	//無し
	return 0;
}

/*boxの移動手順*/

/*
1. boxが動く時、フラグが発生する。
2. ボックスの描写がそのマスに移動する。
3. ボックスの描写がそのマスに移動したら、ボックスの座標がその止まった地点になる。　
		※ ゲーム画面ではボックスが止まってからボックスの座標が動いたことになる。　
*/