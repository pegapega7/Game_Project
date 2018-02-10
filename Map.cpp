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
ゲームマップを描画
======================
引数
MapElement map[] : マップチップ情報
*****/
void Draw_map(MapElement map[])
{
	//マップチップ配置
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			switch (MapData[i][j]) {
			case 0:
				DrawGraph(j*CHIP_SIZE, i*CHIP_SIZE, map[0].handle, TRUE); //草原画像の描画
				break;
			case 1:
				DrawGraph(j*CHIP_SIZE, i*CHIP_SIZE, map[1].handle, TRUE); //木画像の描画
				break;
			default:
				break;
			}
		}
	}
}