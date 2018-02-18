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
=============================
���\�b�h
=============================
******/
class Enemy : public Character
{

public:

	Enemy(int handle_init);
	~Enemy();
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

	//Skill(int handle_init, int drawinterval_init, int intervalcount_init);
	void Draw(Pos p, int handle, int drawinterval);
	int Hit(Pos p, Pos sp);
};


extern int Hit_Enemy( Pos p, Pos ep);
#endif