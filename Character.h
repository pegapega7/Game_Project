#pragma once
#ifndef _CHARACTER_H_INCLUDED_ //�w�b�_���ǂݍ��܂�ĂȂ�������ʂ�
#define _CHARACTER_H_INCLUDED_ //�w�b�_��ǂݍ��񂾂��`����ˎ��Ƀw�b�_���ǂݍ��܂�Ă�ifndef�ɓ��炸�����ł���
#include "DxLib.h"


//�萔��`
#define WINDOW_WIDTH  960
#define WINDOW_HEIGHT 768
#define MAP_WIDTH 10
#define MAP_HEIGHT 12
#define CHIP_SIZE 64


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
=============================
�L�����N�^�[�p�̃N���X
=============================
�����o
int handle : �L�����N�^�摜�̃f�[�^�n���h��
Pos pos : �L�����N�^�̍��W�i�摜�̍���j
int move_v : �L�����N�^�𓮂����Ă������
int chargeflag : �L�����N�^���|���`���[�W���Ă����Ԃ�(0:�`���[�W�Ȃ�, 1:�`���[�W���Ă���)
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
	int aliveflag;

	Character(int handle_init);
	~Character();
	void Draw(Pos p, int handle);
};

/******
=============================
�G�p�N���X
=============================
Character�N���X�̌p��
=============================
�����o
int enemytype : �G�̎��
int bossflag : �{�X���ǂ����̃t���O(0:�{�X�ȊO, 1: �{�X)
int aliveflag : �����Ă��邩�ǂ����̃t���O(0:�|��Ă����� 1:�����Ă�����)
int speed : �G�̓����X�s�[�h
=============================
���\�b�h
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
�Z�p�̃N���X
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