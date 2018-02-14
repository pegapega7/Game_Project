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
	int move_f;//1�ňړ����,0�Ŗ��ړ����
	int move_v;//�ړ����Ă������
	int handle;

	Character(Pos pos_init, int handle_init, int move_f_init, int move_v_init);
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
	Enemy();
	Enemy(Pos pos_init, int handle_init, int move_f_init, int move_v_init);
};

/*****
=============================
�Z�p�̃N���X
=============================
�����o
int handle : �Z�摜�̃f�[�^�n���h��
int drawinterval : �\������t���[����
int intervalcount : �\�������t���[�������J�E���g
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
	int handle;
	int drawinterval;
	int intervalflag = 0;
	int intervalcount;

	Skill(int handle_init, int drawinterval_init, int intervalcount_init);
	void Draw(Pos p, int handle, int drawinterval);
};


extern int Hit_Enemy( Pos p, Pos ep);
#endif