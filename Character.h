#pragma once
#ifndef _CHARACTER_H_INCLUDED_ //�w�b�_���ǂݍ��܂�ĂȂ�������ʂ�
#define _CHARACTER_H_INCLUDED_ //�w�b�_��ǂݍ��񂾂��`����ˎ��Ƀw�b�_���ǂݍ��܂�Ă�ifndef�ɓ��炸�����ł���
#include "DxLib.h"
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
	int handle;
	Pos pos;
	Character();
	void Draw(Pos p, int handle);
};

#endif