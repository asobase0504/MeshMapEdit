//============================
//
// ���b�V���ݒ�w�b�^�[
// Author: hamada ryuuga
// Author: Yuda Kaito
//
//============================
#ifndef _MESH_H_
#define _MESH_H_

#include "main.h"

#define	MESHX	(1)
#define	MESHY	(5)
#define MAX_SIZMESH (50.0f)
#define MAX_MESH (60)

#define MESHMAX (12800)
#define MESHLINE (61)
#define MESHEND  (59)
#define MAPPASTSET "Data/system/Maptset.txt"

//------------------------------------
// �|���S���̍\���̂��`
//------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;						// ���_���W
	D3DXVECTOR3 rot;						// ��]���W
	D3DXMATRIX mtxWorld;					// ���[���h�}�g���b�N�X
	LPDIRECT3DTEXTURE9 pTexture;			// �e�N�X�`��
	LPDIRECT3DINDEXBUFFER9 pIdxBuff;		//�C���f�b�N�X�o�b�t�@
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;		// ���_�o�b�t�@�[�ւ̃|�C���^
	int xsiz;								// �ʐ�
	int zsiz;								// �ʐ�
	int X;									// �ӂ̒��_��
	int Z;									// �ӂ̒��_��
	int nVtx;								// ���_��
	int Index;								// �C���f�b�N�X
	int por;
	int* aMap;							// �}�b�v�`�b�v
	bool bUse;								// �g�p��
} MESH;


//�v���g�^�C�v�錾
void InitMesh(void);//������
void UninitMesh(void);//�j��
void UpdateMesh(void);//�X�V
void DrawMesh(void);//�`��
void SetMesh(int X ,int Z);//�ꏊ.��]
bool CollisionMesh(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 Siz);
bool CreateMesh(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 Siz);
MESH *GetMesh(void);
void InitMap(char *Filename);
void OutputMeshMap(char *Filename);
#endif