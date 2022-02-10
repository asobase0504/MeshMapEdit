//============================
//
// ���b�V���ݒ�(�ȂȂ�)
// Author:hamada ryuuga
//
//============================
//------------------------------------
// include
//------------------------------------
#include "mesh.h"
#include "input.h"
#include "common.h"
#include "player.h"
#include <time.h>
#include <stdio.h>

//------------------------------------
// �}�N����`
//------------------------------------
#define MAXMOVE		(4)	//���b�V���ւ��܂��ő吔
#define MAX_TEX		(4)	//���b�V���ւ��܂��ő吔
#define MOUNTAIN	(5 * 10.0f)					// �l���P�����x�ω�����l
#define MESHTEXFILE	"data/TEXTURE/��.jpg"	// �e�N�X�`���t�@�C��

//------------------------------------
// static�ϐ�
//------------------------------------
static MESH s_Mesh[MAX_TEX];					// �|���S���̍\����
static int* nPosMesh = NULL;

//=========================================
// ����������
// Author: hamada ryuuga
// Aythor: Yuda Kaito
//=========================================
void InitMesh(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	for (int i = 0; i < MAX_TEX; i++)
	{
		MESH* mesh = &s_Mesh[i];

		// ����������
		mesh->pos = ZERO_VECTOR;
		mesh->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ��]���W

		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			MESHTEXFILE,
			&mesh->pTexture);

		//������
		mesh->xsiz = MAX_MESH;
		mesh->zsiz = MAX_MESH;

		//�ӂ̒��_��
		mesh->X = mesh->xsiz + 1;//1��������
		mesh->Z = mesh->zsiz + 1;//1��������

		//���_��
		mesh->nVtx = mesh->X* mesh->Z;//���_�����g���Ă��

		//Vtx�̃T�C�Y���f�[�^���m�ۂ���
		nPosMesh = (int*)malloc(mesh->nVtx * sizeof(int));

		//�C���f�b�N�X��
		mesh->Index = (2 * mesh->X * mesh->zsiz + 2 * (mesh->zsiz - 1));

		mesh->por = mesh->Index - 2;

		// ���_�o�b�t�@�̐���
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * mesh->nVtx,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&mesh->pVtxBuff,
			NULL);

		//�C���f�b�N�X�o�b�t�@����
		pDevice->CreateIndexBuffer(sizeof(WORD) * mesh->Index,
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,
			D3DPOOL_MANAGED,
			&mesh->pIdxBuff,
			NULL);

		VERTEX_3D* pVtx = NULL;

		// ���_���W�����b�N
		mesh->pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		for (int i = 0; i < mesh->nVtx; i++)
		{
			nPosMesh[i] = 0;
			float posx = ((i % mesh->X) - 1.0f);
			float posz = ((i / mesh->Z) - 1.0f)*-1.0f;

			float texU = 1.0f / mesh->xsiz*(i % mesh->X);
			float texV = 1.0f / mesh->zsiz*(i / mesh->Z);

			//�߂������^�񒆂ɂ���␳
			mesh->pos = D3DXVECTOR3(-(posx - 1)*MAX_SIZMESH / 2, 0.0f, -posz * MAX_SIZMESH / 2);


			//���W�̕␳
			pVtx[i].pos += D3DXVECTOR3(posx*MAX_SIZMESH, -1.0f, posz * MAX_SIZMESH);

			// �e���_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
			pVtx[i].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			// ���_�J���[�̐ݒ�
			pVtx[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[i].tex = D3DXVECTOR2(texU, texV);

		}

		// ���_���W���A�����b�N
		mesh->pVtxBuff->Unlock();



		// ���_���W�����b�N
		mesh->pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
		int WideMax = 0;
		int WideMin = MESHEND;
		for (int i = 0; i < mesh->nVtx; i++)
		{

			//�[�����Ɉ�a��������̂Ōv�Z�Œ[�����̃|�X�������ď��ɖ��߂鏈��
			float posx = ((i % mesh->X) - 1.0f);
			float posz = ((i / mesh->Z) - 1.0f)*-1.0f;

			if (i >= 0 && i <= 60)
			{
				pVtx[i].pos = D3DXVECTOR3(posx*MAX_SIZMESH, -1.0f, posz * MAX_SIZMESH);
			}
			if (i >= mesh->nVtx - 60 && i <= mesh->nVtx)
			{
				pVtx[i].pos = D3DXVECTOR3(posx*MAX_SIZMESH, -1.0f, posz * MAX_SIZMESH);
			}
			if (i == WideMax)
			{
				pVtx[i].pos = D3DXVECTOR3(posx*MAX_SIZMESH, -1.0f, posz * MAX_SIZMESH);
				WideMax += MESHLINE;
			}
			if (i == WideMax - 1)
			{
				pVtx[i].pos = D3DXVECTOR3(posx*MAX_SIZMESH, -1.0f, posz * MAX_SIZMESH);
			}
		}

		// ���_���W���A�����b�N
		mesh->pVtxBuff->Unlock();



		//�C���f�b�N�X�o�b�t�@�̃��b�N
		WORD* pIdx;
		mesh->pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);
		for (int z = 0; z < mesh->zsiz; z++)
		{
			int linetop = z * (mesh->X * 2 + 2);
			for (int x = 0; x < mesh->X; x++)
			{
				int nIdxData = x * 2 + linetop;
				pIdx[nIdxData + 1] = (WORD)(x + (z * mesh->X));
				pIdx[nIdxData] = (WORD)(pIdx[nIdxData + 1] + mesh->X);

			}
			//�k�ރ|���S���ݒ�
			if (z < mesh->xsiz - 1)
			{
				pIdx[mesh->X * 2 + 0 + linetop] = (WORD)(mesh->xsiz + mesh->X*z);
				pIdx[mesh->X * 2 + 1 + linetop] = (WORD)(mesh->X * 2 + mesh->X * z);
			}

		}
		for (int z = 0; z < (int)mesh->zsiz; z++)
		{
			int linetop = z * ((int)mesh->X * 2 + 2);
			for (int x = 0; x < (int)mesh->X; x++)
			{
				int nIdxData = x * 2 + linetop;
				pIdx[nIdxData + 1] = (WORD)(x + (z * mesh->X));
				pIdx[nIdxData] = (WORD)(pIdx[nIdxData + 1] + mesh->X);
			}
			//�k�ރ|���S���ݒ�
			if (z < mesh->xsiz - 1)
			{
				pIdx[(int)mesh->X * 2 + 0 + linetop] = (WORD)(mesh->xsiz + mesh->X*z);
				pIdx[(int)mesh->X * 2 + 1 + linetop] = (WORD)(mesh->X * 2 + mesh->X * z);
			}
		}

		//---------------------------------------
		//��������@��
		//---------------------------------------

		//�O�p�̒��_��
		const int nTri = 3;

		D3DXVECTOR3 posLineVec[nTri];//�x�N�g��

		for (int nCnt = 0; nCnt < mesh->por; nCnt++) // �v���~�e�B�u�̐������܂킷�B
		{
			//�x�N�g�������߂�
			posLineVec[0] = pVtx[pIdx[nCnt + 0]].pos;
			posLineVec[1] = pVtx[pIdx[nCnt + 1]].pos;
			posLineVec[2] = pVtx[pIdx[nCnt + 2]].pos;

			if ((pIdx[nCnt + 0] == pIdx[nCnt + 1]) ||
				(pIdx[nCnt + 0] == pIdx[nCnt + 2]) ||
				(pIdx[nCnt + 2] == pIdx[nCnt + 1]))
			{
				continue;
			}

			D3DXVECTOR3 V1 = posLineVec[1] - posLineVec[0];
			D3DXVECTOR3 V2 = posLineVec[2] - posLineVec[0];

			D3DXVECTOR3 Normal;

			if (nCnt % 2 == 0)
			{
				//A��B�̖@�������߂���
				D3DXVec3Cross(&Normal, &V2, &V1);
			}
			else
			{
				//A��B�̖@�������߂���
				D3DXVec3Cross(&Normal, &V1, &V2);
			}

			//Normal���m�[�}���C�Y���āA���� 1�ɂ���B
			D3DXVec3Normalize(&Normal, &Normal);

			for (int i = 0; i < nTri; i++)
			{//�@���v�Z
				pVtx[pIdx[nCnt + i]].nor += Normal;
			}
		}

		for (int nCnt = 0; nCnt < mesh->nVtx; nCnt++)
		{
			//nor���m�[�}���C�Y���āA���� 1�ɂ���B
			D3DXVec3Normalize(&pVtx[nCnt].nor, &pVtx[nCnt].nor);
		}

		// ���_���W���A�����b�N
		mesh->pIdxBuff->Unlock();

	}
}

