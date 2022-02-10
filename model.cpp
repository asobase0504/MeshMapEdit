//=========================================
// 
// ���f�������֐�
// Author YudaKaito
// 
//=========================================
//------------------------------------
// include
//------------------------------------
#include "main.h"
#include "model.h"
#include "common.h"
#include "input.h"
#include "camera.h"
#include "player.h"
#include <stdio.h>

#include "load.h"

//------------------------------------
// �}�N����`
//------------------------------------
#define MODEL_NUM				(100)
#define PLAYER_MOVE				(1.0f)
#define MODEL_ROT_ATTENUATION	(0.05f)
#define MODEL_LOAD_FILE			("data/model.txt")
#define MAP_LOAD_FILE			("data/map03.txt")

//------------------------------------
// �ÓI�ϐ�
//------------------------------------
static Model s_ModelType[MODEL_NUM];	// ���f���̎�ނ�ۊ�
static Model s_Model[MODEL_MAX];		// ���ۂɃ��f�����Ǘ�����\����

//=========================================
// ������
//=========================================
void InitModel(void)
{
	ZeroMemory(s_ModelType, sizeof(s_ModelType));
	ZeroMemory(s_Model, sizeof(s_Model));
}

//=========================================
// �I��
//=========================================
void UninitModel(void)
{
	for (int i = 0; i < MODEL_NUM; i++)
	{
		Model* model = &(s_ModelType[i]);

		if (model->pTexture != NULL)
		{
			for (int j = 0; j < (int)model->nNumMat; j++)
			{
				if (model->pTexture[j] != NULL)
				{// �e�N�X�`���̉��
					model->pTexture[j]->Release();
					model->pTexture[j] = NULL;
				}
			}

			delete[]model->pTexture;
			model->pTexture = NULL;
		}

		// ���b�V���̉��
		if (model->pMesh != NULL)
		{
			model->pMesh->Release();
			model->pMesh = NULL;
		}
		// �}�e���A���̉��
		if (model->pBuffMat != NULL)
		{
			model->pBuffMat->Release();
			model->pBuffMat = NULL;
		}
	}
}

//=========================================
// �X�V
//=========================================
void UpdateModel(void)
{
}

//=========================================
// �`��
//=========================================
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScale, mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;				// �}�e���A���f�[�^�ւ̃|�C���^

	for (int i = 0; i < MODEL_MAX; i++)
	{
		Model* model = &(s_Model[i]);

		if (!model->bUse)
		{
			continue;
		}

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&model->mtxWorld);

		// �X�P�[���̔��f
		D3DXMatrixScaling(&mtxScale, model->scale, model->scale, model->scale);
		D3DXMatrixMultiply(&model->mtxWorld, &model->mtxWorld, &mtxScale);			// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)

		// �����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, model->rot.y, model->rot.x, model->rot.z);	// �s���]�֐�(��1�����Ƀ��[(y)�s�b�`(x)���[��(z)�����̉�]�s����쐬)
		D3DXMatrixMultiply(&model->mtxWorld, &model->mtxWorld, &mtxRot);					// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, model->pos.x, model->pos.y, model->pos.z);		// �s��ړ��֐�(��P������X,Y,Z�����̈ړ��s����쐬)
		D3DXMatrixMultiply(&model->mtxWorld, &model->mtxWorld, &mtxTrans);				// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)

		// �v���C���[�Ƃ������Ă����Ԃ̃��f���̓v���C���[�Ƃ̍s��v�Z
		if (model->nIdxModelParent != -2)
		{
			D3DXMATRIX mtxParent;
		
			if (model->nIdxModelParent == -1)
			{
				mtxParent = GetPlayer()->mtxWorld;
			}
			else
			{
				mtxParent = s_Model[model->nIdxModelParent].mtxWorld;
			}

			D3DXMatrixMultiply(&model->mtxWorld, &model->mtxWorld, &mtxParent);
		}

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &model->mtxWorld);

		// ���݂̃}�e���A����ێ�
		pDevice->GetMaterial(&matDef);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)model->pBuffMat->GetBufferPointer();

		for (int j = 0; j < (int)model->nNumMat; j++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[j].MatD3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, model->pTexture[j]);

			// ���f���p�[�c�̕`��
			model->pMesh->DrawSubset(j);
		}

		// �ێ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}

