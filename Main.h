#pragma once
//���C�u����
#ifndef _MAIN_H_INCLUDED_ //�w�b�_���ǂݍ��܂�ĂȂ�������ʂ�
#define _MAIN_H_INCLUDED_ //�w�b�_��ǂݍ��񂾂��`����ˎ��Ƀw�b�_���ǂݍ��܂�Ă�ifndef�ɓ��炸�����ł���
#include "DxLib.h"
#include "windows.h"
#include <iostream>
#include <stdio.h>

//�萔��`
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 960

typedef struct {
	int x;
	int y;
} Pos;

typedef struct {
	int x, y;       // ���W�i�[�p�ϐ�
	char name[128]; // ���ږ��i�[�p�ϐ�
	int flag;
} MenuElement_t;

#endif

