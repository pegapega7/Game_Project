#pragma once
//ライブラリ
#ifndef _MAIN_H_INCLUDED_ //ヘッダが読み込まれてなかったら通る
#define _MAIN_H_INCLUDED_ //ヘッダを読み込んだら定義する⇒次にヘッダが読み込まれてもifndefに入らず無視できる
#include "DxLib.h"
#include "windows.h"
#include "sstream"

using namespace std;

//定数定義
#define WINDOW_WIDTH  960
#define WINDOW_HEIGHT 768
#define MAP_WIDTH 10
#define MAP_HEIGHT 12
#define CHIP_SIZE 64

/*****
===========================
描画用構造体
===========================
int x : x座標
int y : y座標
char name[128] : 表示する文字列
int flag : 選択中かどうかのフラグ(1:選択中 0:未選択)
*****/
typedef struct {
	int x, y;       // 座標格納用変数
	string name; // 項目名格納用変数
	int flag;
} MenuElement;

MenuElement MainMenu[2] = {
	{ 500, 500, "ゲームスタート", 1 }, // タグの中身の順番で格納される。xに80が、yに100が、nameに"ゲームスタート"が
	{ 500, 550, "ゲーム終了", 0 },
};

MenuElement debug[1] = {
	{ 768, 550, "キャラ座標(", 0 },
};

#endif