//=========================================
// �z�񎩑̂��擾
//=========================================
Model* GetModel()
{
	return s_ModelType;
}

//=========================================
// ����̃��f�����擾
//=========================================
Model* GetModel(int nType)
{
	return &s_ModelType[nType];
}

//=========================================
// �ǂݍ��ݏ���
//=========================================
void LoadModel(void)
{
	FILE* pFile;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	bool isType = false;
	char modelFile[255][255] = {};
	int nModelFileCnt = 0;

	pFile = fopen(MODEL_LOAD_FILE, "r");

	char read[255] = {};
	while (1)
	{
		fscanf(pFile, "%s", &read);

		//# �����o����ƈ�s�ǂݍ���
		if (strncmp(&read[0], "#", 1) == 0)
		{
			fgets(read, 255, pFile);
			continue;
		}

		if (strcmp(&read[0], "END_SCRIPT") == 0)
		{
			break;
		}

		if (strcmp(&read[0], "TYPESET") == 0)
		{
			isType = true;
		}

		if (strcmp(&read[0], "END_TYPESET") == 0)
		{
			nModelFileCnt++;
			isType = false;
		}

		if (isType)
		{
			if (strcmp(&read[0], "FILENAME") == 0)
			{
				fscanf(pFile, "%s", &read);
				fscanf(pFile, "%s", &modelFile[nModelFileCnt][0]);

				Model* modelType = &(s_ModelType[nModelFileCnt]);

				modelType->scale = 1.0f;

				// X�t�@�C���̓ǂݍ���
				D3DXLoadMeshFromX(&modelFile[nModelFileCnt][0],
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&modelType->pBuffMat,
					NULL,
					&modelType->nNumMat,
					&modelType->pMesh);

				// ���b�V���Ɏg�p����Ă���e�N�X�`���p�̔z���p�ӂ���
				modelType->pTexture = new LPDIRECT3DTEXTURE9[modelType->nNumMat];

				// �o�b�t�@�̐擪�|�C���^��D3DXMATERIAL�ɃL���X�g���Ď擾
				D3DXMATERIAL *pMat = (D3DXMATERIAL*)modelType->pBuffMat->GetBufferPointer();

				// �e���b�V���̃}�e���A�������擾����
				for (int i = 0; i < (int)modelType->nNumMat; i++)
				{
					modelType->pTexture[i] = NULL;

					if (pMat[i].pTextureFilename != NULL)
					{// �}�e���A���Őݒ肳��Ă���e�N�X�`���ǂݍ���
						D3DXCreateTextureFromFileA(pDevice,
							pMat[i].pTextureFilename,
							&modelType->pTexture[i]);
					}
				}

				// ���f���̃T�C�Y�v��
				ModelSize(&modelType->MinVtx, &modelType->MaxVtx, modelType->pMesh);
			}
			if (strcmp(&read[0], "NAME") == 0)
			{
				Model* modelType = &(s_ModelType[nModelFileCnt]);

				fscanf(pFile, "%s", &read);
				fscanf(pFile, "%s", &modelType->name[0]);
			}
			if (strcmp(&read[0], "SIZE_CRITERIA") == 0)
			{
				Model* modelType = &(s_ModelType[nModelFileCnt]);

				fscanf(pFile, "%s", &read);
				fscanf(pFile, "%f", &modelType->sizeCriter);
			}
			if (strcmp(&read[0], "SIZE_ADD") == 0)
			{
				Model* modelType = &(s_ModelType[nModelFileCnt]);

				fscanf(pFile, "%s", &read);
				fscanf(pFile, "%f", &modelType->sizeAdd);
			}
			if (strcmp(&read[0], "COLLISION_SPHERE") == 0)
			{
				Model* modelType = &(s_ModelType[nModelFileCnt]);

				fscanf(pFile, "%s", &read);
				fscanf(pFile, "%f", &modelType->fLength);

				modelType->typeCollision = COLLISION_SPHERE;
			}
			if (strcmp(&read[0], "COLLISION_POS") == 0)
			{
				Model* modelType = &(s_ModelType[nModelFileCnt]);

				fscanf(pFile, "%s", &read);
				fscanf(pFile, "%f %f %f", &modelType->pos_Collision.x, &modelType->pos_Collision.y, &modelType->pos_Collision.z);
			}
			if (strcmp(&read[0], "SCALE") == 0)
			{
				Model* modelType = &(s_ModelType[nModelFileCnt]);

				fscanf(pFile, "%s", &read);
				fscanf(pFile, "%f", &modelType->scale);
			}
		}
	}
	fclose(pFile);
}