//=========================================
// �I������
// Author: hamada ryuuga
// Aythor: Yuda Kaito
//=========================================
void UninitMesh(void)
{
	for (int i = 0; i < MAX_TEX; i++)
	{
		MESH* mesh = &s_Mesh[i];
		// ���_�o�b�t�@�[�̉��
		if (mesh->pVtxBuff != NULL)
		{
			mesh->pVtxBuff->Release();
			mesh->pVtxBuff = NULL;
		}

		// ���b�V���e�N�X�`���̉��
		if (mesh->pTexture != NULL)
		{
			mesh->pTexture->Release();
			mesh->pTexture = NULL;
		}

		// �C���f�b�N�X�o�b�t�@�̉��
		if (mesh->pIdxBuff != NULL)
		{
			mesh->pIdxBuff->Release();
			mesh->pIdxBuff = NULL;
		}

		//�f���[��
		if (nPosMesh != NULL)
		{
			free(nPosMesh);
			nPosMesh = NULL;
		}
	}
}

//=========================================
// �X�V����
// Author: hamada ryuuga
// Aythor: Yuda Kaito
//=========================================
void UpdateMesh(void)
{		
}

//=========================================
// �`�揈��
// Author: hamada ryuuga
// Aythor: Yuda Kaito
//=========================================
void DrawMesh(void)
{
	for (int i = 0; i < MAX_TEX; i++)
	{
		MESH* mesh = &s_Mesh[i];

		if (!mesh->bUse)
		{
			continue;
		}

		LPDIRECT3DDEVICE9 pDevice = GetDevice();
		D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

		// ���[���h�}�g���b�N�X�̏�����
		// �s�񏉊����֐�(��1�����̍s���P�ʍs��ɏ�����)
		D3DXMatrixIdentity(&mesh->mtxWorld);

		// �����𔽉f
		// �s���]�֐�(��1�����Ƀ��[(y)�s�b�`(x)���[��(z)�����̉�]�s����쐬)
		D3DXMatrixRotationYawPitchRoll(&mtxRot, mesh->rot.y, mesh->rot.x, mesh->rot.z);
		// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
		D3DXMatrixMultiply(&mesh->mtxWorld, &mesh->mtxWorld, &mtxRot);

		// �ʒu�𔽉f
		// �s��ړ��֐�(��P������X,Y,Z�����̈ړ��s����쐬)
		D3DXMatrixTranslation(&mtxTrans, mesh->pos.x, mesh->pos.y, mesh->pos.z);
		// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
		D3DXMatrixMultiply(&mesh->mtxWorld, &mesh->mtxWorld, &mtxTrans);

		// ���[���h���W�s��̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &mesh->mtxWorld);

		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, mesh->pVtxBuff, 0, sizeof(VERTEX_3D));

		//�C���f�b�N�X�o�b�t�@�ݒ�
		pDevice->SetIndices(mesh->pIdxBuff);
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, mesh->pTexture);

		// �|���S���̕`��
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, mesh->nVtx, 0, mesh->por);


		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);
	}
}

