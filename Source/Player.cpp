#include "DxLib.h"
#include "Player.h"
#include "Keyboard.h"
#include "MAP.h"
#include "Box.h"
#include "UI.h"

typedef enum
{

	E_Object_Wall,      //行けない場所
	E_Object_Load,      //歩ける場所
	E_Object_Goal,      //ゴール

}E_Object;


/**********************************　変数宣言　******************************************/
//共通

	int i;         //for文用


//Player

	//Playerの位置
	S_Player Player;     //Playerの構造体(ヘッダーファイルにて作成)

	//移動
	bool Move_Flg;       //動作管理
	int count_x;         //マップサイズ分カウント ｘ
	int count_y;         //マップサイズ分カウント ｙ

	//向き
	E_Drct Drct;   //向きの管理
	bool Up_Flg;     //上が押されたら(向きやcountの管理を行う)
	bool Down_Flg;   //下が押されたら(向きやcountの管理を行う)
	bool Right_Flg;  //右が押されたら(向きやcountの管理を行う)
	bool Left_Flg;   //左が押されたら(向きやcountの管理を行う)

	//BackSpace
	bool Back_Flg;   //Back_Moveフラグ
	int Drct_Count;      //UIへ向きを渡す際のカウント

	//画像
	int None_Num;        //画像のスタンバイ状態(静止状態)
	int Gyallaly[12];    //プレイヤー画像の変数(今回は12分割なので12)
	bool Player_Image;   //画像の順番(アニメーション)

//Box
	int Box_x;
	int Box_y;
	int Box_nx;         //Boxの仮の x 座標
	int Box_ny;         //Boxの仮の y 座標
	int Judge_x;        //Boxの移動先を判断する x
	int Judge_y;        //Boxの移動先を判断する y
	int Box_Element;    //Boxの要素数


//Playerの初期化
int Player_Init()
{
 //Player

	//Playerの位置(MAPより)
	Player.x = MAP_Player_Pos_Init_x();
	Player.y = MAP_Player_Pos_Init_y();

	//移動
	Move_Flg = false;
	count_x = 0;
	count_y = 0;

	//向き
	Drct = E_Drct_None;  //向き:無し
	Up_Flg = false;
	Down_Flg = false;
	Right_Flg = false;
	Left_Flg = false;

	//画像
	Gyallaly[12] = { 0,0,0,
					 0,0,0,
					 0,0,0,
					 0,0,0 };
	LoadDivGraph("gazou/Player.png", 12, 3, 4, 64, 64, Gyallaly);  //Playerの画像:3x4の64ドット
	None_Num = 7;    //画像のスタンバイ状態(静止状態)を正面向いてるやつへ
	Player_Image = 0;

	//BackSpace
	Drct_Count = 0;
	Back_Flg = false;    //Back_Moveフラグ


 //Box

	//座標
	Box_x = 0;
	Box_y = 0;
	Box_nx = 0;
	Box_ny = 0;

	//移動
	Judge_x = 0;        //Boxの移動先を判断する x
	Judge_y = 0;        //Boxの移動先を判断する y

	//複数個対応
	Box_Element;

	return 0;
}


