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
