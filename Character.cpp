#include "Character.h"

/*****
====================
キャラクタ座標の初期化 : Character()
====================
*****/
Character::Character(int handle_init)
{
	handle = handle_init;
}

Character::~Character()
{// デストラクタ
		
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
Enemy::Enemy(int handle_init) : Character(handle_init)
{
	handle = handle_init;
}

Enemy::~Enemy()
{
	handle = -1;
	pos = { 2000 , 2000};
}
/*****
==============================
技クラスの初期化(引数:画像のデータハンドル, 描画間隔)
==============================
*****/
/*
Skill::Skill(int handle_init, int drawinterval_init, int intervalcount_init)
{
	handle = handle_init;
	drawinterval = drawinterval_init;
	intervalcount = intervalcount_init;
}
*/
/*****
==========================
技の描画 : Skill::Draw(Pos p, int handle, int drawinterval, int direction)
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
技の当たり判定: Skill::Hit(Pos p, Pos ep)
==========================
引数
Pos p : 敵キャラクタの座標
Pos sp: 技の座標

=====================================
戻り値
1 : ヒット
0 : ヒットなし
==================================
*****/
int Skill::Hit(Pos ep,Pos sp)
{
	//敵との当たり判定
	if (ep.x < sp.x + CHIP_SIZE && ep.y < sp.y + CHIP_SIZE  && (ep.x + CHIP_SIZE) > sp.x && (ep.y + CHIP_SIZE) > sp.y)
		return 1;
	return 0;
}

/*****
==========================
敵との当たり判定: Hit_Enemy(Pos p, Pos ep)
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
	if (p.x < ep.x+CHIP_SIZE/4 && p.y < ep.y + CHIP_SIZE && (p.x + CHIP_SIZE/2) > ep.x && (p.y + CHIP_SIZE) > ep.y)
		return 1;
	return 0;
}
