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
マップの初期化
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
			case 2:
				DrawGraph(j*CHIP_SIZE, i*CHIP_SIZE, map[2].handle, TRUE); //草原画像の描画
				break;
			case 3:
				DrawGraph(j*CHIP_SIZE, i*CHIP_SIZE, map[3].handle, TRUE); //木画像の描画
				break;
			default:
				break;
			}
		}
	}
}

/*****
===================
マップとの当たり判定(進めるかどうか)
===================
引数
MapElement map[] : マップチップ情報
Character& c : 自機の情報
===================
戻り値
 1 : 当たり判定あり
 0 : 当たり判定なし 
*****/
int Hit_map(MapElement map[], Character& c)
{
	////マップとの当たり判定計算
	//for (int i = 0; i < MAP_HEIGHT; i++)
	//{
	//	for (int j = 0; j < MAP_WIDTH; j++)
	//	{
	//		if (MapData[i][j] == 2) {//マップチップ配列のデータが2（城壁）の時
	//			if (p.x < (j + 1)*CHIP_SIZE-10 && p.y < (i + 1)*CHIP_SIZE-10 && (p.x + CHIP_SIZE) > j*CHIP_SIZE+10 && (p.y + CHIP_SIZE) > i*CHIP_SIZE+10)
	//				return 1;
	//		}
	//	}
	//}

	if (c.pos.x < 9 * CHIP_SIZE - 8 && c.pos.y <  11 * CHIP_SIZE - 16 && (c.pos.x + CHIP_SIZE) > CHIP_SIZE + 8 && (c.pos.y + CHIP_SIZE) > 10 * CHIP_SIZE)
		return 1;
	return 0;
}
