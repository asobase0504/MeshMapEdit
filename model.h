//=========================================
// 
// ���f���̍쐬(�w�b�_�[�t�@�C��)
// Author YudaKaito
// 
//=========================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

#define MODEL_MAX				(512)

typedef enum
{
	COLLISION_SPHERE,
	COLLISION_CUBOID,
	COLLISION_MAX
}COLLISION_TYPE;

//------------------------------------
// ���f���̍\���̒�`
//------------------------------------
typedef struct
{
	// ��{���
	char name[255];		// ���O
	float sizeCriter;	// �������T�C�Y�̐���
	float sizeAdd;		// ���������Ƃ��ɉ��Z����T�C�Y��
	int nType;			// ���f���^�C�v
	D3DXVECTOR3 pos;				// �ʒu
	D3DXVECTOR3 pos_old;			// �O��ʒu
	D3DXVECTOR3 pos_world;			// ���[���h�ʒu
	D3DXVECTOR3 rot;				// �p�x

	// �����蔻����
	COLLISION_TYPE typeCollision;	// �����蔻��̎��
	D3DXVECTOR3 pos_Collision;		// �����蔻��̊�l
	float fLength;					// ���̓����蔻��̑傫��

	// ���f�����
	LPD3DXMESH pMesh;				// ���b�V�����ւ̃|�C���^		// ���_�̏W�܂�̂���
	LPD3DXBUFFER pBuffMat;			// �}�e���A�����ւ̃|�C���^	// 1��X�t�@�C���ɕ����̃}�e���A���������Ă���
	LPDIRECT3DTEXTURE9 *pTexture;	// �e�N�X�`���ւ̃|�C���^
	DWORD nNumMat;					// �}�e���A�����̐�
	D3DXMATRIX mtxWorld;			// ���[���h�}�g���b�N�X
	float scale;					// ���f���X�P�[��

	// �N�I�[�^�j�I�����
	D3DXQUATERNION quaternion;		// �N�I�[�^�j�I��
	bool isQuaternion;				// �N�I�[�^�j�I�����g�p���邩�ǂ����B

	D3DXVECTOR3 movevec;			// �x�N�g��
	float moverot;					// �ړ����̉�]��
	D3DXVECTOR3 move;				// �ړ���
	D3DXVECTOR3 MinVtx;				// ���_�̍ŏ��l
	D3DXVECTOR3 MaxVtx;				// ���_�̍ő�l
	int nIdxModelParent;			// �e���f���̃C���f�b�N�X
	bool bUse;						// �g�p��
}Model;

//------------------------------------
// �v���g�^�C�v�錾
//------------------------------------
void InitModel(void);				// ���f���̏���������
void UninitModel(void);				// ���f���̏I������
void UpdateModel(void);				// ���f���̍X�V����
void DrawModel(void);				// ���f���̕`�揈��
Model* GetModel(void);				// ���f���̎擾����
Model* GetModel(int nType);			// ���f���̎擾����
void LoadModel(void);				// ���f���̓ǂݍ��ݏ���
void LoadMap(void);					// ���f���}�b�v�̓ǂݍ��ݏ���
Model* SetModel(Model* model);		// ���f���̐ݒ�(�ǂݍ��݂��ꂽ���f���Q��)
Model* SetModel(int nType);			// ���f���̐ݒ�(�ǂݍ��݂��ꂽ���f���Q��)
void OutputMap(char *Filename);		// �A�C�e���̐ݒu

#endif // !_MODEL_H_
