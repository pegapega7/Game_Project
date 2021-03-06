#pragma once
//ライブラリ
#ifndef _MAIN_H_INCLUDED_ //ヘッダが読み込まれてなかったら通る
#define _MAIN_H_INCLUDED_ //ヘッダを読み込んだら定義する⇒次にヘッダが読み込まれてもifndefに入らず無視できる
#include "DxLib.h"
#include "windows.h"
#include "sstream"
#include "vector"

using namespace std;

//定数定義
#define WINDOW_WIDTH  960
#define WINDOW_HEIGHT 768
#define MAP_WIDTH 10
#define MAP_HEIGHT 12
#define CHIP_SIZE 64
#define PI 3.1415926f

#define MAXCHARGE 512
#define ENEMY_TYPE_NUM 3
#define ENEMY_NUM 10

/*****
===========================
描画用構造体 : MenuElement
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

MenuElement Status[3] = {
	{650, 120, "HP", 1 }, 
	{650, 220, "耐久度", 1 },
	{650, 320, "スコア ", 1},
};

MenuElement MainMenu[2] = {
	{ 500, 500, "ゲームスタート", 1 }, // タグの中身の順番で格納される。xに80が、yに100が、nameに"ゲームスタート"が
	{ 500, 550, "ゲーム終了", 0 },
};

MenuElement debug[5] = {
	{ 640, 550, "キャラ座標(", 0 },
	{ 640, 600, "入力キー : ", 0 },
	{ 640, 650, "時間 : ",0},
	{ 640, 500, "侵入されたカウント ", 0 },
};

MenuElement manual[7] = {
	{ 670, 450, "操作方法", 0},
	{ 640, 500, "↑ ↓ ← →　: 移動", 0 },
	{ 640, 550, "Z(長押し) : 矢のチャージ", 0 },
	{ 640, 600, "Z(離す): 矢の発射",0 },
	{ 640, 650, "TIPS-矢をチャージするほど\n　 　弓が強くなるぞ!! ", 0 },
	{ 640, 650, "TIPS-防壁の上に登ると\n　 　直接攻撃を受けなくなるぞ!! ", 0 },
	{ 640, 650, "TIPS-敵に当たると\n　　 ＨＰを減らして敵が倒せるぞ!\n　 　うまく活用して防壁を守ろう!! ", 0 },
};

MenuElement Ending[2] = {
	{ 500, 500, "タイトルに戻る", 1 }, 
	{ 500, 550, "ゲーム終了", 0 },
};

MenuElement Gameover[2] = {
	{ 500, 500, "リトライ", 1 },
	{ 500, 550, "タイトルに戻る", 0 },
};


#endif