//=========================================
// ���b�V���ݒ�
// Author:hamada ryuuga
//=========================================
void SetMesh(int X ,int Z)//�ꏊ.��]
{
	for (int i = 0; i < MAX_TEX; i++)
	{
		MESH* mesh = &s_Mesh[i];
		// ���_�o�b�t�@�[�̉��
		if (mesh->pVtxBuff != NULL)
		{
			mesh->pVtxBuff->Release();
			mesh->pVtxBuff = NULL;
		}
		if (mesh->pIdxBuff != NULL)
		{
			mesh->pIdxBuff->Release();
			mesh->pIdxBuff = NULL;
		}

		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		// ����������
		mesh->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		mesh->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ��]���W

		//������
		mesh->xsiz = X;
		mesh->zsiz = Z;

		//�ӂ̒��_��
		mesh->X = mesh->xsiz + 1;//1��������
		mesh->Z = mesh->zsiz + 1;//1��������

		mesh->nVtx = mesh->X* mesh->Z;//���_�����g���Ă��

		//�C���f�b�N�X��
		mesh->Index = (2 * mesh->X * mesh->zsiz + 2 * (mesh->zsiz - 1));

		mesh->por = mesh->Index - 2;
		//���_�o�b�t�@�̐���
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * mesh->nVtx,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&mesh->pVtxBuff,
			NULL);

		//�C���f�b�N�X�o�b�t�@����
		pDevice->CreateIndexBuffer(sizeof(WORD) * mesh->Index,
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,
			D3DPOOL_MANAGED,
			&mesh->pIdxBuff,
			NULL);

		VERTEX_3D* pVtx = NULL;

		// ���_���W�����b�N
		mesh->pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		for (int i = 0; i < mesh->nVtx; i++)
		{
			float posx = ((i % mesh->X) - 1.0f);
			float posz = ((i / mesh->Z) - 1.0f)*-1.0f;

			float texU = 1.0f / mesh->xsiz*(i % mesh->X);
			float texV = 1.0f / mesh->zsiz*(i / mesh->Z);

			//�߂������^�񒆂ɂ���␳
			mesh->pos = D3DXVECTOR3(-(posx - 1)*MAX_SIZMESH / 2, 0.0f, -posz * MAX_SIZMESH / 2);
			if (i <= mesh->nVtx / 2)
			{
				//pos
				pVtx[i].pos += D3DXVECTOR3(posx*MAX_SIZMESH, (float)sin(i)*60.0f, posz * MAX_SIZMESH);
			}



			// �e���_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
			pVtx[i].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// ���_�J���[�̐ݒ�
			pVtx[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[i].tex = D3DXVECTOR2(texU, texV);

		}

		//�C���f�b�N�X�o�b�t�@�̃��b�N
		WORD* pIdx;
		mesh->pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);
		for (int z = 0; z < (int)mesh->zsiz; z++)
		{
			int linetop = z * ((int)mesh->X * 2 + 2);
			for (int x = 0; x < (int)mesh->X; x++)
			{
				int nIdxData = x * 2 + linetop;
				pIdx[nIdxData + 1] = (WORD)(x + (z * mesh->X));
				pIdx[nIdxData] = (WORD)(pIdx[nIdxData + 1] + mesh->X);
			}
			//�k�ރ|���S���ݒ�
			if (z < mesh->xsiz - 1)
			{
				pIdx[(int)mesh->X * 2 + 0 + linetop] = (WORD)(mesh->xsiz + mesh->X*z);
				pIdx[(int)mesh->X * 2 + 1 + linetop] = (WORD)(mesh->X * 2 + mesh->X * z);
			}
		}
		//�O�p�̒��_��
		const int nTri = 3;

		D3DXVECTOR3 posLineVec[nTri];//�x�N�g��

		for (int nCnt = 0; nCnt < mesh->por; nCnt++) // �v���~�e�B�u�̐������܂킷�B
		{
			//�x�N�g�������߂�
			posLineVec[0] = pVtx[pIdx[nCnt + 0]].pos;
			posLineVec[1] = pVtx[pIdx[nCnt + 1]].pos;
			posLineVec[2] = pVtx[pIdx[nCnt + 2]].pos;

			if ((pIdx[nCnt + 0] == pIdx[nCnt + 1]) ||
				(pIdx[nCnt + 0] == pIdx[nCnt + 2]) ||
				(pIdx[nCnt + 2] == pIdx[nCnt + 1]))
			{
				continue;
			}

			D3DXVECTOR3 V1 = posLineVec[1] - posLineVec[0];
			D3DXVECTOR3 V2 = posLineVec[2] - posLineVec[0];

			D3DXVECTOR3 Normal;

			if (nCnt % 2 == 0)
			{
				//A��B�̖@�������߂���
				D3DXVec3Cross(&Normal, &V2, &V1);
			}
			else
			{
				//A��B�̖@�������߂���
				D3DXVec3Cross(&Normal, &V1, &V2);
			}

			//Normal���m�[�}���C�Y���āA���� 1�ɂ���B
			D3DXVec3Normalize(&Normal, &Normal);

			for (int i = 0; i < nTri; i++)
			{//�@���v�Z
				pVtx[pIdx[nCnt + i]].nor += Normal;
			}
		}

		for (int nCnt = 0; nCnt < mesh->nVtx; nCnt++)
		{
			//nor���m�[�}���C�Y���āA���� 1�ɂ���B
			D3DXVec3Normalize(&pVtx[nCnt].nor, &pVtx[nCnt].nor);
		}

		// ���_���W���A�����b�N
		mesh->pIdxBuff->Unlock();

		// ���_���W���A�����b�N
		mesh->pVtxBuff->Unlock();
	}
}

