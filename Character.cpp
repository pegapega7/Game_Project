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
void Character::Draw(Pos p, int handle, int chargeflag)
{
	if (chargeflag == 0) {
		DrawRectGraph(p.x, p.y, 0, 0, CHIP_SIZE, CHIP_SIZE, handle, TRUE, FALSE); //画像の描画
	}
	else if (chargeflag == 1) {
		DrawRectGraph(p.x, p.y, CHIP_SIZE, 0, CHIP_SIZE, CHIP_SIZE, handle, TRUE, FALSE); //画像の描画
	}
}


/*****
====================
敵の初期化
====================
*****/
Enemy::Enemy(int enemytype_init)
{
	enemytype = enemytype_init;
}

Enemy::~Enemy()
{
	handle = -1;
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
void Enemy::Draw(Pos p, int handle)
{
	DrawGraph(p.x, p.y, handle, TRUE); //画像の描画
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
Pos ep : 敵キャラクタの座標
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
	if (ep.x+24 < sp.x + CHIP_SIZE/2 && ep.y < sp.y + CHIP_SIZE && (ep.x + 40) > sp.x && (ep.y + CHIP_SIZE) > sp.y)
		return 1;
	return 0;
}

/*****
==========================
敵と自機の当たり判定: Hit_Enemy( Character& c, Enemy& e)
==========================
引数
Character& c : 自機の情報
Enemy& e : 敵の情報
=====================================
1 : 敵と当たった判定
0: 当たっていない
==================================
*****/
int Hit_Enemy(Character& c, Enemy& e)
{
	//敵との当たり判定
	if (c.pos.x < e.pos.x+CHIP_SIZE/4 && c.pos.y < e.pos.y + CHIP_SIZE && (c.pos.x + CHIP_SIZE/2) > e.pos.x && (c.pos.y + CHIP_SIZE) > e.pos.y)
		return 1;
	return 0;
}

/*****
==========================
弓と敵の当たり判定: Hit_Skill(Enemy& e, Skill& s)
==========================
引数
Enemy& e :　敵の情報
Skill& s: 弓・敵の攻撃の情報
=====================================
1 : 敵と当たった判定
0: 当たっていない
==================================
*****/
int Hit_Skill(Enemy& e, Skill& s)
{
	//敵との当たり判定
	switch (e.enemytype) {
	case 0:
		if (e.pos.x + 16 < s.pos.x + 40 && e.pos.y < s.pos.y + CHIP_SIZE && (e.pos.x + 48) > s.pos.x + 8 && (e.pos.y + CHIP_SIZE) > s.pos.y) 
			return 1;
		break;
	case 1:
		if (e.pos.x + 16 < s.pos.x + 40 && e.pos.y < s.pos.y + CHIP_SIZE && (e.pos.x + 48) > s.pos.x + 8 && (e.pos.y + CHIP_SIZE) > s.pos.y) 
			return 1;
		break;
	case 2:
		if (e.pos.x + 16 < s.pos.x + 40 && e.pos.y < s.pos.y + CHIP_SIZE && (e.pos.x + 48) > s.pos.x + 8 && (e.pos.y + CHIP_SIZE) > s.pos.y)
			return 1;
		break;
	case 3:
		if (e.pos.x + 16 < s.pos.x + 40 && e.pos.y < s.pos.y + CHIP_SIZE && (e.pos.x + 112) > s.pos.x + 8 && (e.pos.y + CHIP_SIZE) > s.pos.y) 
			return 1;
		break;
	default:
		break;
	}
	return 0;
}

/*****
==========================
敵の攻撃と味方の当たり判定: Hit_Attack(Character& c, Skill& s)
==========================
引数
Character& c :　敵の情報
Skill& s: 弓・敵の攻撃の情報
=====================================
1 : 敵と当たった判定
0: 当たっていない
==================================
*****/
int Hit_Attack(Character& c, Skill& s)
{
	//敵との当たり判定
	if (c.pos.x + 16 < s.pos.x + 40 && c.pos.y < s.pos.y + 48 && (c.pos.x + 48) > s.pos.x + 8 && (c.pos.y + CHIP_SIZE) > s.pos.y + 8)
		return 1;
	return 0;
}


/*****
=====================================
敵の種類ごとに移動先を決定 : void Move_enemy(Enemy e)
=====================================
引数
Enemy e : 敵のクラス
=====================================
戻り値
なし
=====================================
*****/
void Move_enemy(Enemy& e)
{
	Pos oldp = e.pos;
	switch (e.enemytype) {
	case 0:
		e.pos.y = e.pos.y + e.speed;
		break;
	case 1: 
		if (e.move_pattern == 0) {
			e.pos.x += std::cos(135 * PI / 180)*e.speed;
			e.pos.y += std::sin(135 * PI / 180)*e.speed;
		}
		else if(e.move_pattern == 1) {
			e.pos.x += std::cos(45 * PI / 180)*e.speed;
			e.pos.y += std::sin(45 * PI / 180)*e.speed;
		}
		if (e.move_pattern == 0 && e.pos.x < 0)	e.move_pattern = 1;
		else if (e.move_pattern == 1 && e.pos.x > (MAP_WIDTH-1)*CHIP_SIZE) e.move_pattern = 0;
		break;
	case 2:
		e.pos.y = e.pos.y + e.speed;
		break;
	case 3:
	{
		int random = GetRand(4);//4方向のランダム
		if (e.move_pattern == 0) {
			e.pos.x -= e.speed;
			switch (random) {
			case 0:
				e.pos.y += std::sin(45 * random * PI / 180)*e.speed;
				break;
			case 1:
				e.pos.y += std::sin(135 * random * PI / 180)*e.speed;
				break;
			case 2:
				e.pos.y += std::sin(225 * random * PI / 180)*e.speed;
				break;
			case 3:
				e.pos.y += std::sin(315 * random * PI / 180)*e.speed;
				break;
			default: break;
			}
		}
		else if (e.move_pattern == 1) {
			e.pos.x += e.speed;
			switch (random) {
			case 0:
				e.pos.y += std::sin(45 * random * PI / 180)*e.speed;
				break;
			case 1:
				e.pos.y += std::sin(135 * random * PI / 180)*e.speed;
				break;
			case 2:
				e.pos.y += std::sin(225 * random * PI / 180)*e.speed;
				break;
			case 3:
				e.pos.y += std::sin(315 * random * PI / 180)*e.speed;
				break;
			default: break;
			}
		}
		if (e.move_pattern == 0 && e.pos.x < 0)	e.move_pattern = 1;
		else if (e.move_pattern == 1 && e.pos.x > (MAP_WIDTH - 2)*CHIP_SIZE) e.move_pattern = 0;

		if (e.pos.y < 5) e.pos.y = oldp.y;
		if (e.pos.y > 64) e.pos.y = oldp.y;
		break;
	}
	default : 
		break;
	}

	if (e.pos.y > (MAP_HEIGHT - 1)*CHIP_SIZE) 
	{ 
		e.enemy_clearflag = 1; 
		e.aliveflag = 0;
	}
}
