
#ifndef INCLUDE_PLAYER
#define INCLUDE_PLAYER

extern int Player_Init();
extern int Player_Dpct();
extern int Player_Draw();
extern int Player_End();
extern int Player_Move_Flg();
extern int Player_Push_Box(int *,int *,int);

extern int Player_Move_Check();
extern int Player_Move();
extern int Player_Back_Argument();


typedef struct {

	int x;  //プレイヤーのx座標
	int y;  //プレイヤーのy座標
	int nx;  //仮のプレイヤーx座標
	int ny;  //仮のプレイヤーy座標

}S_Player;

typedef enum {

	E_Drct_Up,     //上
	E_Drct_Right,  //右
	E_Drct_Down,   //下
	E_Drct_Left,   //左

	E_Drct_None
} E_Drct;  //Drct = Direction(向き)

//オブジェクトの当たり判定用
typedef enum
{
	E_Object_Wall,      //行けない場所
	E_Object_Load,      //歩ける場所
	E_Object_Goal,      //ゴール
}E_Object;

extern int Player_Back_Move(E_Drct);

#endif