//計算(毎フレーム呼ばれる)
int Player_Dpct()
{

	//キー入力処理とnx/nyの座標更新
	if (Move_Flg == false)  //静止状態ならキー入力を受け付ける
	{
		//nx/nyの座標更新
		if (Back_Flg == false)  //BackSpaceが押されていないなら
		{
			Player.nx = Player.x;
			Player.ny = Player.y;
		}

	//キー入力処理

		//上
		if (Keyboard_Get(KEY_INPUT_UP) == 1)   //↑
		{
			Player.ny--;    //プレイヤーの仮の変数nyの座標が-1(-MAP_SIZE)される
			Drct = E_Drct_Up;
		}
		//左
		if (Keyboard_Get(KEY_INPUT_LEFT) == 1)  //←
		{
			Player.nx--;      //プレイヤーの仮の変数nxのx座標が-1(-MAP_SIZE)される
			Drct = E_Drct_Left;
		}
		//下
		if (Keyboard_Get(KEY_INPUT_DOWN) == 1)  //↓
		{
			Player.ny++;      //プレイヤーの仮の変数nyのy座標が+1(+MAP_SIZE)される
			Drct = E_Drct_Down;
		}
		//右
		if (Keyboard_Get(KEY_INPUT_RIGHT) == 1) //→
		{
			Player.nx++;       //プレイヤーの仮の変数nxのx座標が+1(+MAP_SIZE)される
			Drct = E_Drct_Right;
		}


	}

	//プレイヤーの移動先に何があるかの判断
	if (Drct != E_Drct_None)  //キーが入力されているなら
	{
		Player_Move_Check();
	}
		

	//プレイヤーを移動させる
	if (Move_Flg == true)	//移動先が壁じゃないならtrueになっている
	{
		Player_Move();
	}



	return 0;
}


int Player_Move_Check()
{
	//壁

		//移動先に壁が ない なら
		if (MAP_Data(Player.nx, Player.ny) == E_Object_Load || MAP_Data(Player.nx, Player.ny) == E_Object_Goal)
		{
			Move_Flg = true;  //これにより動いているという判定になる
		}

		//移動先に壁が ある なら
		if (MAP_Data(Player.nx, Player.ny) == E_Object_Wall)
		{
			//壁なら動作させない
			Player.ny = Player.ny;
			Player.nx = Player.nx;

			//各キーフラグのfalse　>>  キー入力ができるようになる
			Drct = E_Drct_None;
		}

	//Box


//	for(int i=0;i<Box_Element;i++)  //複数のやつ
//	{
		Box_Pos(&Box_x, &Box_y, Box_Element);

		if (Player.nx == Box_x && Player.ny == Box_y)
		{
			//Box - Player = 1or-1 これを　Boxに足すとBoxの次の座標が出る。
			Judge_x = Player.nx - Player.x;
			Judge_y = Player.ny - Player.y;

			//仮の変数(nx・ny)に代入
			Box_nx = Box_x + Judge_x;
			Box_ny = Box_y + Judge_y;

			//もし、押された方向に壁が　ない　なら
			if (MAP_Data(Box_nx, Box_ny) == E_Object_Load || MAP_Data(Box_nx, Box_ny) == E_Object_Goal)
			{
				Box_Move(Drct, Box_Element);
				UI_Box_Move_History(Drct, Box_Element);			
			}
			//もし、押された方向に壁が　ある　なら
			if (MAP_Data(Box_nx, Box_ny) == E_Object_Wall)
			{
				Player.nx = Player.nx;
				Player.ny = Player.ny;
				Move_Flg = false;
				Drct = E_Drct_None;
			}
		}
//	}

	return 0;
}


int Player_Move()
{

		//入力されたキーの方向にあわせてcountが + か - される
	switch (Drct)
	{
		//上
	case E_Drct_Up:
		count_y--;
		break;
		//左
	case E_Drct_Left:
		count_x--;
		break;
		//下
	case E_Drct_Down:
		count_y++;
		break;
		//右
	case E_Drct_Right:
		count_x++;
		break;
	}


	//もし、x・yのカウントが±64なら
	if (count_x >= MAP_SIZE || count_y <= -MAP_SIZE || count_x <= -MAP_SIZE || count_y >= MAP_SIZE)
	{
		//プレイヤーの座標に仮の座標を代入する  >>  描画の際に使うのはxとy
		Player.y = Player.ny;
		Player.x = Player.nx;

		//カウントの初期化  各フラグのfalse(0)
		count_x = 0;
		count_y = 0;
		Move_Flg = false;
		Drct = E_Drct_None;

	}

	return 0;
}

int Player_Back_Argument()
{
	if (Back_Flg == false)
	{
		UI_Player_Move_History(Drct);   //プレイヤーの向きを渡す

		UI_StepCount_MoveOn();   //ステップカウントを増やす
	}
	else
	{
		Back_Flg = false;
	}

	Drct_Count = 0;

	return 0;
}

