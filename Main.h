#pragma once
//���C�u����
#ifndef _MAIN_H_INCLUDED_ //�w�b�_���ǂݍ��܂�ĂȂ�������ʂ�
#define _MAIN_H_INCLUDED_ //�w�b�_��ǂݍ��񂾂��`����ˎ��Ƀw�b�_���ǂݍ��܂�Ă�ifndef�ɓ��炸�����ł���
#include "DxLib.h"
#include "windows.h"
#include "sstream"

using namespace std;

//�萔��`
#define WINDOW_WIDTH  960
#define WINDOW_HEIGHT 768
#define MAP_WIDTH 10
#define MAP_HEIGHT 12
#define CHIP_SIZE 64

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

MenuElement debug[1] = {
	{ 768, 550, "�L�������W(", 0 },
};

#endif

