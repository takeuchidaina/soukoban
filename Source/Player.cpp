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
	//E_Object_Box,       //ボックス

}E_Object;


/**********************************　変数宣言　******************************************/
//共通
E_Drct Drct;             //向きの管理
int i;                   //for文用
int Count = 0;

//Player
S_Player Player;         //Playerの構造体(ヘッダーファイルにて作成)
int Gyallaly[12];        //プレイヤー画像の変数(今回は12分割なので12)
int count_x = 0;         //マップサイズ分カウントする役割 x
int count_y = 0;         //マップサイズ分カウントする役割 y
bool Move_Flg = false; //動作管理
bool Up_Flg = false;  //上が押されたら(向きやcountの管理を行う)
bool Down_Flg = false;  //下が押されたら(向きやcountの管理を行う)
bool Right_Flg = false;  //右が押されたら(向きやcountの管理を行う)
bool Left_Flg = false;  //左が押されたら(向きやcountの管理を行う)
bool Back_Flg = false;  //Back_Moveフラグ
bool Player_Image = 0;   //画像の順番(アニメーション)
int None_Num = 7;        //画像のスタンバイ状態(静止状態)
bool Check_Flg = false;  //確認用

//Box
int Box_x = 0;
int Box_y = 0;
int Box_nx = 0;         //Boxの仮の x 座標
int Box_ny = 0;         //Boxの仮の y 座標
int Judge_x = 0;        //Boxの移動先を判断する x
int Judge_y = 0;        //Boxの移動先を判断する y
int Box_Element;        //Boxの要素数


//Playerの初期化
int Player_Init()
{
	/*プレイヤーのx/y座標を初期化する(値はMAP.hより)*/
	Player.x = MAP_Player_Pos_Init_x();  //プレイヤーの初期化 x
	Player.y = MAP_Player_Pos_Init_y();  //プレイヤーの初期化 y
	Drct = E_Drct_None;                  //向きの初期化
	LoadDivGraph("gazou/Player.png", 12, 3, 4, 64, 64, Gyallaly);  	//画像の読み込み

	return 0;
}


