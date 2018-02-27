#pragma once

#ifndef _MAP_H_INCLUDED_ //�w�b�_���ǂݍ��܂�ĂȂ�������ʂ�
#define _MAP_H_INCLUDED_ //�w�b�_��ǂݍ��񂾂��`����ˎ��Ƀw�b�_���ǂݍ��܂�Ă�ifndef�ɓ��炸�����ł���

#include "Character.h"
// �萔��`
#define WINDOW_WIDTH  960
#define WINDOW_HEIGHT 768
#define MAP_WIDTH 10
#define MAP_HEIGHT 12
#define CHIP_SIZE 64


/*****
===========================
�}�b�v�`�b�v�̍\����
===========================
int handle : �摜�Ăяo���p�̃f�[�^�n���h��
int hitflag : �}�b�v���Ƃ̓����蔻�� (0:�ʏ�}�b�v�A1�F�ʂ蔲���s�A�Q�F�_���[�W��(������))
*****/
typedef struct {
	int handle;
	int hitflag;
} MapElement;


extern void Init_map();
extern void Draw_map(MapElement map[]);
extern int Hit_map(MapElement map[], Character& c);
#endif
