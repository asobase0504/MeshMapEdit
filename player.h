//=========================================
// 
// �v���C���[�̍쐬(�w�b�_�[�t�@�C��)
// Author YudaKaito
// 
//=========================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//------------------------------------
// include
//------------------------------------
#include "main.h"
#include "model.h"

//------------------------------------
// ���f���p�[�c�̍\���̒�`
//------------------------------------
#define PARTS_NUM	(512)		// �p�[�c�̐�

//------------------------------------
// ���f���̍\���̒�`
//------------------------------------
typedef struct
{
	D3DXMATRIX	mtxWorld;			// ���[���h�}�g���b�N�X
	D3DXVECTOR3	pos;				// �ʒu
	D3DXVECTOR3	pos_old;			// �O��ʒu
	D3DXVECTOR3	rot;				// �p�x
	D3DXVECTOR3	rotDest;			// �ړI�̊p�x
	D3DXVECTOR3	movevec;			// �x�N�g��
	D3DXVECTOR3	MinVtx;				// ���_�̍ŏ��l
	D3DXVECTOR3	MaxVtx;				// ���_�̍ő�l
	Model		model;				// ���f��
	float		moverot;			// �ړ����̉�]��
	float		fLength;			// �傫��
	float		fLengthLand;		// �ڕW�̑�n�܂ł̋���
	int			nModelCnt;			// �������Ă��郂�f����
}Player;

//------------------------------------
// �v���g�^�C�v�錾
//------------------------------------
void InitPlayer(void);		// �v���C���[�̏���������
void UninitPlayer(void);	// �v���C���[�̏I������
void UpdatePlayer(void);	// �v���C���[�̍X�V����
void DrawPlayer(void);		// �v���C���[�̍X�V����
void MovePlayer(void);		// �v���C���[�̈ړ�
void DeleteModel(void);		// �v���C���[�ȊO�̃��f�����������
Player* GetPlayer(void);	// �v���C���[�̎擾����
#endif // !_PLAYER_H_