//=========================================
// �ǂݍ��ݏ���
//=========================================
void LoadMap(void)
{
	FILE* pFile;
	bool isModel = false;
	bool isPlayer = false;
	int nModelCnt = 1;
	int nModelData;

	pFile = fopen(MAP_LOAD_FILE, "r");

	char read[255] = {};
	while (1)
	{
		fscanf(pFile, "%s", &read);

		//# �����o����ƈ�s�ǂݍ���
		if (strncmp(&read[0], "#", 1) == 0)
		{
			fgets(read, 255, pFile);
			continue;
		}

		if (strcmp(&read[0], "END_SCRIPT") == 0)
		{
			break;
		}

		if (strcmp(&read[0], "MODELSET") == 0)
		{
			for (nModelData = 0; nModelData < MODEL_MAX; nModelData++)
			{
				if (!s_Model[nModelData].bUse)
				{
					break;
				}
			}
			isModel = true;
		}
		else if (strcmp(&read[0], "PLAYERSET") == 0)
		{
			for (nModelData = 0; nModelData < MODEL_MAX; nModelData++)
			{
				if (!s_Model[nModelData].bUse)
				{
					break;
				}
			}
			isPlayer = true;
		}

		if (strcmp(&read[0], "END_MODELSET") == 0)
		{
			isModel = false;
		}
		else if (strcmp(&read[0], "END_PLAYERSET") == 0)
		{
			isPlayer = false;
		}

		if (isModel)
		{
			if (strcmp(&read[0], "TYPE") == 0)
			{
				int nData;

				fscanf(pFile, "%s", &read);
				fscanf(pFile, "%d", &nData);

				s_Model[nModelData] = s_ModelType[nData];
				s_Model[nModelData].nType = nData;
				s_Model[nModelData].nIdxModelParent = -2;
				s_Model[nModelData].bUse = true;
			}
			if (strcmp(&read[0], "POS") == 0)
			{
				D3DXVECTOR3 pos;

				fscanf(pFile, "%s", &read);
				fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
				s_Model[nModelData].pos = pos;
			}
			if (strcmp(&read[0], "ROT") == 0)
			{
				D3DXVECTOR3 rot;

				fscanf(pFile, "%s", &read);
				fscanf(pFile, "%f %f %f", &rot.x, &rot.y, &rot.z);
				s_Model[nModelData].rot = rot;
			}
		}
		if (isPlayer)
		{
			if (strcmp(&read[0], "TYPE") == 0)
			{
				int nData;

				fscanf(pFile, "%s", &read);
				fscanf(pFile, "%d", &nData);

				s_Model[nModelData] = s_ModelType[nData];

				s_Model[nModelData].nIdxModelParent = -2;
				s_Model[nModelData].bUse = true;
			}
			if (strcmp(&read[0], "POS") == 0)
			{
				D3DXVECTOR3 pos;

				fscanf(pFile, "%s", &read);
				fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
				s_Model[nModelData].pos = pos;
			}
		}
	}
	fclose(pFile);
}

//=========================================
// �ݒ�
//=========================================
Model* SetModel(Model* model)
{
	for (int i = 0; i < MODEL_MAX; i++)
	{
		Model* pModel = &(s_Model[i]);

		if (pModel->bUse)
		{
			continue;
		}

		pModel = model;

		return pModel;
	}
	return NULL;
}

