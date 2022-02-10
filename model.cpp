//=========================================
// 
// モデル処理関数
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
// マクロ定義
//------------------------------------
#define MODEL_NUM				(100)
#define PLAYER_MOVE				(1.0f)
#define MODEL_ROT_ATTENUATION	(0.05f)
#define MODEL_LOAD_FILE			("data/model.txt")
#define MAP_LOAD_FILE			("data/map03.txt")

//------------------------------------
// 静的変数
//------------------------------------
static Model s_ModelType[MODEL_NUM];	// モデルの種類を保管
static Model s_Model[MODEL_MAX];		// 実際にモデルを管理する構造体

//=========================================
// 初期化
//=========================================
void InitModel(void)
{
	ZeroMemory(s_ModelType, sizeof(s_ModelType));
	ZeroMemory(s_Model, sizeof(s_Model));
}

//=========================================
// 終了
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
				{// テクスチャの解放
					model->pTexture[j]->Release();
					model->pTexture[j] = NULL;
				}
			}

			delete[]model->pTexture;
			model->pTexture = NULL;
		}

		// メッシュの解放
		if (model->pMesh != NULL)
		{
			model->pMesh->Release();
			model->pMesh = NULL;
		}
		// マテリアルの解放
		if (model->pBuffMat != NULL)
		{
			model->pBuffMat->Release();
			model->pBuffMat = NULL;
		}
	}
}

//=========================================
// 更新
//=========================================
void UpdateModel(void)
{
}

//=========================================
// 描画
//=========================================
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScale, mtxRot, mtxTrans;	// 計算用マトリックス
	D3DMATERIAL9 matDef;			// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;				// マテリアルデータへのポインタ

	for (int i = 0; i < MODEL_MAX; i++)
	{
		Model* model = &(s_Model[i]);

		if (!model->bUse)
		{
			continue;
		}

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&model->mtxWorld);

		// スケールの反映
		D3DXMatrixScaling(&mtxScale, model->scale, model->scale, model->scale);
		D3DXMatrixMultiply(&model->mtxWorld, &model->mtxWorld, &mtxScale);			// 行列掛け算関数(第2引数×第3引数第を１引数に格納)

		// 向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, model->rot.y, model->rot.x, model->rot.z);	// 行列回転関数(第1引数にヨー(y)ピッチ(x)ロール(z)方向の回転行列を作成)
		D3DXMatrixMultiply(&model->mtxWorld, &model->mtxWorld, &mtxRot);					// 行列掛け算関数(第2引数×第3引数第を１引数に格納)

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, model->pos.x, model->pos.y, model->pos.z);		// 行列移動関数(第１引数にX,Y,Z方向の移動行列を作成)
		D3DXMatrixMultiply(&model->mtxWorld, &model->mtxWorld, &mtxTrans);				// 行列掛け算関数(第2引数×第3引数第を１引数に格納)

		// プレイヤーとくっついている状態のモデルはプレイヤーとの行列計算
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

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &model->mtxWorld);

		// 現在のマテリアルを保持
		pDevice->GetMaterial(&matDef);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)model->pBuffMat->GetBufferPointer();

		for (int j = 0; j < (int)model->nNumMat; j++)
		{
			// マテリアルの設定
			pDevice->SetMaterial(&pMat[j].MatD3D);

			// テクスチャの設定
			pDevice->SetTexture(0, model->pTexture[j]);

			// モデルパーツの描写
			model->pMesh->DrawSubset(j);
		}

		// 保持していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}

//=========================================
// 配列自体を取得
//=========================================
Model* GetModel()
{
	return s_ModelType;
}

//=========================================
// 特定のモデルを取得
//=========================================
Model* GetModel(int nType)
{
	return &s_ModelType[nType];
}

//=========================================
// 読み込み処理
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

		//# を検出すると一行読み込む
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

				// Xファイルの読み込み
				D3DXLoadMeshFromX(&modelFile[nModelFileCnt][0],
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&modelType->pBuffMat,
					NULL,
					&modelType->nNumMat,
					&modelType->pMesh);

				// メッシュに使用されているテクスチャ用の配列を用意する
				modelType->pTexture = new LPDIRECT3DTEXTURE9[modelType->nNumMat];

				// バッファの先頭ポインタをD3DXMATERIALにキャストして取得
				D3DXMATERIAL *pMat = (D3DXMATERIAL*)modelType->pBuffMat->GetBufferPointer();

				// 各メッシュのマテリアル情報を取得する
				for (int i = 0; i < (int)modelType->nNumMat; i++)
				{
					modelType->pTexture[i] = NULL;

					if (pMat[i].pTextureFilename != NULL)
					{// マテリアルで設定されているテクスチャ読み込み
						D3DXCreateTextureFromFileA(pDevice,
							pMat[i].pTextureFilename,
							&modelType->pTexture[i]);
					}
				}

				// モデルのサイズ計測
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
// 読み込み処理
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

		//# を検出すると一行読み込む
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
// 設定
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
// 設定
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
// 設定
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

		// Xファイルの読み込み
		D3DXLoadMeshFromX(file,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&pModel->pBuffMat,
			NULL,
			&pModel->nNumMat,
			&pModel->pMesh);

		// メッシュに使用されているテクスチャ用の配列を用意する
		pModel->pTexture = new LPDIRECT3DTEXTURE9[pModel->nNumMat];

		// バッファの先頭ポインタをD3DXMATERIALにキャストして取得
		D3DXMATERIAL *pMat = (D3DXMATERIAL*)pModel->pBuffMat->GetBufferPointer();

		// 各メッシュのマテリアル情報を取得する
		for (int j = 0; j < (int)pModel->nNumMat; j++)
		{
			pModel->pTexture[j] = NULL;

			if (pMat[j].pTextureFilename != NULL)
			{// マテリアルで設定されているテクスチャ読み込み
				D3DXCreateTextureFromFileA(pDevice,
					pMat[j].pTextureFilename,
					&pModel->pTexture[j]);
			}
		}

		// モデルのサイズ計測
		ModelSize(&pModel->MinVtx, &pModel->MaxVtx, pModel->pMesh);

		pModel->bUse = true;

		return pModel;
	}
	return NULL;
}

//=========================================
// マップの出力処理
// Author hamada ryuuga
// Author YudaKaito
//=========================================
void OutputMap(char *Filename)
{
	//ファイル開く
	FILE *pFile = fopen(Filename, "w");

	fprintf(pFile, "SCRIPT\n\n");
	fprintf(pFile, "#------------------------------------------------------------------------------\n");
	fprintf(pFile, "# プレイヤーの設置\n");
	fprintf(pFile, "#------------------------------------------------------------------------------\n");

	fprintf(pFile, "PLAYERSET\n");
	fprintf(pFile, "TYPE = %d\n", s_Model[0].nType);
	fprintf(pFile, "ROT = %.4f %.4f %.4f\n", s_Model[0].pos.x, s_Model[0].pos.y, s_Model[0].pos.z);
	fprintf(pFile, "END_PLAYERSET\n");

	fprintf(pFile, "#------------------------------------------------------------------------------\n");
	fprintf(pFile, "# モデルの設置\n");
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
