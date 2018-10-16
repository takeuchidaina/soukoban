#include "DxLib.h"
#include "Player.h"
#include "Keyboard.h"
#include "MAP.h"
#include "Box.h"
#include "UI.h"


/**********************************　変数宣言　******************************************/

//Player

	//Playerの位置
	S_Player Player;     //Playerの構造体(ヘッダーファイルにて作成)

	//移動
	bool Move_Flg;       //動作管理
	int count_x;         //マップサイズ分カウント ｘ
	int count_y;         //マップサイズ分カウント ｙ

	//向き
	E_Drct Drct;     //向きの管理

	//画像
	int None_Num;        //画像のスタンバイ状態(静止状態)
	int Gyallaly[12];    //プレイヤー画像の変数(今回は12分割なので12)
	bool Player_Image;   //画像の順番(アニメーション)

	//一歩戻る
	bool Back_Flg;   //Back_Moveフラグ
	int Argument_Check;  //引数と関数の管理を行う


//Box

	//Boxの座標
	
	int Box_x;       // x 座標
	int Box_y;       // y 座標
	int Box_nx;      //仮の x 座標
	int Box_ny;      //仮の y 座標
	
	//S_Box Box[5];

	//移動先の判断
	int Judge_x;     //Boxの横の移動先を判断する
	int Judge_y;     //Boxの縦の移動先を判断する

	//個数管理
	int Box_Max;  //Boxの最大数


/**********************************　初期化(一回)　******************************************/
int Player_Init()
{
 //Player

	//Playerの位置(MAPより)
	Player.x = MAP_Player_Pos_Init_x();
	Player.y = MAP_Player_Pos_Init_y();

	//移動
	Move_Flg = false;   //動いていない
	count_x = 0;
	count_y = 0;

	//向き
	Drct = E_Drct_None;  //向き:無し

	//画像
	Gyallaly[12] = {};
	LoadDivGraph("Images/Player.png", 12, 3, 4, 64, 64, Gyallaly);  //配列「Gyallaly」へ画像を入れる
			//LoadDivGraph("File/name.",画像の分割数,横の枚数,縦の枚数,画像のサイズx,画像のサイズy,配列名)
	None_Num = 7;    //スタンバイ状態の向いてる方向を正面へするための画像番号7
	Player_Image = 0;

	//一歩戻る
	Back_Flg = false;    //キー入力されていない
	Argument_Check = 0;  //プレイヤーもボックスも動かさない


 //Box

	//座標
	
	Box_x = 0;
	Box_y = 0;
	Box_nx = 0;
	Box_ny = 0;
	

	//移動
	Judge_x = 0;
	Judge_y = 0;

	//個数管理
	Box_Max = MAP_Box_Count_Init();

	return 0;
}


/**********************************　計算(毎回) ******************************************/
int Player_Dpct()
{

	//キー入力処理とnx/nyの座標更新
	if (Move_Flg == false )  //静止状態ならキー入力を受け付ける
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

	//プレイヤーの移動先に何があるかの判断(関数:Player_Move_Check)
	if (Drct != E_Drct_None)  //キーが入力されているなら
	{
		Player_Move_Check();
	}
		
	//プレイヤーを移動させる(関数:Player_Move)
	if (Move_Flg == true)	//移動先が壁じゃないなら
	{
		Player_Move();
		Player_Back_Argument();
	}

	return 0;
}

/**********************************　移動判断(条件)　******************************************/
int Player_Move_Check()
{
	//Player

		//移動先が 道かゴール なら　>>　動く
		if (MAP_Data(Player.nx, Player.ny) == E_Object_Load || MAP_Data(Player.nx, Player.ny) == E_Object_Goal)
		{
			Move_Flg = true;  //動作状態(Player_Moveが作動)

			if (Argument_Check == 0)
			{
				UI_Player_Move_History(Drct);
				Argument_Check = 1;   //歩数が増える
			}
		}

		//移動先が 壁 なら　>>　動かない
		if (MAP_Data(Player.nx, Player.ny) == E_Object_Wall)
		{
			//各キーフラグのfalse　>>  キー入力ができるようになる
			Move_Flg = false;
			Drct = E_Drct_None;
		}

	//Box

		for(int i=0;i<Box_Max;i++)  //複数のやつ
		{
		    //座標と何個目かの取得(MAPより)
			Box_Pos(&Box_x, &Box_y, i);

			//移動先が Box なら　>>　Boxを動かせるか判断
			if (Player.nx == Box_x && Player.ny == Box_y)
			{
				//Box - Player = 1or-1 これを　Boxに足すとBoxの次の座標が出る。
				Judge_x = Player.nx - Player.x;
				Judge_y = Player.ny - Player.y;

				//仮の変数(nx/ny)に代入
				Box_nx = Box_x + Judge_x;
				Box_ny = Box_y + Judge_y;
				for (int j = 0; j < Box_Max; j++)
				{
					int Temp_x = 0;
					int Temp_y = 0;
					Box_Pos(&Temp_x, &Temp_y, j);

				//押された方向が 道かゴール なら　>>　Boxへ引数を渡す
				if ((MAP_Data(Box_nx, Box_ny) == E_Object_Load || MAP_Data(Box_nx, Box_ny) == E_Object_Goal) || (Box_nx == Temp_x && Box_ny == Temp_y))
				{
					//Box_Move(Drct, i);  //向きと何個目のBoxか
					//UI_Box_Move_History(Drct, i);
				}



					if (i != j)
					{
						//押された方向が 壁 なら　>>　動かない
						if (MAP_Data(Box_nx, Box_ny) == E_Object_Wall || (Box_nx  == Temp_x && Box_ny == Temp_y))
						{
							//各キーフラグのfalse　>>  キー入力ができるようになる
							Move_Flg = false;
							Drct = E_Drct_None;
						}
						else
						{
							Box_Move(Drct, i);  //向きと何個目のBoxか
						UI_Box_Move_History(Drct, i);
						}
					}
				}
			}
     	}

	return 0;
}

