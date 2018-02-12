#pragma once
#ifndef _CHARACTER_H_INCLUDED_ //ヘッダが読み込まれてなかったら通る
#define _CHARACTER_H_INCLUDED_ //ヘッダを読み込んだら定義する⇒次にヘッダが読み込まれてもifndefに入らず無視できる
#include "DxLib.h"


//定数定義
#define WINDOW_WIDTH  960
#define WINDOW_HEIGHT 768
#define MAP_WIDTH 10
#define MAP_HEIGHT 12
#define CHIP_SIZE 64


/*****
===========================
座標
===========================
int x : x座標
int y : y座標
*****/
typedef struct {
	int x;
	int y;
} Pos;

/*****
=============================
キャラクター用のクラス
=============================
メンバ
int handle : キャラクタ画像のデータハンドル
Pos pos : キャラクタの座標（画像の左上）
=============================
メソッド
Character() : キャラクタの初期設定
void Draw(Pos p,int handle) : キャラクタ画像の表示
=============================
*****/
class Character
{
private:
public:
	Pos pos;
	int move_f;//1で移動状態,0で未移動状態
	int move_v;//移動している向き
	int handle;

	Character(Pos pos_init, int handle_init, int move_f_init, int move_v_init);
	void Draw(Pos p, int handle);
};

#endif