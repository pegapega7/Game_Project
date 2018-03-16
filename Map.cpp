#include "Map.h"
#include "DxLib.h"


//マップの初期状態
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

//マップの状態を保存
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
マップの初期化
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
ゲームマップを描画
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
				DrawGraph(j*CHIP_SIZE, i*CHIP_SIZE, map[0].handle, TRUE);  //マップ番号０：草
				break;
			case 1:
				DrawGraph(j*CHIP_SIZE, i*CHIP_SIZE, map[1].handle, TRUE);  //マップ番号１：床
				break;
			case 2:
				DrawGraph(j*CHIP_SIZE, i*CHIP_SIZE, map[2].handle, TRUE);  //マップ番号２：城壁
				break;
			case 3:
				DrawGraph(j*CHIP_SIZE, i*CHIP_SIZE, map[3].handle, TRUE);  //マップ番号３：階段
				break;
			default:
				break;
			}
		}
	}
}

/*****
マップとの当たり判定(0:あたりなし，1:あたり)
*****/
int Hit_map(MapElement map[], Character& c)
{
	if (c.pos.x < 9 * CHIP_SIZE - 8 && c.pos.y <  11 * CHIP_SIZE - 16 && (c.pos.x + CHIP_SIZE) > CHIP_SIZE + 8 && (c.pos.y + CHIP_SIZE) > 10 * CHIP_SIZE)
		return 1;
	return 0;
}