//=========================================
// �Q�b�g(�\����)
// Author:hamada ryuuga
//=========================================
MESH *GetMesh(void)
{
	return s_Mesh;
}

//=========================================
// �����蔻��
// Author: hamada ryuuga
// Aythor: Yuda Kaito
//=========================================
bool CollisionMesh(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 Siz)
{
	bool bIsLanding = false;
	const int nTri = 3;

	for (int i = 0; i < MAX_TEX; i++)
	{
		MESH* mesh = &s_Mesh[i];

		if (!mesh->bUse)
		{
			continue;
		}

		// ���_���W�����b�N
		VERTEX_3D* pVtx = NULL;
		mesh->pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//�C���f�b�N�X�o�b�t�@�̃��b�N
		WORD* pIdx;
		mesh->pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

		D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxWorld;

		// ���[���h�}�g���b�N�X�̏�����
		// �s�񏉊����֐�(��1�����̍s���P�ʍs��ɏ�����)
		D3DXMatrixIdentity(&mtxWorld);

		// �s��ړ��֐�(��P������X,Y,Z�����̈ړ��s����쐬)
		D3DXMatrixTranslation(&mtxTrans, mesh->pos.x, mesh->pos.y, mesh->pos.z);
		// �s��|���Z�֐�(��2�����~��3�������P�����Ɋi�[)
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

		for (int nCnt = 0; nCnt < mesh->por; nCnt++)
		{
			D3DXVECTOR3 posLineVec[nTri];

			posLineVec[0] = pVtx[pIdx[nCnt + 0]].pos;
			posLineVec[1] = pVtx[pIdx[nCnt + 1]].pos;
			posLineVec[2] = pVtx[pIdx[nCnt + 2]].pos;

			if ((pIdx[nCnt + 0] == pIdx[nCnt + 1]) ||
				(pIdx[nCnt + 0] == pIdx[nCnt + 2]) ||
				(pIdx[nCnt + 2] == pIdx[nCnt + 1]))
			{//�k�ރ|���S�����Ȃ�
				continue;
			}

			for (int i = 0; i < nTri; i++)
			{//�x�N�g���R���W���}�g���b�N�X�ŕϊ�����i��Z�j
				D3DXVec3TransformCoord(&posLineVec[i], &posLineVec[i], &mtxWorld);
			}

			int  LineCout = 0;

			for (int i = 0; i < nTri; i++)
			{
				//�x�N�g��S2 V2												
				D3DXVECTOR3 vecWall = posLineVec[(i + 1) % nTri] - posLineVec[i];

				//�x�N�g�����݂�POS�Ǝn�_�܂ł̋���
				D3DXVECTOR3 vecPos = *pPos - posLineVec[i];

				//�O�όv�Z//�ӂP
				float vecLine = Vec2Cross(&vecPos, &vecWall);

				//�O�p�̒��ɓ����Ă�Ƃ��̔���
				if ((nCnt % 2 == 0 && vecLine > 0.0f) ||
					(nCnt % 2 != 0 && vecLine < 0.0f))
				{
					LineCout++;
				}
				else
				{
					break;
				}
			}
			if (LineCout == nTri)
			{
				D3DXVECTOR3 V1 = posLineVec[1] - posLineVec[0];
				D3DXVECTOR3 V2 = posLineVec[2] - posLineVec[0];

				D3DXVECTOR3 Normal;
				//A��B�̖@�������߂���
				D3DXVec3Cross(&Normal, &V1, &V2);

				//vecB ���m�[�}���C�Y���āA���� 1�ɂ���B
				D3DXVec3Normalize(&Normal, &Normal);

				D3DXVECTOR3 VecA = *pPos - posLineVec[0];
				//�v���C���[�̈ʒu�␳
				pPos->y = posLineVec[0].y - (Normal.x*(pPos->x - posLineVec[0].x) + Normal.z*(pPos->z - posLineVec[0].z)) / Normal.y;

			}
		}
		// ���_���W���A�����b�N
		mesh->pVtxBuff->Unlock();
		// ���_�C���f�b�N�X���A�����b�N
		mesh->pIdxBuff->Unlock();
	}
	return bIsLanding;
}

