#pragma once
//ライブラリ
#ifndef _MAIN_H_INCLUDED_ //ヘッダが読み込まれてなかったら通る
#define _MAIN_H_INCLUDED_ //ヘッダを読み込んだら定義する⇒次にヘッダが読み込まれてもifndefに入らず無視できる
#include "DxLib.h"
#include "windows.h"
#include <iostream>
#include <stdio.h>

//定数定義
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 960

typedef struct {
	int x;
	int y;
} Pos;

typedef struct {
	int x, y;       // 座標格納用変数
	char name[128]; // 項目名格納用変数
	int flag;
} MenuElement_t;

#endif

