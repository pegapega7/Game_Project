#include "Character.h"

/*****
====================
�L�����N�^���W�̏����� : Character()
====================
*****/
Character::Character()
{
	pos.x = 500;
	pos.y = 500;
}

/*****
====================
�L�����N�^�摜��\�� : Draw(Pos p, int handle)
====================
����
Pos p : �L�����N�^�̍��W
int handle : �f�[�^�n���h��
====================
�߂�l
�Ȃ�
====================

*****/
void Character::Draw(Pos p, int handle)
{
	DrawGraph(p.x, p.y, handle, TRUE); //�摜�̕`��
}
