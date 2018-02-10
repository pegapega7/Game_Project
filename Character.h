#pragma once
#ifndef _CHARACTER_H_INCLUDED_ //ヘッダが読み込まれてなかったら通る
#define _CHARACTER_H_INCLUDED_ //ヘッダを読み込んだら定義する⇒次にヘッダが読み込まれてもifndefに入らず無視できる
#include "DxLib.h"
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
	int handle;
	Pos pos;
	Character();
	void Draw(Pos p, int handle);
};

#endif