/**********************************　移動(条件:Dpct)　******************************************/
int Player_Move()
{
	//入力されたキーの向きにあわせてcount_x/count_yが + か - される
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


	//count_x/count_yのどれかのカウントが±64なら　>>　Player.x/yの座標更新・カウントとフラグの初期化
	if (count_x >= MAP_SIZE-1 || count_y <= -MAP_SIZE+1 || count_x <= -MAP_SIZE+1 || count_y >= MAP_SIZE-1)
	{
		//プレイヤーの座標に仮の座標を代入して座標を更新(描画の際に使うのはPlayer.x/.y)
		Player.y = Player.ny;
		Player.x = Player.nx;

		//カウントの初期化
		count_x = 0;
		count_y = 0;

		//フラグと向きの管理
		Move_Flg = false;
		Drct = E_Drct_None;
		Argument_Check = 0;
	}

	return 0;
}

/**********************************　一歩戻る 引数渡し(条件)　******************************************/
int Player_Back_Argument()
{
	//BackSpaceが押されていないなら(プレイヤーが進んだら)　>>　プレイヤーの向きをUIへ渡す・歩数の増加
	if (Back_Flg == false)
	{
		if (Argument_Check == 1)
		{
			UI_StepCount_MoveOn();
			Argument_Check = 2;
		}
	}

	//Back_Flgがtrueなら　>>　Back_Flg をfalseへ
	else
	{
		//BackSpaceが押されていない状態へ
		Back_Flg = false;
	}

	return 0;
}

/**********************************　一歩戻る(条件:UIより)　******************************************/
int Player_Back_Move(E_Drct Old_Drct) {

	//フラグがtrueだとPlayerのnx/ny座標にx/yが代入されない
	Back_Flg = true;

	//向きを反転させる
	Drct = (E_Drct)((Old_Drct + 2) % 4);

	Argument_Check = 4;

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

	return 0;
}

/**********************************　描画(毎回)　******************************************/
int Player_Draw()
{
	//MAP_SIZEをかけることによってマスの移動処理が1マスなら+1をすれば64ずれるというように楽になる

	//キー入力されてない時の画像表示
	if (Drct == E_Drct_None)
	{
		DrawGraph(Player.x * MAP_SIZE + count_x, Player.y * MAP_SIZE + count_y, Gyallaly[None_Num], TRUE);
	}


	//歩いてるように見える用に画像を表示する・None_Num(静止状態時の向く方向)の更新
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


#ifdef _DEBUG

	DrawFormatString(700,  20, GetColor(255, 0, 0), "0:上 1:右 2:下 3:左 4:通常");
	DrawFormatString(700,  40, GetColor(255, 0, 0), "Drct:%d", Drct);
	DrawFormatString(700,  60, GetColor(255, 0, 0), "MoveFlg:%d", Move_Flg);

	DrawFormatString(700,  120, GetColor(255, 0, 0), "Boxの最大個数:%d", Box_Max);
	DrawFormatString(700, 160, GetColor(255, 0, 0), "Box_x:%d", Box_x);
	DrawFormatString(700, 180, GetColor(255, 0, 0), "Box_y:%d", Box_y);
	DrawFormatString(700, 200, GetColor(255, 0, 0), "Box_nx:%d", Box_nx);
	DrawFormatString(700, 220, GetColor(255, 0, 0), "Box_ny:%d", Box_ny);
	DrawFormatString(700, 240, GetColor(255, 0, 0), "Judge_x:%d", Judge_x);
	DrawFormatString(700, 260, GetColor(255, 0, 0), "Judge_y:%d", Judge_y);

	DrawFormatString(700, 300, GetColor(255, 0, 0), "Argument_Check:%d", Argument_Check);

#endif

	return 0;
}

/**********************************　同時操作防止(条件:Dpct)　******************************************/
int Player_Move_Flg() {
	//BackSpeaceとキー操作を同時にできないようにするためにMove_Flgを渡す

	return Move_Flg;

}

/**********************************　終了(一回)　******************************************/
int Player_End()
{
	//No Script
	return 0;
}