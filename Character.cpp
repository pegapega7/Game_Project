#include "Character.h"

/*****
====================
�L�����N�^���W�̏����� : Character()
====================
*****/
Character::Character(int handle_init)
{
	handle = handle_init;
}

Character::~Character()
{// �f�X�g���N�^
		
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
void Enemy::Draw(Pos p, int handle)
{
	DrawGraph(p.x, p.y, handle, TRUE); //�摜�̕`��
}

/*****
==============================
�Z�N���X�̏�����(����:�摜�̃f�[�^�n���h��, �`��Ԋu)
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
�Z�̕`�� : Skill::Draw(Pos p, int handle, int drawinterval, int direction)
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
�Z�̓����蔻��: Skill::Hit(Pos p, Pos ep)
==========================
����
Pos ep : �G�L�����N�^�̍��W
Pos sp: �Z�̍��W

=====================================
�߂�l
1 : �q�b�g
0 : �q�b�g�Ȃ�
==================================
*****/
int Skill::Hit(Pos ep,Pos sp)
{
	//�G�Ƃ̓����蔻��
	if (ep.x+24 < sp.x + CHIP_SIZE/2 && ep.y < sp.y + CHIP_SIZE && (ep.x + 40) > sp.x && (ep.y + CHIP_SIZE) > sp.y)
		return 1;
	return 0;
}

/*****
==========================
�G�Ƃ̓����蔻��: Hit_Enemy(Pos p, Pos ep)
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
	if (p.x < ep.x+CHIP_SIZE/4 && p.y < ep.y + CHIP_SIZE && (p.x + CHIP_SIZE/2) > ep.x && (p.y + CHIP_SIZE) > ep.y)
		return 1;
	return 0;
}

/*****
=====================================
�G�̎�ނ��ƂɈړ�������� : void Move_enemy(Enemy e)
=====================================
����
Enemy e : �G�̃N���X
=====================================
�߂�l
�Ȃ�
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
		e.pos.x += std::cos(135 * PI / 180)*e.speed;
		e.pos.y += std::sin(135 * PI / 180)*e.speed;
		break;

	case 2:
		e.pos.y = e.pos.y + e.speed;
		break;
	default : 
		break;
	}

	if (e.pos.y > (MAP_HEIGHT - 1)*CHIP_SIZE) 
	{ 
		e.enemy_clearflag = 1; 
		e.aliveflag = 0;
	}
}
