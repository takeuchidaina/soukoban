#include "DxLib.h"
#include "Player.h"
#include "Keyboard.h"
#include "MAP.h"
#include "Box.h"
#include "UI.h"

typedef enum 
{

	E_Object_Wall,                   //行けない場所
	E_Object_Load,                   //歩ける場所
	E_Object_Box,                    //ボックス

}E_Object;


//ここで変数を宣言（C++を使わないのでグローバル変数）
S_Player Player;      //Playerの構造体(ヘッダーファイルにて作成)
E_Drct Drct;          //向きの管理
int count_x = 0;      //マップサイズ分カウントする x
int count_y = 0;      //マップサイズ分カウントする y
bool  Move_Flg  = false;  //動作管理
bool Up_Flg    = false;  //上が押されたら(向きやcountの管理を行う)
bool Down_Flg  = false;  //下が押されたら(向きやcountの管理を行う)
bool Right_Flg = false;  //右が押されたら(向きやcountの管理を行う)
bool Left_Flg  = false;  //左が押されたら(向きやcountの管理を行う)
int Gyallaly[12];       //プレイヤー画像の変数(今回は12分割なので12)
static int i=0;         //ループ用
int Box_Cnt;
int Box_x = 3;
int Box_y = 3;

//初期化
int Player_Init() 
{
	/*プレイヤーのx/y座標を初期化する(値はMAP.hより)*/
	Player.x = Map_Player_Pos_Init_x();  //プレイヤーの初期化 x
	Player.y = Map_Player_Pos_Init_y();  //プレイヤーの初期化 y
	Box_Cnt = Map_Box_Count_Init();  //ボックスの個数
	LoadDivGraph("gazou/PlayerTest.png", 12, 3, 4, 64, 64, Gyallaly);  	//画像の読み込み
	Drct = E_Drct_None;
	return 0;
}

//計算(毎フレーム呼ばれる)
int Player_Dpct() 
{

	/**********************************　上下左右　******************************************/
	//もし、Move_Flgがfalse(0)ならキー入力を受け付ける(動いていない状態)
	if (Move_Flg == false) 
	{
		/*仮の変数nxにプレイヤーのx座標を入れる  >>  ny/nxの座標の更新*/
		Player.nx = Player.x;
		Player.ny = Player.y;
		
		//上
		if (Keyboard_Get(KEY_INPUT_UP) == 1)   //↑が押されたら
		{
			Player.ny--;    //プレイヤーの仮の変数nyの座標が-1(-MAP_SIZE)される
			Drct = E_Drct_Up;  //上のキーが押された
		}
		//下
		if (Keyboard_Get(KEY_INPUT_DOWN) == 1)   //↓が押されたら
		{
			Player.ny++;      //プレイヤーの仮の変数nyのy座標が+1(+MAP_SIZE)される
			Drct = E_Drct_Down;  //下のキーが押された
		}
		//左
		if (Keyboard_Get(KEY_INPUT_LEFT) == 1)   //←が押されたら
		{
			Player.nx--;      //プレイヤーの仮の変数nxのx座標が-1(-MAP_SIZE)される
			Drct = E_Drct_Left;  //左のキーが押された
		}
		//右
		if (Keyboard_Get(KEY_INPUT_RIGHT) == 1)   //→が押されたら
		{
			Player.nx++;       //プレイヤーの仮の変数nxのx座標が+1(+MAP_SIZE)される
			Drct = E_Drct_Right;  //右のキーが押された
		}
	}

	/*********************************　移動制御(壁)　*****************************************/
	//もし、上下左右どれかのキーが押されているなら
	if (Drct != E_Drct_None)
	{
		//もし、移動先が壁じゃないなら
		if (Map_Data(Player.nx, Player.ny) == E_Object_Load) 
		{
			Move_Flg = true;  //Move_Flgのtrue　これにより動いているという判定になる
		}

		//もし、移動先が壁なら
		if (Map_Data(Player.nx, Player.ny) == E_Object_Wall)
		{
			/*壁なら動作させない(下記の代入式は分かりやすいように書いてあるだけ)*/
			Player.ny = Player.ny;
			Player.nx = Player.nx;

			/*各キーフラグのfalse　>>  キー入力ができるようになる*/
			Drct = E_Drct_None;
		}

		//もし、Move_Flgがtrueなら(Move_Flgは移動先が壁じゃないならtrueになっている)
		if (Move_Flg == true)
		{
			//各キーのFlgによりその方向にあわせてcountが + か - される
			if (Drct == E_Drct_Up)
			{
				count_y--;   //y座標が - される
			}
			if (Drct == E_Drct_Down)
			{
				count_y++;   //y座標が + される
			}
			if (Drct == E_Drct_Left)
			{
				count_x--;   //x座標が - される
			}
			if (Drct == E_Drct_Right)
			{
				count_x++;   //x座標が + される
			}
		}

		//もし、x/yのカウントが±64なら
		if (count_x >= MAP_SIZE || count_y <= -MAP_SIZE || count_x <= -MAP_SIZE || count_y >= MAP_SIZE)
		{
			/*プレイヤーの座標に仮の座標を代入する  >>  描画の際に使うのはxとy*/
			Player.y = Player.ny;
			Player.x = Player.nx;


			/*カウントの初期化  各フラグのfalse(0)*/
			count_x = 0;
			count_y = 0;
			Move_Flg = false;
			Drct =  E_Drct_None;

		}
	}

	/************************************　移動制御(Box)　*****************************************/

	//if (Map_Data(Player.nx, Player.ny) == Map_Data())
	//{

		//Box_Touch(ON);
	//}

	return 0;
}

