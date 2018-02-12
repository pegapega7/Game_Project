#include "Map.h"
#include "DxLib.h"


int MapData[MAP_HEIGHT][MAP_WIDTH]
{
	{ 1,1,1,1,1, 0,0,0,1,1 },
	{ 1,0,0,0,0, 0,0,0,0,1 },
	{ 1,0,0,0,0, 0,0,0,0,1 },
	{ 1,0,0,0,0, 0,0,0,0,1 },
	{ 1,0,0,0,0, 0,0,0,0,1 },
	
	{ 1,0,0,0,1, 0,0,0,0,1 },
	{ 0,0,0,0,0, 0,0,0,0,0 },
	{ 0,0,0,0,0, 0,0,0,0,0 },
	{ 0,0,0,0,0, 0,0,0,0,0 },
	{ 0,0,0,0,0, 0,0,0,0,0 },

	{ 1,0,0,0,0, 0,0,0,0,1 },
	{ 1,1,1,1,0, 0,0,1,1,1 },
};

/*****
======================
�Q�[���}�b�v��`��
======================
����
MapElement map[] : �}�b�v�`�b�v���
*****/
void Draw_map(MapElement map[])
{
	//�}�b�v�`�b�v�z�u
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			switch (MapData[i][j]) {
			case 0:
				DrawGraph(j*CHIP_SIZE, i*CHIP_SIZE, map[0].handle, TRUE); //�����摜�̕`��
				break;
			case 1:
				DrawGraph(j*CHIP_SIZE, i*CHIP_SIZE, map[1].handle, TRUE); //�؉摜�̕`��
				break;
			default:
				break;
			}
		}
	}
}

/*****
===================
�}�b�v�Ƃ̓����蔻��(�i�߂邩�ǂ���)
===================
����
MapElement map[] : �}�b�v�`�b�v���
int hitflag : �ǂ̌����ɓ����������i�E0��1��2��3�j
int p : ���L�����N�^�̈ړ���̍��W
int oldp : ���L�����N�^�̈ړ��O�̍��W
===================
�߂�l
//int p : �����蔻�肪�Ȃ��������͈ړ���̍��W��Ԃ�
//int oldp : �����蔻�肪�Ȃ��������͈ړ��O�̍��W��Ԃ�
 1 : �����蔻�肠��
 0 : �����蔻��Ȃ� 
*****/
int Hit_map(MapElement map[], int hitflag, Pos p, Pos oldp)
{
	/*
	if (p.x%CHIP_SIZE == 0 || p.y%CHIP_SIZE == 0) {//�`�b�v�T�C�Y�i�U�S�j�Ŋ����Ƃ����������蔻��̌v�Z
		if (hitflag == 0) {//�E����ڐG
			if (p.y == 0 || p.y == (MAP_HEIGHT - 1)*CHIP_SIZE)
				if (MapData[p.y / CHIP_SIZE][p.x / CHIP_SIZE + 1] == 1) return 1;
			if (MapData[p.y / CHIP_SIZE][p.x / CHIP_SIZE + 1] == 1 /*|| MapData[p.y / CHIP_SIZE + 1][p.x / CHIP_SIZE + 1]* == 1) return 1;
		}
		else if (hitflag == 1) {//�ォ��ڐG
			if (p.x == 0 || p.x == (MAP_WIDTH - 1)*CHIP_SIZE)
				if (MapData[p.y / CHIP_SIZE + 1][p.x / CHIP_SIZE] == 1) return 1;
			if (MapData[p.y / CHIP_SIZE + 1][p.x / CHIP_SIZE] == 1 /*|| MapData[p.y / CHIP_SIZE + 1][p.x / CHIP_SIZE + 1]* == 1) return 1;
		}
		else if (hitflag == 2) {//������ڐG
			if (p.y == 0 || p.y == (MAP_HEIGHT - 1)*CHIP_SIZE)
				if (MapData[p.y / CHIP_SIZE][p.x / CHIP_SIZE - 1] == 1) return 1;
			if (MapData[p.y / CHIP_SIZE][p.x / CHIP_SIZE - 1] == 1 /*|| MapData[p.y / CHIP_SIZE + 1][p.x / CHIP_SIZE - 1]* == 1) return 1;
		}
		else if (hitflag == 3) {//������ڐG
			if (p.x == 0 || p.x == (MAP_WIDTH - 1)*CHIP_SIZE)
				if (MapData[p.y / CHIP_SIZE - 1][p.x / CHIP_SIZE] == 1) return 1;
			if (MapData[p.y / CHIP_SIZE - 1][p.x / CHIP_SIZE] == 1 /*|| MapData[p.y / CHIP_SIZE - 1][p.x / CHIP_SIZE + 1]* == 1) return 1;
		}
	}
	*/

	//�}�b�v�Ƃ̓����蔻��v�Z
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (MapData[i][j] == 1) {//�}�b�v�`�b�v�z��̃f�[�^��1�i�؁j�̎�
				if (p.x < (j + 1)*CHIP_SIZE && p.y < (i + 1)*CHIP_SIZE && (p.x + CHIP_SIZE) > j*CHIP_SIZE && (p.y + CHIP_SIZE) > i*CHIP_SIZE)
					return 1;
			}
		}
	}


	return 0;
}
