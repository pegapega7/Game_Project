#include "Character.h"

/*****
�L�����N�^�N���X�̏�����
*****/
Character::Character(int handle_init)
{
	handle = handle_init;
}


/*****
�L�����N�^�摜��\��
*****/
void Character::Draw()
{
	if (chargeflag == 0) {//�ҋ@��Ԃ̉摜
		DrawRectGraph(pos.x, pos.y, 0, 0, CHIP_SIZE, CHIP_SIZE, handle, TRUE, FALSE);
	}
	else if (chargeflag == 1) {//�`���[�W���̉摜
		if (charge_count <= 50) {
			DrawRectGraph(pos.x, pos.y, CHIP_SIZE, 0, CHIP_SIZE, CHIP_SIZE, handle, TRUE, FALSE);
		}
		else if(50 < charge_count && charge_count <= 75) {
			SetDrawBlendMode(DX_BLENDMODE_ADD, 128); 
			DrawRectGraph(pos.x + 5, pos.y, CHIP_SIZE, 0, CHIP_SIZE, CHIP_SIZE, handle, TRUE, FALSE);
			DrawRectGraph(pos.x - 5, pos.y, CHIP_SIZE, 0, CHIP_SIZE, CHIP_SIZE, handle, TRUE, FALSE);
			DrawRectGraph(pos.x, pos.y + 5, CHIP_SIZE, 0, CHIP_SIZE, CHIP_SIZE, handle, TRUE, FALSE);
			DrawRectGraph(pos.x, pos.y - 5, CHIP_SIZE, 0, CHIP_SIZE, CHIP_SIZE, handle, TRUE, FALSE); 

			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);  
			DrawRectGraph(pos.x, pos.y, CHIP_SIZE, 0, CHIP_SIZE, CHIP_SIZE, handle, TRUE, FALSE);
		}
		else {
			SetDrawBlendMode(DX_BLENDMODE_ADD, 128);   
			DrawRectGraph(pos.x + 5, pos.y, CHIP_SIZE, 0, CHIP_SIZE, CHIP_SIZE, handle, TRUE, FALSE); 
			DrawRectGraph(pos.x - 5, pos.y, CHIP_SIZE, 0, CHIP_SIZE, CHIP_SIZE, handle, TRUE, FALSE); 
			DrawRectGraph(pos.x, pos.y + 5, CHIP_SIZE, 0, CHIP_SIZE, CHIP_SIZE, handle, TRUE, FALSE);
			DrawRectGraph(pos.x, pos.y - 5, CHIP_SIZE, 0, CHIP_SIZE, CHIP_SIZE, handle, TRUE, FALSE);
			DrawRectGraph(pos.x + 5, pos.y - 5, CHIP_SIZE, 0, CHIP_SIZE, CHIP_SIZE, handle, TRUE, FALSE); 
			DrawRectGraph(pos.x - 5, pos.y - 5, CHIP_SIZE, 0, CHIP_SIZE, CHIP_SIZE, handle, TRUE, FALSE); 
			DrawRectGraph(pos.x + 5, pos.y + 5, CHIP_SIZE, 0, CHIP_SIZE, CHIP_SIZE, handle, TRUE, FALSE);
			DrawRectGraph(pos.x - 5, pos.y + 5, CHIP_SIZE, 0, CHIP_SIZE, CHIP_SIZE, handle, TRUE, FALSE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);  
			DrawRectGraph(pos.x, pos.y, CHIP_SIZE, 0, CHIP_SIZE, CHIP_SIZE, handle, TRUE, FALSE);
		}
	}
}


/*****
�G�̏�����
*****/
Enemy::Enemy(int enemytype_init)
{
	enemytype = enemytype_init;
}

/*****
�G�摜��\�� 
*****/
void Enemy::Draw()
{
	if (pos.y >= 9 * CHIP_SIZE && (pos.x >= CHIP_SIZE && pos.x < (MAP_WIDTH-1) * CHIP_SIZE)) {
		SetDrawBlendMode(DX_BLENDMODE_ADD, 128);          
		DrawGraph(pos.x, pos.y, handle, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else  {
		DrawGraph(pos.x, pos.y, handle, TRUE);
	}
}

/*****
��̉摜��\��
*****/
void Skill::Draw()
{
	DrawGraph(pos.x, pos.y, handle, TRUE); //�摜�̕`��
}




/*****
�G�Ǝ��@�̓����蔻��
*****/
int Hit_Enemy(Character& c, Enemy& e)
{
	if (e.enemytype == 3) {//�{�X�̎�
		if (c.pos.x < e.pos.x + CHIP_SIZE * 2 - CHIP_SIZE / 4 && c.pos.y < e.pos.y + CHIP_SIZE * 2 - CHIP_SIZE / 4 && (c.pos.x + CHIP_SIZE / 2) > e.pos.x && (c.pos.y + CHIP_SIZE) > e.pos.y)
			return 1;

	}
	else {
		if (c.pos.x < e.pos.x + CHIP_SIZE / 4 && c.pos.y < e.pos.y + CHIP_SIZE && (c.pos.x + CHIP_SIZE / 2) > e.pos.x && (c.pos.y + CHIP_SIZE) > e.pos.y)
			return 1;
	}
	return 0;
}

/*****
�|�ƓG�̓����蔻��
*****/
int Hit_Skill(Enemy& e, Skill& s)
{
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
�G�̍U���Ɩ����̓����蔻��
*****/
int Hit_Attack(Character& c, Skill& s)
{
	if (c.pos.x + 16 < s.pos.x + 40 && c.pos.y < s.pos.y + 48 && (c.pos.x + 48) > s.pos.x + 8 && (c.pos.y + CHIP_SIZE) > s.pos.y + 8)
		return 1;

	return 0;
}


/*****
�G�̎�ނ��ƂɈړ��������
*****/
void Move_enemy(Enemy& e)
{
	Pos oldp = e.pos;
	switch (e.enemytype) {
	case 0:
		e.pos.y = e.pos.y + e.speed;
		break;
	case 1: 
		if (e.pos.y < 9 * CHIP_SIZE)
		{
			if (e.move_pattern == 0) {
				e.pos.x += std::cos(135 * PI / 180)*e.speed;
				e.pos.y += std::sin(135 * PI / 180)*e.speed;
			}
			else if (e.move_pattern == 1) {
				e.pos.x += std::cos(45 * PI / 180)*e.speed;
				e.pos.y += std::sin(45 * PI / 180)*e.speed;
			}
			if (e.move_pattern == 0 && e.pos.x < 0)	e.move_pattern = 1;
			else if (e.move_pattern == 1 && e.pos.x > (MAP_WIDTH - 1)*CHIP_SIZE) e.move_pattern = 0;
		}
		else
		{
			e.pos.y = e.pos.y + std::sin(90 * PI / 180)*e.speed;
		}
		break;
	case 2:
		e.pos.y = e.pos.y + e.speed;
		break;
	case 3:
	{
		int random = GetRand(4);
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
