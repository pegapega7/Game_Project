#pragma once
#ifndef _CHARACTER_H_INCLUDED_ //�w�b�_���ǂݍ��܂�ĂȂ�������ʂ�
#define _CHARACTER_H_INCLUDED_ //�w�b�_��ǂݍ��񂾂��`����ˎ��Ƀw�b�_���ǂݍ��܂�Ă�ifndef�ɓ��炸�����ł���
#include "DxLib.h"
#include "windows.h"
#include "sstream"
#include "vector"

//�萔��`
#define WINDOW_WIDTH  960
#define WINDOW_HEIGHT 768
#define MAP_WIDTH 10
#define MAP_HEIGHT 12
#define CHIP_SIZE 64

#define PI 3.1415926f

/*****
===========================
���W
===========================
int x : x���W
int y : y���W
*****/
typedef struct {
	int x;
	int y;
} Pos;

/*****
==========================
��`
==========================
int lx : �����x���W
int ly : �����y���W
int rx : �E����x���W
int ry : �E����y���W
*****/


/*****
=============================
�L�����N�^�[�p�̃N���X
=============================
�����o
int handle : �L�����N�^�摜�̃f�[�^�n���h��
Pos pos : �L�����N�^�̍��W�i�摜�̍���j
int move_v : �L�����N�^�𓮂����Ă������
int chargeflag : �L�����N�^���|���`���[�W���Ă����Ԃ�(0:�`���[�W�Ȃ�, 1:�`���[�W���Ă���)
int cancharge : �L�����N�^�����łĂ��Ԃ�(0:�łĂȂ�, 1:�łĂ�)
int shootflag : ���ł��Ă�����(0:�ł��Ă��Ȃ�, �ł��Ă���)
int HP : �L�����N�^��HP
int shootcount : �ł�����̐���ۑ�
=============================
���\�b�h
Character() : �L�����N�^�̏����ݒ�
void Draw(Pos p,int handle) : �L�����N�^�摜�̕\��
=============================
*****/
class Character
{
private:
public:
	Pos pos;
	int move_v;//�ړ����Ă������
	int handle;
	int chargeflag;
	int cancharge;
	int shootflag;
	int aliveflag;
	int HP;
	int shootcount;

	Character(int handle_init);
	~Character();
	void Draw(Pos p, int handle,int chargeflag);
};

/******
=============================
�G�p�N���X
=============================
Character�N���X�̌p��
=============================
�����o
int enemy_clearflag : �G�����w�S�[���܂ŗ����t���O
int aliveflag : �����Ă��邩�ǂ����̃t���O(0:�|��Ă����� 1:�����Ă�����)
int enemytype : �G�̎��
int bossflag : �{�X���ǂ����̃t���O(0:�{�X�ȊO, 1: �{�X)
int speed : �G�̓����X�s�[�h
int move_pattern : �G�̓����̃p�^�[���Ǘ��p
int HP : �G��HP
int MAXHP : �G�̍ő�HP
int point : �G�L�����N�^�̃|�C���g
=============================
���\�b�h
=============================
******/
class Enemy
{
public:
	Pos pos;
	int handle;
	int enemy_clearflag;
	int aliveflag;
	int enemytype;
	int bossflag;
	int speed;
	int move_pattern;
	int HP;
	int MAXHP;
	int point;
	Enemy(int enemytype_init);
	~Enemy();
	void Draw(Pos p, int handle);
};

/*****
=============================
�|�p�̃N���X
=============================
�����o
int speed : ��𓮂����X�s�[�h�i���W�̕ω����j
int pos : : ���\��������W
int handle : �Z�摜�̃f�[�^�n���h��
int drawinterval : �\������t���[����
int intervalcount : �\�������t���[�������J�E���g
int shootflag : ����ł��邩�ǂ����̃t���O(1:���ł���, 0:���ł��Ȃ�)
int distance : ����ł��鋗��
int range : ��̔򋗗�
int chargetime : �ǂꂾ���`���[�W���ꂽ��i�򋗗��ɉe���j
int damage : �ꔭ�̃_���[�W��
=============================
���\�b�h
Character() : �L�����N�^�̏����ݒ�
void Draw(Pos p,int handle) : �L�����N�^�摜�̕\��
=============================
*****/
class Skill
{
private:
public:
	int speed;
	Pos pos;
	int handle;
	int drawinterval;
	int intervalflag;
	int intervalcount;
	int shootflag;
	int distance;
	int range;
	int chargetime;
	int damage;

	//Skill(int handle_init, int drawinterval_init, int intervalcount_init);
	void Draw(Pos p, int handle, int drawinterval);
	int Hit(Pos p, Pos sp);
};


extern int Hit_Enemy( Character& c, Enemy& e);
extern int Hit_Skill(Enemy& e, Skill& s);
extern int Hit_Attack(Character& c, Skill& s);
extern void Move_enemy(Enemy& e);
#endif