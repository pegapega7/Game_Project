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
void Character::Draw(Pos p, int handle, int chargeflag)
{
	if (chargeflag == 0) {
		DrawRectGraph(p.x, p.y, 0, 0, CHIP_SIZE, CHIP_SIZE, handle, TRUE, FALSE); //�摜�̕`��
	}
	else if (chargeflag == 1) {
		DrawRectGraph(p.x, p.y, CHIP_SIZE, 0, CHIP_SIZE, CHIP_SIZE, handle, TRUE, FALSE); //�摜�̕`��
	}
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
�G�Ǝ��@�̓����蔻��: Hit_Enemy( Character& c, Enemy& e)
==========================
����
Character& c : ���@�̏��
Enemy& e : �G�̏��
=====================================
1 : �G�Ɠ�����������
0: �������Ă��Ȃ�
==================================
*****/
int Hit_Enemy(Character& c, Enemy& e)
{
	//�G�Ƃ̓����蔻��
	if (c.pos.x < e.pos.x+CHIP_SIZE/4 && c.pos.y < e.pos.y + CHIP_SIZE && (c.pos.x + CHIP_SIZE/2) > e.pos.x && (c.pos.y + CHIP_SIZE) > e.pos.y)
		return 1;
	return 0;
}

/*****
==========================
�|�ƓG�̓����蔻��: Hit_Skill(Enemy& e, Skill& s)
==========================
����
Enemy& e :�@�G�̏��
Skill& s: �|�E�G�̍U���̏��
=====================================
1 : �G�Ɠ�����������
0: �������Ă��Ȃ�
==================================
*****/
int Hit_Skill(Enemy& e, Skill& s)
{
	//�G�Ƃ̓����蔻��
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
�G�̍U���Ɩ����̓����蔻��: Hit_Attack(Character& c, Skill& s)
==========================
����
Character& c :�@�G�̏��
Skill& s: �|�E�G�̍U���̏��
=====================================
1 : �G�Ɠ�����������
0: �������Ă��Ȃ�
==================================
*****/
int Hit_Attack(Character& c, Skill& s)
{
	//�G�Ƃ̓����蔻��
	if (c.pos.x + 16 < s.pos.x + 40 && c.pos.y < s.pos.y + 48 && (c.pos.x + 48) > s.pos.x + 8 && (c.pos.y + CHIP_SIZE) > s.pos.y + 8)
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
		int random = GetRand(4);//4�����̃����_��
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
