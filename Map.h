#pragma once

#ifndef _MAP_H_INCLUDED_ //ヘッダが読み込まれてなかったら通る
#define _MAP_H_INCLUDED_ //ヘッダを読み込んだら定義する⇒次にヘッダが読み込まれてもifndefに入らず無視できる

#include "Character.h"
// 定数定義
#define WINDOW_WIDTH  960
#define WINDOW_HEIGHT 768
#define MAP_WIDTH 10
#define MAP_HEIGHT 12
#define CHIP_SIZE 64


/*****
===========================
マップチップの構造体
===========================
int handle : 画像呼び出し用のデータハンドル
int hitflag : マップごとの当たり判定 (0:通常マップ、1：通り抜け不可、２：ダメージ床(未実装))
*****/
typedef struct {
	int handle;
	int hitflag;
} MapElement;


extern void Init_map();
extern void Draw_map(MapElement map[]);
extern int Hit_map(MapElement map[], Character& c);
#endif
