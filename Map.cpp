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
	/*
	if (p.x%CHIP_SIZE == 0 || p.y%CHIP_SIZE == 0) {//チップサイズ（６４）で割れるときだけ当たり判定の計算
		if (hitflag == 0) {//右から接触
			if (p.y == 0 || p.y == (MAP_HEIGHT - 1)*CHIP_SIZE)
				if (MapData[p.y / CHIP_SIZE][p.x / CHIP_SIZE + 1] == 1) return 1;
			if (MapData[p.y / CHIP_SIZE][p.x / CHIP_SIZE + 1] == 1 /*|| MapData[p.y / CHIP_SIZE + 1][p.x / CHIP_SIZE + 1]* == 1) return 1;
		}
		else if (hitflag == 1) {//上から接触
			if (p.x == 0 || p.x == (MAP_WIDTH - 1)*CHIP_SIZE)
				if (MapData[p.y / CHIP_SIZE + 1][p.x / CHIP_SIZE] == 1) return 1;
			if (MapData[p.y / CHIP_SIZE + 1][p.x / CHIP_SIZE] == 1 /*|| MapData[p.y / CHIP_SIZE + 1][p.x / CHIP_SIZE + 1]* == 1) return 1;
		}
		else if (hitflag == 2) {//左から接触
			if (p.y == 0 || p.y == (MAP_HEIGHT - 1)*CHIP_SIZE)
				if (MapData[p.y / CHIP_SIZE][p.x / CHIP_SIZE - 1] == 1) return 1;
			if (MapData[p.y / CHIP_SIZE][p.x / CHIP_SIZE - 1] == 1 /*|| MapData[p.y / CHIP_SIZE + 1][p.x / CHIP_SIZE - 1]* == 1) return 1;
		}
		else if (hitflag == 3) {//下から接触
			if (p.x == 0 || p.x == (MAP_WIDTH - 1)*CHIP_SIZE)
				if (MapData[p.y / CHIP_SIZE - 1][p.x / CHIP_SIZE] == 1) return 1;
			if (MapData[p.y / CHIP_SIZE - 1][p.x / CHIP_SIZE] == 1 /*|| MapData[p.y / CHIP_SIZE - 1][p.x / CHIP_SIZE + 1]* == 1) return 1;
		}
	}
	*/

	//マップとの当たり判定計算
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (MapData[i][j] == 1) {//マップチップ配列のデータが1（木）の時
				if (p.x < (j + 1)*CHIP_SIZE && p.y < (i + 1)*CHIP_SIZE && (p.x + CHIP_SIZE) > j*CHIP_SIZE && (p.y + CHIP_SIZE) > i*CHIP_SIZE)
					return 1;
			}
		}
	}


	return 0;
}