//バックスペースが押されたら戻る
int Player_Back_Move(E_Drct Old_Drct) {
	//フラグがtrueだとカウントされる
	Move_Flg = true;

	//向きを反転させる
	Drct = (E_Drct)((Old_Drct + 2) % 4);


	//向きに合わせて移動する
	switch (Drct) 
	{
		//上
	case E_Drct_Up:
		Player.ny += -1;
		break;
		//左
	case E_Drct_Left:
		Player.nx += -1;
		break;
		//下
	case E_Drct_Down:
		Player.ny += 1;
		break;
		//右
	case E_Drct_Right:
		Player.nx += 1;
		break;
	}

	//フラグがtrueだとPlayerのnx/ny座標にx/yが代入されない
	Back_Flg = true;




	return 0;
}

//描写(毎フレーム呼ばれる)
int Player_Draw()
{
	/*MAP_SIZEをかけることによってマスの移動処理が1マスなら+1をすれば64ずれるというように楽になる*/
	/*LoadDivGraph("File/name.",画像の分割数,横の枚数,縦の枚数,画像のサイズx,画像のサイズy,配列名)*/

	//キー入力されてない場合の画像
	if (Drct == E_Drct_None)
	{
		DrawGraph(Player.x * MAP_SIZE + count_x, Player.y * MAP_SIZE + count_y, Gyallaly[None_Num], TRUE);
	}


	//もし、Move_FlgがONなら(Move_Flgは移動先が壁じゃないならONになっている)
	if (Move_Flg == true)
	{

		//上下
		if (Drct == E_Drct_Up || Drct == E_Drct_Down)
		{
			Player_Image = count_y / 8 % 3;   //画像のアニメーション用の変数 y
		}
		//左右
		if (Drct == E_Drct_Right || Drct == E_Drct_Left)
		{
			Player_Image = count_x / 8 % 3;   //画像のアニメーション用の変数 x
		}

		//上
		if (Drct == E_Drct_Up)
		{
			DrawGraph(Player.x * MAP_SIZE + count_x, Player.y * MAP_SIZE + count_y, Gyallaly[0 + Player_Image], TRUE);
			None_Num = 1;
		}
		//左
		if (Drct == E_Drct_Left)
		{
			DrawGraph(Player.x * MAP_SIZE + count_x, Player.y * MAP_SIZE + count_y, Gyallaly[9 + Player_Image], TRUE);
			None_Num = 10;
		}
		//下
		if (Drct == E_Drct_Down)
		{
			DrawGraph(Player.x * MAP_SIZE + count_x, Player.y * MAP_SIZE + count_y, Gyallaly[6 + Player_Image], TRUE);
			None_Num = 7;
		}
		//右
		if (Drct == E_Drct_Right)
		{
			DrawGraph(Player.x * MAP_SIZE + count_x, Player.y * MAP_SIZE + count_y, Gyallaly[3 + Player_Image], TRUE);
			None_Num = 4;
		}

	}


	//確認用ー各変数(後に削除)
#ifdef _DEBUG

	DrawFormatString(70, 20, GetColor(255, 0, 0), "0:上 1:右 2:下 3:左 4:通常");
	DrawFormatString(320, 20, GetColor(255, 0, 0), "向き:%d", Drct);
	DrawFormatString(420, 20, GetColor(255, 0, 0), "MoveFlg:%d", Move_Flg);
	DrawFormatString(70, 40, GetColor(255, 0, 0), "個数:%d", Box_Element);
	DrawFormatString(70, 60, GetColor(255, 0, 0), "back_flg:%d", Back_Flg);

#endif

	return 0;
}

//BackSpeaceとキー操作を同時にできないようにするためにMove_Flgを渡す
int Player_Move_Flg() {
	//0 か 1
	return Move_Flg;

}

int Player_End()
{
	//No Script
	return 0;
}