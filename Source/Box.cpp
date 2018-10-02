#include "Dxlib.h"
#include "Box.h"
#include "Player.h"
#include "MAP.h"
#include "Keyboard.h"

#define OFF 0		//FALSE
#define ON 1		//TRUE
#define LOAD 1		//道
#define WALL 0		//壁



static int  i;   //for
int  yousosuu;	 //Boxの個数
S_Box box[5];    //構造体
int Box_Move_Flg = OFF;		//動くか動かないか
int Box_Count_x = 0;	//ヌルヌル動かす
int Box_Count_y = 0;// ヌルヌル動かす
int Handle;				//// データハンドル格納用変数

int Box_Up_Flg = OFF;  //上が押されたら(向きやcountの管理を行う)
int Box_Down_Flg = OFF;  //下が押されたら(向きやcountの管理を行う)
int Box_Right_Flg = OFF;  //右が押されたら(向きやcountの管理を行う)
int Box_Left_Flg = OFF;  //左が押されたら(向きやcountの管理を行う)

int Box_Pos(int*x, int*y, int num) {
	//ボックスの位置をマップから貰う

	*x = box[num].x;                             
	*y = box[num].y;

	return 0;
}

int Box_Move(E_Drct drct, int num) {
	//プレイヤーからボックスにここへ動けという関数をもらう                                                               

	switch (drct) {

	case E_Drct_Up:
			//box[num].x += 0;
			box[num].y += -1;
			break;
		
	case E_Drct_Right:
			box[num].x += 1;
			//box[num].y += 0;
			break;
		
	case E_Drct_Down:
			//box[num].x += 0;
			box[num].y += 1;
			break;
		
	case E_Drct_Left:
			box[num].x += -1;
			//box[num].y += 0;
			break;
	};

	return 0;
}

/*int Box_Bectl(int *x, int *y, int num) {
	//動いた時のベクトル（方向）をもらう

	num = ;

	*x = box[num].x = ;
	*y = box[num].y = ;

	return 0;
}*/

int Box_Init() {
	//ここで初期化をする
	
	yousosuu =  Map_Box_Count_Init();
	
	for (i = 0;i < yousosuu;i++) {
		//Map_Box_Pos_Init(box[i], i);    //なにこいつ

		/*ボックスと壁の当たり判定*/
		if (Map_Data(box[i].y, box[i].x) == LOAD) {
			Box_Move_Flg = ON;
		}
		if (Map_Data(box[i].y, box[i].x) == WALL) {
			box[i].y = box[i].x;
			box[i].x = box[i].y;
			Box_Move_Flg = OFF;
		}
	}
	return 0;
}

int Box_Dbug() {

	if (Box_Move_Flg == OFF) {
		//上
		if (Keyboard_Get(KEY_INPUT_UP) == 1)   //↑が押されたら
		{
			Box_Up_Flg = ON;
			Box_Move(E_Drct_Up, 0);
		}
		//下
		if (Keyboard_Get(KEY_INPUT_RIGHT) == 1)   //↓が押されたら
		{
			Box_Move(E_Drct_Right, 0);
			Box_Right_Flg = ON;
		}
		//左
		if (Keyboard_Get(KEY_INPUT_DOWN) == 1)   //←が押されたら
		{
			Box_Move(E_Drct_Down, 0);
			Box_Down_Flg = ON;
		}
		//右
		if (Keyboard_Get(KEY_INPUT_LEFT) == 1)   //→が押されたら
		{
			Box_Move(E_Drct_Left, 0);
			Box_Left_Flg = ON;
		}
	}
	return 0;
}

int Box_Dpct() {
	//ここで計算
	//Dqctは毎フレーム呼ばれる
	if (Box_Up_Flg == ON || Box_Right_Flg == ON || Box_Down_Flg == ON || Box_Left_Flg == ON) {
		
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
		
		
		if (Box_Count_y <= -MAP_SIZE || Box_Count_x >= MAP_SIZE || Box_Count_y >= MAP_SIZE || Box_Count_x <= -MAP_SIZE)
		{
			/*プレイヤーの座標に仮の座標を代入する  >>  描画の際に使うのはxとy
			Player.y = Player.ny;
			Player.x = Player.nx;*/

			/*カウントの初期化  各フラグのOFF(0)*/
	        Box_Count_x = 0;
			Box_Count_y = 0;
			Box_Up_Flg = OFF;
			Box_Right_Flg = OFF;
			Box_Down_Flg = OFF;
			Box_Left_Flg = OFF;
		}
	}
	return 0;
}

int Box_Draw() {
	//ここで描写
	//こっちも毎フレーム呼ばれますが計算とは別に書きます

	Handle = LoadGraph("gazou/block.png"); // 画像をロード

	for (i = 0;i < yousosuu;i++) {
			DrawGraph(box[i].x * MAP_SIZE + Box_Count_x, box[i].y * MAP_SIZE + Box_Count_y, Handle, TRUE); // データハンドルを使って画像を描画
		}
	
	//確認用ー各変数(後に削除)
	/*-DrawFormatString(0, 20, GetColor(255, 0, 0), "x座標:%d", box[0].x);
	DrawFormatString(80, 20, GetColor(255, 0, 0), "y座標:%d", box[0].y);
	DrawFormatString(0, 40, GetColor(255, 0, 0), "MoveFlg:%d", Box_Move_Flg);
	DrawFormatString(150, 20, GetColor(255, 0, 0), "xカウント:%d", Box_Count_x);
	DrawFormatString(250, 20, GetColor(255, 0, 0), "yカウント:%d", Box_Count_y);*/

	return 0;
}



int Box_End() {
	//無し
	return 0;
}