//=========================================
// �}�b�v�̓ǂݍ���
// Author:hamada ryuuga
//=========================================
void InitMap(char *Filename)
{
	for (int i = 0; i < MAX_TEX; i++)
	{
		MESH* mesh = &s_Mesh[i];

		if (mesh->bUse)
		{
			continue;
		}

		mesh->aMap = (int*)malloc(mesh->nVtx * sizeof(int));

		FILE *pFile = NULL;	//�t�@�C���|�C���^��錾
		int nCnt;

		VERTEX_3D* pVtx = NULL;
		mesh->pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
		//�t�@�C�����J��

		pFile = fopen(&Filename[0], "r");

		if (pFile != NULL)
		{//�t�@�C�����J�����ꍇ

			for (nCnt = 0; nCnt < mesh->nVtx; nCnt++)
			{//Map�̏�������
				fscanf(pFile, "%d", &mesh->aMap[nCnt]);
			}
			//�t�@�C�������
			fclose(pFile);
		}
		else
		{

		}

		for (nCnt = 0; nCnt < mesh->nVtx; nCnt++, pVtx++)
		{//Map�̏�������
			pVtx[0].pos.y += (5 * 10.0f)*mesh->aMap[nCnt];

		}
		// ���_���W���A�����b�N
		mesh->pVtxBuff->Unlock();

		free(mesh->aMap);


		// ���_���W�����b�N
		mesh->pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
		int WideMax = 0;
		int WideMin = MESHEND;
		for (int i = 0; i < mesh->nVtx; i++)
		{

			//�[�����Ɉ�a��������̂Ōv�Z�Œ[�����̃|�X�������ď��ɖ��߂鏈��
			float posx = ((i % mesh->X) - 1.0f);
			float posz = ((i / mesh->Z) - 1.0f)*-1.0f;

			if (i >= 0 && i <= 60)
			{
				pVtx[i].pos = D3DXVECTOR3(posx*MAX_SIZMESH, -1.0f, posz * MAX_SIZMESH);
			}
			if (i >= mesh->nVtx - 60 && i <= mesh->nVtx)
			{
				pVtx[i].pos = D3DXVECTOR3(posx*MAX_SIZMESH, -1.0f, posz * MAX_SIZMESH);
			}
			if (i == WideMax)
			{
				pVtx[i].pos = D3DXVECTOR3(posx*MAX_SIZMESH, -1.0f, posz * MAX_SIZMESH);
				WideMax += MESHLINE;
			}
			if (i == WideMax - 1)
			{
				pVtx[i].pos = D3DXVECTOR3(posx*MAX_SIZMESH, -1.0f, posz * MAX_SIZMESH);
			}
		}

		// ���_���W���A�����b�N
		mesh->pVtxBuff->Unlock();

		//�C���f�b�N�X�o�b�t�@�̃��b�N
		WORD* pIdx;
		mesh->pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);
		for (int z = 0; z < mesh->zsiz; z++)
		{
			int linetop = z * (mesh->X * 2 + 2);
			for (int x = 0; x < mesh->X; x++)
			{
				int nIdxData = x * 2 + linetop;
				pIdx[nIdxData + 1] = (WORD)(x + (z * mesh->X));
				pIdx[nIdxData] = (WORD)(pIdx[nIdxData + 1] + mesh->X);

			}
			//�k�ރ|���S���ݒ�
			if (z < mesh->xsiz - 1)
			{
				pIdx[mesh->X * 2 + 0 + linetop] = (WORD)(mesh->xsiz + mesh->X*z);
				pIdx[mesh->X * 2 + 1 + linetop] = (WORD)(mesh->X * 2 + mesh->X * z);
			}

		}
		for (int z = 0; z < (int)mesh->zsiz; z++)
		{
			int linetop = z * ((int)mesh->X * 2 + 2);
			for (int x = 0; x < (int)mesh->X; x++)
			{
				int nIdxData = x * 2 + linetop;
				pIdx[nIdxData + 1] = (WORD)(x + (z * mesh->X));
				pIdx[nIdxData] = (WORD)(pIdx[nIdxData + 1] + mesh->X);
			}
			//�k�ރ|���S���ݒ�
			if (z < mesh->xsiz - 1)
			{
				pIdx[(int)mesh->X * 2 + 0 + linetop] = (WORD)(mesh->xsiz + mesh->X*z);
				pIdx[(int)mesh->X * 2 + 1 + linetop] = (WORD)(mesh->X * 2 + mesh->X * z);
			}
			break;
		}


		//---------------------------------------
		//��������@��
		//---------------------------------------

		//�O�p�̒��_��
		const int nTri = 3;

		D3DXVECTOR3 posLineVec[nTri];//�x�N�g��

		for (int nCnt = 0; nCnt < mesh->por; nCnt++) // �v���~�e�B�u�̐������܂킷�B
		{
			//�x�N�g�������߂�
			posLineVec[0] = pVtx[pIdx[nCnt + 0]].pos;
			posLineVec[1] = pVtx[pIdx[nCnt + 1]].pos;
			posLineVec[2] = pVtx[pIdx[nCnt + 2]].pos;

			if ((pIdx[nCnt + 0] == pIdx[nCnt + 1]) ||
				(pIdx[nCnt + 0] == pIdx[nCnt + 2]) ||
				(pIdx[nCnt + 2] == pIdx[nCnt + 1]))
			{
				continue;
			}

			D3DXVECTOR3 V1 = posLineVec[1] - posLineVec[0];
			D3DXVECTOR3 V2 = posLineVec[2] - posLineVec[0];

			D3DXVECTOR3 Normal;

			if (nCnt % 2 == 0)
			{
				//A��B�̖@�������߂���
				D3DXVec3Cross(&Normal, &V2, &V1);
			}
			else
			{
				//A��B�̖@�������߂���
				D3DXVec3Cross(&Normal, &V1, &V2);
			}

			//Normal���m�[�}���C�Y���āA���� 1�ɂ���B
			D3DXVec3Normalize(&Normal, &Normal);

			for (int i = 0; i < nTri; i++)
			{//�@���v�Z
				pVtx[pIdx[nCnt + i]].nor += Normal;
			}
		}

		for (int nCnt = 0; nCnt < mesh->nVtx; nCnt++)
		{
			//nor���m�[�}���C�Y���āA���� 1�ɂ���B
			D3DXVec3Normalize(&pVtx[nCnt].nor, &pVtx[nCnt].nor);
		}

		// ���_���W���A�����b�N
		mesh->pIdxBuff->Unlock();

		mesh->bUse = true;
		break;
	}
}

