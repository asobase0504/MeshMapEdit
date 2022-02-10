//=========================================
// 
// �|���S���̍쐬(�w�b�_�[�t�@�C��)
// Author YudaKaito
// 
//=========================================
#ifndef _POLYGON_H_
#define _POLYGON_H_

//------------------------------------
// include
//------------------------------------
#include "main.h"

//------------------------------------
// �|���S���̍\���̂��`
//------------------------------------
typedef struct
{
	char* name;
	LPDIRECT3DVERTEXBUFFER9	VtxBuff;	// ���_�o�b�t�@�[�ւ̃|�C���^
	LPDIRECT3DTEXTURE9		Tex;		// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3				pos;		// ���_���W
	D3DXVECTOR3				size;		// ���_���W
	D3DXVECTOR3				rot;		// ��]���W
	D3DXMATRIX				mtxWorld;	// ���[���h�}�g���b�N�X
	bool					bUse;		// �g�p���Ă��邩
} ObjectPolygon;

//------------------------------------
// �v���g�^�C�v�錾
//------------------------------------
void InitPolygon(void);		// �|���S���̏���������
void UninitPolygon(void);	// �|���S���̏I������
void UpdatePolygon(void);	// �|���S���̍X�V����
void DrawPolygon(void);		// �|���S���̕`�揈��
void SetPolygon(D3DXVECTOR3* pos, D3DXVECTOR3* rot, D3DXVECTOR3 size, char* texFile, char* name);		// �|���S���̐ݒ菈��
void DrawPolygonUI(void);	// �|���S����UI�`�揈��
void SetPolygonUI(D3DXVECTOR3* pos, D3DXVECTOR3* rot, D3DXVECTOR3 size, char* texFile);	// �|���S����UI�ݒ菈��
bool CollisionPolygon(D3DXVECTOR3* pos, char* name);		// �|���S���̐ݒ菈��
ObjectPolygon* GetPolygon(char* name);			// �|���S���̎擾����
D3DXVECTOR3 GetPolygonPos(void);		// �|���S���̎擾����

#endif // !_POLYGON_H_
