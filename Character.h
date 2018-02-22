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
int move_v : キャラクタを動かしている向き
int chargeflag : キャラクタが弓をチャージしている状態か(0:チャージなし, 1:チャージしている)
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
	int move_v;//移動している向き
	int handle;
	int chargeflag;
	int aliveflag;

	Character(int handle_init);
	~Character();
	void Draw(Pos p, int handle);
};

/******
=============================
敵用クラス
=============================
Characterクラスの継承
=============================
メンバ
int enemytype : 敵の種類
int bossflag : ボスかどうかのフラグ(0:ボス以外, 1: ボス)
int aliveflag : 生きているかどうかのフラグ(0:倒れている状態 1:生きている状態)
int speed : 敵の動くスピード
=============================
メソッド
=============================
******/
class Enemy
{
public:
	Pos pos;
	int handle;
	int aliveflag;
	int enemytype;
	int bossflag;
	int speed;
	Enemy(int enemytype_init);
	~Enemy();
	void Draw(Pos p, int handle);
};

/*****
=============================
技用のクラス
=============================
メンバ
int speed : 矢を動かすスピード（座標の変化率）
int pos : : 矢を表示する座標
int handle : 技画像のデータハンドル
int drawinterval : 表示するフレーム数
int intervalcount : 表示したフレーム数をカウント
int shootflag : 矢が飛んでいるかどうかのフラグ(1:飛んでいる, 0:飛んでいない)
int distance : 矢が飛んでいる距離
int range : 矢の飛距離
int chargetime : どれだけチャージされた矢か（飛距離に影響）
=============================
メソッド
Character() : キャラクタの初期設定
void Draw(Pos p,int handle) : キャラクタ画像の表示
=============================
*****/
class Skill
{
private:
public:
	int speed = 16;
	Pos pos;
	int handle;
	int drawinterval;
	int intervalflag = 0;
	int intervalcount;
	int shootflag;
	int distance;
	int range;
	int chargetime;

	//Skill(int handle_init, int drawinterval_init, int intervalcount_init);
	void Draw(Pos p, int handle, int drawinterval);
	int Hit(Pos p, Pos sp);
};


extern int Hit_Enemy( Pos p, Pos ep);
extern void Move_enemy(Enemy& e);
#endif