//=========================================
// �}�b�v�̏�������
// Author:hamada ryuuga
//=========================================
void OutputMeshMap(char *Filename)
{
	MESH* mesh = &s_Mesh[0];

	//�t�@�C���J��
	FILE *pFile = fopen(Filename, "w");

	for (int nCnt = 0; nCnt < mesh->nVtx; nCnt++)
	{
		fprintf(pFile, "%d\t", nPosMesh[nCnt]);
	}
	fclose(pFile);
}

//=========================================
// ���b�V���̍쐬
// Author:hamada ryuuga
//=========================================
bool CreateMesh(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 Siz)
{
	bool bIsLanding = false;

	for (int i = 0; i < MAX_TEX; i++)
	{
		MESH* mesh = &s_Mesh[i];

		if (!mesh->bUse)
		{
			continue;
		}

		VERTEX_3D* pVtx = NULL;

		const int nTri = 3;
		// ���_���W�����b�N
		mesh->pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//�C���f�b�N�X�o�b�t�@�̃��b�N
		WORD* pIdx;
		mesh->pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

		D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxWorld;

		// ���[���h�}�g���b�N�X�̏�����
		// �s�񏉊����֐�(��1�����̍s���P�ʍs��ɏ�����)
		D3DXMatrixIdentity(&mtxWorld);

		// �s��ړ��֐�(��P������X,Y,Z�����̈ړ��s����쐬)
		D3DXMatrixTranslation(&mtxTrans, mesh->pos.x, mesh->pos.y, mesh->pos.z);
		// �s��|���Z�֐�(��2�����~��3�������P�����Ɋi�[)
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

		for (int nCnt = 0; nCnt < mesh->por; nCnt++)
		{
			D3DXVECTOR3 posLineVec[nTri];

			posLineVec[0] = pVtx[pIdx[nCnt + 0]].pos;
			posLineVec[1] = pVtx[pIdx[nCnt + 1]].pos;
			posLineVec[2] = pVtx[pIdx[nCnt + 2]].pos;

			if ((pIdx[nCnt + 0] == pIdx[nCnt + 1]) ||
				(pIdx[nCnt + 0] == pIdx[nCnt + 2]) ||
				(pIdx[nCnt + 2] == pIdx[nCnt + 1]))
			{//�k�ރ|���S�����Ȃ�
				continue;
			}

			for (int i = 0; i < nTri; i++)
			{//�x�N�g���R���W���}�g���b�N�X�ŕϊ�����i��Z�j
				D3DXVec3TransformCoord(&posLineVec[i], &posLineVec[i], &mtxWorld);
			}

			int  LineCout = 0;

			for (int i = 0; i < nTri; i++)
			{
				//�x�N�g��S2 V2												
				D3DXVECTOR3 vecWall = posLineVec[(i + 1) % nTri] - posLineVec[i];

				//�x�N�g�����݂�POS�Ǝn�_�܂ł̋���
				D3DXVECTOR3 vecPos = *pPos - posLineVec[i];

				//�O�όv�Z//�ӂP
				float vecLine = Vec2Cross(&vecPos, &vecWall);

				//�O�p�̒��ɓ����Ă�Ƃ��̔���
				if ((nCnt % 2 == 0 && vecLine > 0.0f) ||
					(nCnt % 2 != 0 && vecLine < 0.0f))
				{
					LineCout++;
				}
				else
				{
					break;
				}
			}
			if (LineCout == nTri)
			{
				if (GetKeyboardTrigger(DIK_O))
				{
					if (nPosMesh[pIdx[nCnt + 0]] >= -MAXMOVE)
					{
						nPosMesh[pIdx[nCnt + 0]]--;
						pVtx[pIdx[nCnt + 0]].pos.y -= MOUNTAIN;
					}
					if (nPosMesh[pIdx[nCnt + 1]] >= -MAXMOVE)
					{
						nPosMesh[pIdx[nCnt + 1]]--;
						pVtx[pIdx[nCnt + 1]].pos.y -= MOUNTAIN;
					}
					if (nPosMesh[pIdx[nCnt + 2]] >= -MAXMOVE)
					{
						nPosMesh[pIdx[nCnt + 2]]--;
						pVtx[pIdx[nCnt + 2]].pos.y -= MOUNTAIN;
					}
				}
				if (GetKeyboardTrigger(DIK_L))
				{
					if (nPosMesh[pIdx[nCnt + 0]] <= MAXMOVE)
					{
						nPosMesh[pIdx[nCnt + 0]]++;
						pVtx[pIdx[nCnt + 0]].pos.y += MOUNTAIN;
					}
					if (nPosMesh[pIdx[nCnt + 1]] <= MAXMOVE)
					{
						nPosMesh[pIdx[nCnt + 1]]++;
						pVtx[pIdx[nCnt + 1]].pos.y += MOUNTAIN;
					}
					if (nPosMesh[pIdx[nCnt + 2]] <= MAXMOVE)
					{
						nPosMesh[pIdx[nCnt + 2]]++;
						pVtx[pIdx[nCnt + 2]].pos.y += MOUNTAIN;
					}


				}

			}

		}

		// ���_���W���A�����b�N
		mesh->pVtxBuff->Unlock();
		// ���_���W���A�����b�N
		mesh->pIdxBuff->Unlock();
	}
	return bIsLanding;
}