//計算(毎フレーム呼ばれる)
int Player_Dpct()
{

	/**********************************　上下左右　******************************************/
	//もし、Move_Flgがfalse(0)ならキー入力を受け付ける(動いていない状態)
	if (Move_Flg == false)
	{
		//戻るボタンが押されていないなら
		if (Back_Flg == false)
		{
			/*仮の変数nxにプレイヤーのx座標を入れる  >>  ny/nxの座標の更新*/
			Player.nx = Player.x;
			Player.ny = Player.y;
		}

		//上
		if (Keyboard_Get(KEY_INPUT_UP) == 1)   //↑が押されたら
		{
			Player.ny--;    //プレイヤーの仮の変数nyの座標が-1(-MAP_SIZE)される
			Drct = E_Drct_Up;  //上のキーが押された
		}
		//左
		if (Keyboard_Get(KEY_INPUT_LEFT) == 1)   //←が押されたら
		{
			Player.nx--;      //プレイヤーの仮の変数nxのx座標が-1(-MAP_SIZE)される
			Drct = E_Drct_Left;  //左のキーが押された
		}
		//下
		if (Keyboard_Get(KEY_INPUT_DOWN) == 1)   //↓が押されたら
		{
			Player.ny++;      //プレイヤーの仮の変数nyのy座標が+1(+MAP_SIZE)される
			Drct = E_Drct_Down;  //下のキーが押された
		}
		//右
		if (Keyboard_Get(KEY_INPUT_RIGHT) == 1)   //→が押されたら
		{
			Player.nx++;       //プレイヤーの仮の変数nxのx座標が+1(+MAP_SIZE)される
			Drct = E_Drct_Right;  //右のキーが押された
		}
	}

	/*********************************　移動制御(Player)　*****************************************/
	//もし、方向が定められていないなら(移動が終わっている状態なら)
	if (Drct != E_Drct_None)
	{
		//もし、移動先に壁が　ない　なら
		if (MAP_Data(Player.nx, Player.ny) == E_Object_Load || MAP_Data(Player.nx, Player.ny) == E_Object_Goal)
		{
			Move_Flg = true;  //Move_Flgのtrue　これにより動いているという判定になる
		}

		//もし、移動先に壁が　ある　なら
		if (MAP_Data(Player.nx, Player.ny) == E_Object_Wall)
		{
			//壁なら動作させない
			Player.ny = Player.ny;
			Player.nx = Player.nx;

			//各キーフラグのfalse　>>  キー入力ができるようになる
			Drct = E_Drct_None;
		}
		Box_Pos(&Box_x, &Box_y, Box_Element);

		//ここはBox_Elementの使い方がおかしい
		for (i = Box_Element; i == 0; i--)
		{
			if (Player.nx == Box_x && Player.ny == Box_y)
			{
				Check_Flg = true;
				//Box - Player = 1or-1 これを　Boxに足すとBoxの次の座標が出る。
				Judge_x = Player.nx - Player.x;
				Judge_y = Player.ny - Player.y;
				//仮の変数に代入
				Box_nx = Box_x + Judge_x;
				Box_ny = Box_y + Judge_y;
				//もし、押された方向に壁が　ない　なら
				if (MAP_Data(Box_nx, Box_ny) == E_Object_Load || MAP_Data(Box_nx, Box_ny) == E_Object_Goal)
				{
					Box_Move(Drct, Box_Element);
					UI_Box_Move_History(Drct, Box_Element);

					//					Box_x = Box_nx;
					//					Box_y = Box_ny;
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
		}


		//もし、Move_Flgがtrueなら　(Move_Flgは移動先が壁じゃないならtrueになっている)
		if (Move_Flg == true)
		{
			//各キーのFlgによりその方向にあわせてcountが + か - される
			if (Drct == E_Drct_Up)
			{
				count_y--;   //y座標が - される
			}
			if (Drct == E_Drct_Left)
			{
				count_x--;   //x座標が - される
			}
			if (Drct == E_Drct_Down)
			{
				count_y++;   //y座標が + される
			}
			if (Drct == E_Drct_Right)
			{
				count_x++;   //x座標が + される
			}
		}

		//もし、x/yのカウントが±64なら
		if (count_x >= MAP_SIZE || count_y <= -MAP_SIZE || count_x <= -MAP_SIZE || count_y >= MAP_SIZE)
		{
			//プレイヤーの座標に仮の座標を代入する  >>  描画の際に使うのはxとy
			Player.y = Player.ny;
			Player.x = Player.nx;
			if (Back_Flg == false)
			{
				UI_Player_Move_History(Drct);

				UI_StepCount_MoveOn();
			}
			else
			{
				Back_Flg = false;
			}

			//カウントの初期化  各フラグのfalse(0)
			count_x = 0;
			count_y = 0;
			Move_Flg = false;
			Drct = E_Drct_None;

		}
	}

	//Boxを押す関数



	return 0;
}




//バックスペースが押されたら戻る
int Player_Back_Move(E_Drct Old_Drct) {

	//向きを反転させる
	Drct = (E_Drct)((Old_Drct + 2) % 4);
	//フラグがtrueだとカウントされる
	Move_Flg = true;

	//向きに合わせて移動する
	switch (Drct) {

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

	};

	//フラグがtrueだと、Playerのnx/ny座標にx/yが代入されない
	Back_Flg = true;

	return 0;
}

//描写(毎フレーム呼ばれる)
int Player_Draw()
{

	/****************************************** Player ******************************************/
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
	DrawFormatString(130, 40, GetColor(255, 0, 0), "boxのx座標:%d", Box_x);
	DrawFormatString(250, 40, GetColor(255, 0, 0), "boxのy座標:%d", Box_y);
	DrawFormatString(200, 400, GetColor(255, 0, 0), "(接触)Check_Flg:%d", Check_Flg);
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