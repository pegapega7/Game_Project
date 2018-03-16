#pragma once
#ifndef _CHARACTER_H_INCLUDED_ //ヘッダが読み込まれてなかったら通る
#define _CHARACTER_H_INCLUDED_ //ヘッダを読み込んだら定義する⇒次にヘッダが読み込まれてもifndefに入らず無視できる
#include "DxLib.h"
#include "windows.h"
#include "sstream"
#include "vector"

//定数定義
#define WINDOW_WIDTH  960
#define WINDOW_HEIGHT 768
#define MAP_WIDTH 10
#define MAP_HEIGHT 12
#define CHIP_SIZE 64

#define PI 3.1415926f

/*****
===========================
座標 : Pos
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
キャラクター用のクラス : Character
=============================
メンバ
int handle : キャラクタ画像のデータハンドル
Pos pos : キャラクタの座標（画像の左上）
int hitflag : 当たったかどうか(0:ヒットしていない, 1:ヒットした)
int chargeflag : キャラクタが弓をチャージしている状態か(0:チャージなし, 1:チャージしている)
int charge_count : //チャージした時間
int cancharge : キャラクタが矢を打てる状態か(0:打てない, 1:打てる)
int shootflag : 矢を打っている状態(0:打っていない, 打っている)
int aliveflag : 生きているかどうか
int HP : キャラクタのHP
int shootcount : 打った矢の数を保存
=============================
メソッド
Character() : キャラクタの初期設定
void Draw() : キャラクタ画像の表示
=============================
*****/
class Character
{
private:
public:
	//メンバ変数
	int handle;
	Pos pos;
	int hitflag;
	int chargeflag;
	int charge_count;
	int cancharge;
	int shootflag;
	int aliveflag;
	int HP;
	int shootcount;

	//メソッド関数
	Character(int handle_init);
	void Draw();
};

/******
=============================
敵用クラス : Enemy
=============================
メンバ
int handle : キャラクタ画像のデータハンドル
Pos pos : キャラクタの座標（画像の左上）
int hitflag : 当たったかどうか(0:ヒットしていない, 1:ヒットした)
int enemy_clearflag : 敵が自陣ゴールまで来たフラグ
int aliveflag : 生きているかどうかのフラグ(0:倒れている状態 1:生きている状態)
int enemytype : 敵の種類
int bossflag : ボスかどうかのフラグ(0:ボス以外, 1: ボス)
int speed : 敵の動くスピード
int move_pattern : 敵の動きのパターン管理用
int HP : 敵のHP
int MAXHP : 敵の最大HP
int point : 敵キャラクタのポイント
=============================
メソッド
Enemy(int enemytype_init) : キャラクタの初期設定
void Draw() : キャラクタ画像の表示
=============================
******/
class Enemy
{
public:
	//メンバ変数
	int handle;
	Pos pos;
	int hitflag;
	int enemy_clearflag;
	int aliveflag;
	int enemytype;
	int bossflag;
	int speed;
	int move_pattern;
	int HP;
	int MAXHP;
	int point;

	//メソッド関数
	Enemy(int enemytype_init);
	void Draw();
};

/*****
=============================
弓用のクラス
=============================
メンバ
int handle : 技画像のデータハンドル
int pos : : 矢を表示する座標
int speed : 矢を動かすスピード（座標の変化率）
int shootflag : 矢が飛んでいるかどうかのフラグ(1:飛んでいる, 0:飛んでいない)
int damage : 一発のダメージ量
=============================
メソッド
void Draw(Pos p,int handle) : キャラクタ画像の表示
=============================
*****/
class Skill
{
private:
public:
	//メンバ変数
	int handle;
	Pos pos;
	int speed;
	int shootflag;
	int damage;
	//メソッド関数
	void Draw();
};


extern int Hit_Enemy( Character& c, Enemy& e);	//自機と敵　　　　あたり判定
extern int Hit_Skill(Enemy& e, Skill& s);		//敵と自機の弓矢　あたり判定
extern int Hit_Attack(Character& c, Skill& s);	//自機と敵　　　　あたり判定
extern void Move_enemy(Enemy& e);				//敵の移動
#endif