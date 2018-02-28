#include "Map.h"
#include "DxLib.h"


int MapData_init[MAP_HEIGHT][MAP_WIDTH]
{
	{ 0,0,0,0,0, 0,0,0,0,0 },
	{ 0,0,0,0,0, 0,0,0,0,0 },
	{ 0,0,0,0,0, 0,0,0,0,0 },
	{ 0,0,0,0,0, 0,0,0,0,0 },
	{ 0,0,0,0,0, 0,0,0,0,0 },

	{ 0,0,0,0,0, 0,0,0,0,0 },
	{ 0,0,0,0,0, 0,0,0,0,0 },
	{ 0,0,0,0,0, 0,0,0,0,0 },
	{ 0,0,0,0,0, 0,0,0,0,0 },
	{ 0,0,0,0,0, 0,0,0,0,0 },

	{ 3,2,2,2,2, 2,2,2,2,3 },
	{ 1,1,1,1,1, 1,1,1,1,1 },
};

int MapData[MAP_HEIGHT][MAP_WIDTH]
{
	{ 0,0,0,0,0, 0,0,0,0,0 },
	{ 0,0,0,0,0, 0,0,0,0,0 },
	{ 0,0,0,0,0, 0,0,0,0,0 },
	{ 0,0,0,0,0, 0,0,0,0,0 },
	{ 0,0,0,0,0, 0,0,0,0,0 },
	
	{ 0,0,0,0,0, 0,0,0,0,0 },
	{ 0,0,0,0,0, 0,0,0,0,0 },
	{ 0,0,0,0,0, 0,0,0,0,0 },
	{ 0,0,0,0,0, 0,0,0,0,0 },
	{ 0,0,0,0,0, 0,0,0,0,0 },

	{ 3,2,2,2,2, 2,2,2,2,3 },
	{ 1,1,1,1,1, 1,1,1,1,1 },
};

/*****
======================
�}�b�v�̏�����
======================
*****/
void Init_map()
{
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			MapData[i][j] = MapData_init[i][j];
		}
	}

}
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
			case 2:
				DrawGraph(j*CHIP_SIZE, i*CHIP_SIZE, map[2].handle, TRUE); //�����摜�̕`��
				break;
			case 3:
				DrawGraph(j*CHIP_SIZE, i*CHIP_SIZE, map[3].handle, TRUE); //�؉摜�̕`��
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
Character& c : ���@�̏��
===================
�߂�l
 1 : �����蔻�肠��
 0 : �����蔻��Ȃ� 
*****/
int Hit_map(MapElement map[], Character& c)
{
	////�}�b�v�Ƃ̓����蔻��v�Z
	//for (int i = 0; i < MAP_HEIGHT; i++)
	//{
	//	for (int j = 0; j < MAP_WIDTH; j++)
	//	{
	//		if (MapData[i][j] == 2) {//�}�b�v�`�b�v�z��̃f�[�^��2�i��ǁj�̎�
	//			if (p.x < (j + 1)*CHIP_SIZE-10 && p.y < (i + 1)*CHIP_SIZE-10 && (p.x + CHIP_SIZE) > j*CHIP_SIZE+10 && (p.y + CHIP_SIZE) > i*CHIP_SIZE+10)
	//				return 1;
	//		}
	//	}
	//}

	if (c.pos.x < 9 * CHIP_SIZE - 8 && c.pos.y <  11 * CHIP_SIZE - 16 && (c.pos.x + CHIP_SIZE) > CHIP_SIZE + 8 && (c.pos.y + CHIP_SIZE) > 10 * CHIP_SIZE)
		return 1;
	return 0;
}
