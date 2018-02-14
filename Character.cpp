#include "Character.h"

/*****
====================
キャラクタ座標の初期化 : Character()
====================
*****/
Character::Character(Pos pos_init, int handle_init, int move_f_init, int move_v_init)
{
	
	pos = pos_init;
	handle = handle_init;
	move_f = move_f_init;
	move_v = move_v_init;
	
}

/*****
====================
キャラクタ画像を表示 : Draw(Pos p, int handle)
====================
引数
Pos p : キャラクタの座標
int handle : データハンドル
====================
戻り値
なし
====================

*****/
void Character::Draw(Pos p, int handle)
{
	DrawGraph(p.x, p.y, handle, TRUE); //画像の描画
}


/*****
====================
敵の初期化
====================
*****/
Enemy::Enemy(Pos pos_init, int handle_init, int move_f_init, int move_v_init) : Character(pos_init, handle_init, move_f_init, move_v_init)
{
	pos = pos_init;
	handle = handle_init;
	move_f = move_f_init;
	move_v = move_v_init;
}
/*****
==============================
技クラスの初期化(引数:画像のデータハンドル, 描画間隔)
==============================
*****/
Skill::Skill(int handle_init, int drawinterval_init, int intervalcount_init)
{
	handle = handle_init;
	drawinterval = drawinterval_init;
	intervalcount = intervalcount_init;
}

/*****
==========================
技の描画 : Draw(Pos p, int handle, int drawinterval, int direction)
==========================
引数
Pos p : 表示する場所の左上座標
Pos dest: 画像から切り取る矩形の座標
int Width : 切り取る矩形の幅
int Height : 切り取る矩形の高さ
int handle : 技画像のデータハンドル
int drawinterval : 技を描画する間隔

=====================================
戻り値なし
==================================
*****/
void Skill::Draw(Pos p,int handle, int drawinterval)
{
	DrawGraph(p.x, p.y, handle, TRUE); //画像の描画
}


/*****
==========================
技の描画 : Draw(Pos p, int handle, int drawinterval, int direction)
==========================
引数
Pos p : 表示する場所の左上座標
Pos ep: 敵の座標
=====================================
1 : 敵と当たった判定
0: 当たっていない
==================================
*****/
int Hit_Enemy(Pos p, Pos ep)
{
	//敵との当たり判定
	if (p.x < ep.x + CHIP_SIZE-10 && p.y < ep.y + CHIP_SIZE-10 && (p.x + CHIP_SIZE) > ep.x+10 && (p.y + CHIP_SIZE) > ep.y+10)
		return 1;
	return 0;
}