//=========================================
// �ݒ�
//=========================================
Model* SetModel(int nType)
{
	for (int i = 0; i < MODEL_MAX; i++)
	{
		Model* pModel = &(s_Model[i]);

		if (pModel->bUse)
		{
			continue;
		}

		s_Model[i] = s_ModelType[nType];
		s_Model[i].nType = nType;
		s_Model[i].nIdxModelParent = -2;
		s_Model[i].bUse = true;

		return pModel;
	}
	return NULL;
}

//=========================================
// �ݒ�
//=========================================
Model* SetModel(char* file)
{
	for (int i = 0; i < MODEL_MAX; i++)
	{
		Model* pModel = &(s_Model[i]);

		if (pModel->bUse)
		{
			continue;
		}

		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(file,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&pModel->pBuffMat,
			NULL,
			&pModel->nNumMat,
			&pModel->pMesh);

		// ���b�V���Ɏg�p����Ă���e�N�X�`���p�̔z���p�ӂ���
		pModel->pTexture = new LPDIRECT3DTEXTURE9[pModel->nNumMat];

		// �o�b�t�@�̐擪�|�C���^��D3DXMATERIAL�ɃL���X�g���Ď擾
		D3DXMATERIAL *pMat = (D3DXMATERIAL*)pModel->pBuffMat->GetBufferPointer();

		// �e���b�V���̃}�e���A�������擾����
		for (int j = 0; j < (int)pModel->nNumMat; j++)
		{
			pModel->pTexture[j] = NULL;

			if (pMat[j].pTextureFilename != NULL)
			{// �}�e���A���Őݒ肳��Ă���e�N�X�`���ǂݍ���
				D3DXCreateTextureFromFileA(pDevice,
					pMat[j].pTextureFilename,
					&pModel->pTexture[j]);
			}
		}

		// ���f���̃T�C�Y�v��
		ModelSize(&pModel->MinVtx, &pModel->MaxVtx, pModel->pMesh);

		pModel->bUse = true;

		return pModel;
	}
	return NULL;
}

//=========================================
// �}�b�v�̏o�͏���
// Author hamada ryuuga
// Author YudaKaito
//=========================================
void OutputMap(char *Filename)
{
	//�t�@�C���J��
	FILE *pFile = fopen(Filename, "w");

	fprintf(pFile, "SCRIPT\n\n");
	fprintf(pFile, "#------------------------------------------------------------------------------\n");
	fprintf(pFile, "# �v���C���[�̐ݒu\n");
	fprintf(pFile, "#------------------------------------------------------------------------------\n");

	fprintf(pFile, "PLAYERSET\n");
	fprintf(pFile, "TYPE = %d\n", s_Model[0].nType);
	fprintf(pFile, "ROT = %.4f %.4f %.4f\n", s_Model[0].pos.x, s_Model[0].pos.y, s_Model[0].pos.z);
	fprintf(pFile, "END_PLAYERSET\n");

	fprintf(pFile, "#------------------------------------------------------------------------------\n");
	fprintf(pFile, "# ���f���̐ݒu\n");
	fprintf(pFile, "#------------------------------------------------------------------------------\n");
	for (int nCnt = 0; nCnt < PARTS_NUM; nCnt++)
	{
		Model* model = &s_Model[nCnt];

		if (model == NULL || !model->bUse)
		{
			continue;
		}

		fprintf(pFile, "# %s\n", model->name);
		fprintf(pFile, "MODELSET\n");
		fprintf(pFile, "TYPE = %d\n", model->nType);
		fprintf(pFile, "POS = %.4f %.4f %.4f\n", model->pos.x, model->pos.y, model->pos.z);
		fprintf(pFile, "ROT = %.4f %.4f %.4f\n", model->rot.x, model->rot.y, model->rot.z);

		fprintf(pFile, "END_MODELSET\n");
		fprintf(pFile, "\n");
	}
	fprintf(pFile, "END_SCRIPT\n\n");

	fclose(pFile);
}
