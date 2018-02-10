#include "Character.h"

/*****
====================
キャラクタ座標の初期化 : Character()
====================
*****/
Character::Character()
{
	pos.x = 500;
	pos.y = 500;
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
