#include "Main.h"
#include "Character.h"

Character::Character()
{
	pos.x = 500;
	pos.y = 500;
}

void Character::Draw(Pos p, int handle)
{
	DrawGraph(p.x, p.y, handle, TRUE); //‰æ‘œ‚Ì•`‰æ
}
