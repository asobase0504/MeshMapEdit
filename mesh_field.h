//=========================================
// 
// �|���S���̍쐬(�w�b�_�[�t�@�C��)
// Author YudaKaito
// 
//=========================================
#ifndef _MESH_FIELD_H_
#define _MESH_FIELD_H_

//------------------------------------
// include
//------------------------------------
#include "main.h"

//------------------------------------
// �Z�b�g���b�V���̍\���̂��`
//------------------------------------
typedef struct
{
	char* file;
	D3DXVECTOR3 pos;		// ���_���W
	D3DXVECTOR3 rot;		// ��]���W
	int nSurfaceWidth;		// �ʂ̕�
	int nSurfaceHeight;		// �ʂ̍���
	float fLineWidth;		// �ӂ̕�
	float fLineHeight;		// �ӂ̍���
} SetMesh;

//------------------------------------
// �v���g�^�C�v�錾
//------------------------------------
void InitMeshField(void);				// ���b�V���̏���������
void UninitMeshField(void);				// ���b�V���̏I������
void UpdateMeshField(void);				// ���b�V���̍X�V����
void DrawMeshField(void);				// ���b�V���̕`�揈��
void SetMeshField(SetMesh* mesh);		// ���b�V���̕`�揈��
D3DXVECTOR3 GetMeshFieldPos(void);		// ���b�V���̎擾����
void CollisionMeshField(D3DXVECTOR3* pos);						// ���b�V���t�B�[���h�̓����蔻��
void CollisionMeshField(D3DXVECTOR3* pos, D3DXVECTOR3* HitPos);	// �߂�pos�Ɠ����蔻���pos���Ⴄ�ꍇ

#endif // !_MESH_FIELD_H_
