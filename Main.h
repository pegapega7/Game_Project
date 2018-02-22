#pragma once
//���C�u����
#ifndef _MAIN_H_INCLUDED_ //�w�b�_���ǂݍ��܂�ĂȂ�������ʂ�
#define _MAIN_H_INCLUDED_ //�w�b�_��ǂݍ��񂾂��`����ˎ��Ƀw�b�_���ǂݍ��܂�Ă�ifndef�ɓ��炸�����ł���
#include "DxLib.h"
#include "windows.h"
#include "sstream"
#include "vector"

using namespace std;

//�萔��`
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
�`��p�\����
===========================
int x : x���W
int y : y���W
char name[128] : �\�����镶����
int flag : �I�𒆂��ǂ����̃t���O(1:�I�� 0:���I��)
*****/
typedef struct {
	int x, y;       // ���W�i�[�p�ϐ�
	string name; // ���ږ��i�[�p�ϐ�
	int flag;
} MenuElement;

MenuElement MainMenu[2] = {
	{ 500, 500, "�Q�[���X�^�[�g", 1 }, // �^�O�̒��g�̏��ԂŊi�[�����Bx��80���Ay��100���Aname��"�Q�[���X�^�[�g"��
	{ 500, 550, "�Q�[���I��", 0 },
};

MenuElement debug[2] = {
	{ 640, 550, "�L�������W(", 0 },
	{ 640, 600, "���̓L�[ : ", 0 },
};

MenuElement Ending[2] = {
	{ 500, 500, "�^�C�g���ɖ߂�", 1 }, 
	{ 500, 550, "�Q�[���I��", 0 },
};

MenuElement Gameover[2] = {
	{ 500, 500, "���g���C", 1 },
	{ 500, 550, "�^�C�g���ɖ߂�", 0 },
};

#endif

