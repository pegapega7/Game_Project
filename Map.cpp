#include "Map.h"
#include "DxLib.h"


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

	{ 0,0,0,0,0, 0,0,0,0,0 },
	{ 0,0,0,0,0, 0,0,0,0,0 },
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

/*****
===================
マップとの当たり判定(進めるかどうか)
===================
引数
MapElement map[] : マップチップ情報
int hitflag : どの向きに当たったか（右0下1左2上3）
int p : 自キャラクタの移動後の座標
int oldp : 自キャラクタの移動前の座標
===================
戻り値
//int p : 当たり判定がなかった時は移動後の座標を返す
//int oldp : 当たり判定がなかった時は移動前の座標を返す
 1 : 当たり判定あり
 0 : 当たり判定なし 
*****/
int Hit_map(MapElement map[], int hitflag, Pos p, Pos oldp)
{
	//マップとの当たり判定計算
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (MapData[i][j] == 1) {//マップチップ配列のデータが1（木）の時
				if (p.x < (j + 1)*CHIP_SIZE-10 && p.y < (i + 1)*CHIP_SIZE-10 && (p.x + CHIP_SIZE) > j*CHIP_SIZE+10 && (p.y + CHIP_SIZE) > i*CHIP_SIZE+10)
					return 1;
			}
		}
	}


	return 0;
}
