//============================
//
// �A�C�e���ݒ�w�b�^�[
// Author:hamada ryuuga
//
//============================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

#define MAX_ITEMWAID (50.0f)	//�}�b�v�̃T�C�Y/�������ŏo���}�b�v�T�C�Y�v�Z��MIN-�P�T�O�OMAX+�P�T�O�O�͂Ȃ�R�O�O�O�ɂȂ�
#define MINX (-1500.0f)			
#define MINY (-1500.0f)
#define MAXX (1500.0f)
#define MAXY (1500.0f)

//�v���g�^�C�v�錾
void InitItem(void);//������
void UninitItem(void);//�j��
void UpdateItem(void);//�X�V
void DrawItem(void);//�`��
#endif