//バックスペースが押されたら戻る
int Player_Back_Move(E_Drct Old_Drct) {

	Drct = (E_Drct)((Old_Drct + 2) % 4);
	Move_Flg = true;
	Player.x = Player.nx;
	Player.y = Player.ny;

	return 0;
}

//描写(毎フレーム呼ばれる)
int Player_Draw() 
{

   /****************************************** Player ******************************************/
	/*MAP_SIZEをかけることによってマスの移動処理が1マスなら+1をすれば64ずれるというように楽になる*/
	/*LoadDivGraph("File/name.",画像の分割数,横の枚数,縦の枚数,画像のサイズx,画像のサイズy,配列名)*/



	//キー入力されてない場合の画像(途中)
	//if (Move_Flg == false) {

		DrawGraph(Player.x * MAP_SIZE + count_x, Player.y * MAP_SIZE + count_y, Gyallaly[0], TRUE); // x,y の位置にキャラを描画
	//}

	//もし、Move_FlgがONなら(Move_Flgは移動先が壁じゃないならONになっている)
	if (Move_Flg == true) 
	{
		//上
		if (Drct == E_Drct_Up)
		{
			DrawGraph(Player.x * MAP_SIZE + count_x, Player.y * MAP_SIZE + count_y, Gyallaly[0], TRUE);
		}
		//下
		if (Drct == E_Drct_Down)
		{
			DrawGraph(Player.x * MAP_SIZE + count_x, Player.y * MAP_SIZE + count_y, Gyallaly[6], TRUE);
		}
		//右
		if (Drct == E_Drct_Right)
		{
			DrawGraph(Player.x * MAP_SIZE + count_x, Player.y * MAP_SIZE + count_y, Gyallaly[3], TRUE);
		}
		//左
		if (Drct == E_Drct_Left)
		{

			DrawGraph(Player.x * MAP_SIZE + count_x, Player.y * MAP_SIZE + count_y, Gyallaly[9], TRUE);
		}
	}
	
	/************************************　移動制御(Box)　*****************************************/
	DrawBox(Box_x*MAP_SIZE, Box_y*MAP_SIZE, Box_x*MAP_SIZE + MAP_SIZE, Box_y*MAP_SIZE + MAP_SIZE, GetColor(255, 0, 0), TRUE);


	//確認用ー各変数(後に削除)
	DrawFormatString(0, 20, GetColor(255, 0, 0), "x座標:%d",Player.x);
	DrawFormatString(80,20, GetColor(255, 0, 0), "y座標:%d",Player.y);
	DrawFormatString(0, 40, GetColor(255, 0, 0), "MoveFlg:%d",Move_Flg);
	DrawFormatString(150, 20, GetColor(255, 0, 0), "xカウント:%d", count_x);
	DrawFormatString(250, 20, GetColor(255, 0, 0), "yカウント:%d", count_y);
	DrawFormatString(350, 20, GetColor(255, 0, 0), "個数:%d", Box_Cnt);


	return 0;
}
int Player_End() 
{
	//No Script
	return 0;
}