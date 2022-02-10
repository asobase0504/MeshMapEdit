//=========================================
// 
// �e�̏���
// Author YudaKaito
// 
//=========================================
//------------------------------------
// include
//------------------------------------
#include "main.h"
#include "load.h"
#include "model.h"
#include "common.h"
#include <stdio.h>

//------------------------------------
// �}�N����`
//------------------------------------
#define MODEL_LOAD_FILE			("data/model.txt")
#define MAP_LOAD_FILE			("data/map.txt")
#define MODEL_NUM				(100)

//------------------------------------
// �ÓI�ϐ�
//------------------------------------
static Model s_ModelType[MODEL_NUM];	// ���f���̎�ނ�ۊ�

//=========================================
// ���f���̃o�C�i���t�@�C����
//=========================================
void WritingBinaryModel(void)
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
		}
	}
	fclose(pFile);

	pFile = fopen("data/model.bin", "wb");

	if (pFile != NULL)
	{// �t�@�C�����J�����ꍇ
	 // �t�@�C���̏�������
		fwrite(s_ModelType, sizeof(Model), MODEL_NUM, pFile);
		//�t�@�C�������
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ��ꍇ
		printf("\n * * * �t�@�C�����J���܂��� * * * \n");
	}

}

//=========================================
// �}�b�v�̃o�C�i���t�@�C����
//=========================================
void WritingBinaryMap(void)
{
}
