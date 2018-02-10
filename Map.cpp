#include "Map.h"
#include "DxLib.h"


int MapData[MAP_HEIGHT][MAP_WIDTH]
{
	{ 0,0,0,0,0, 0, 0,0,0,0,0 },
	{ 0,0,1,0,0, 0, 0,0,0,0,0 },
	{ 0,0,0,0,0, 0, 0,0,1,0,0 },
	{ 0,0,0,1,0, 0, 0,0,0,0,0 },
	{ 0,0,0,0,0, 0, 0,0,0,0,0 },
	
	{ 0,0,0,0,0, 0, 0,0,0,0,0 },
	{ 0,0,0,0,0, 0, 0,0,0,0,0 },
	{ 0,0,0,1,0, 0, 0,0,0,0,0 },
	{ 0,0,0,0,0, 0, 0,1,0,0,0 },
	{ 0,1,0,0,0, 0, 0,0,0,0,0 },

	{ 0,0,0,1,0, 0, 0,0,0,0,0 },
	{ 0,0,0,0,0, 0, 0,0,0,0,0 },
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