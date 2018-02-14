#include "Character.h"

/*****
====================
�L�����N�^���W�̏����� : Character()
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


/*****
====================
�G�̏�����
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
�Z�N���X�̏�����(����:�摜�̃f�[�^�n���h��, �`��Ԋu)
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
�Z�̕`�� : Draw(Pos p, int handle, int drawinterval, int direction)
==========================
����
Pos p : �\������ꏊ�̍�����W
Pos dest: �摜����؂����`�̍��W
int Width : �؂����`�̕�
int Height : �؂����`�̍���
int handle : �Z�摜�̃f�[�^�n���h��
int drawinterval : �Z��`�悷��Ԋu

=====================================
�߂�l�Ȃ�
==================================
*****/
void Skill::Draw(Pos p,int handle, int drawinterval)
{
	DrawGraph(p.x, p.y, handle, TRUE); //�摜�̕`��
}


/*****
==========================
�Z�̕`�� : Draw(Pos p, int handle, int drawinterval, int direction)
==========================
����
Pos p : �\������ꏊ�̍�����W
Pos ep: �G�̍��W
=====================================
1 : �G�Ɠ�����������
0: �������Ă��Ȃ�
==================================
*****/
int Hit_Enemy(Pos p, Pos ep)
{
	//�G�Ƃ̓����蔻��
	if (p.x < ep.x + CHIP_SIZE-10 && p.y < ep.y + CHIP_SIZE-10 && (p.x + CHIP_SIZE) > ep.x+10 && (p.y + CHIP_SIZE) > ep.y+10)
		return 1;
	return 0;
}
