//============================
//
// メッシュ設定(ななめ)
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
// マクロ定義
//------------------------------------
#define MAXMOVE		(4)	//メッシュへこます最大数
#define MAX_TEX		(4)	//メッシュへこます最大数
#define MOUNTAIN	(5 * 10.0f)					// 値が１ずれる度変化する値
#define MESHTEXFILE	"data/TEXTURE/草.jpg"	// テクスチャファイル

//------------------------------------
// static変数
//------------------------------------
static MESH s_Mesh[MAX_TEX];					// ポリゴンの構造体
static int* nPosMesh = NULL;

//=========================================
// 初期化処理
// Author: hamada ryuuga
// Aythor: Yuda Kaito
//=========================================
void InitMesh(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	for (int i = 0; i < MAX_TEX; i++)
	{
		MESH* mesh = &s_Mesh[i];

		// 初期化処理
		mesh->pos = ZERO_VECTOR;
		mesh->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 回転座標

		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			MESHTEXFILE,
			&mesh->pTexture);

		//初期化
		mesh->xsiz = MAX_MESH;
		mesh->zsiz = MAX_MESH;

		//辺の頂点数
		mesh->X = mesh->xsiz + 1;//1多い数字
		mesh->Z = mesh->zsiz + 1;//1多い数字

		//頂点数
		mesh->nVtx = mesh->X* mesh->Z;//頂点数を使ってるよ

		//Vtxのサイズ分データを確保する
		nPosMesh = (int*)malloc(mesh->nVtx * sizeof(int));

		//インデックス数
		mesh->Index = (2 * mesh->X * mesh->zsiz + 2 * (mesh->zsiz - 1));

		mesh->por = mesh->Index - 2;

		// 頂点バッファの生成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * mesh->nVtx,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&mesh->pVtxBuff,
			NULL);

		//インデックスバッファ生成
		pDevice->CreateIndexBuffer(sizeof(WORD) * mesh->Index,
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,
			D3DPOOL_MANAGED,
			&mesh->pIdxBuff,
			NULL);

		VERTEX_3D* pVtx = NULL;

		// 頂点座標をロック
		mesh->pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		for (int i = 0; i < mesh->nVtx; i++)
		{
			nPosMesh[i] = 0;
			float posx = ((i % mesh->X) - 1.0f);
			float posz = ((i / mesh->Z) - 1.0f)*-1.0f;

			float texU = 1.0f / mesh->xsiz*(i % mesh->X);
			float texV = 1.0f / mesh->zsiz*(i / mesh->Z);

			//めっしゅを真ん中にする補正
			mesh->pos = D3DXVECTOR3(-(posx - 1)*MAX_SIZMESH / 2, 0.0f, -posz * MAX_SIZMESH / 2);


			//座標の補正
			pVtx[i].pos += D3DXVECTOR3(posx*MAX_SIZMESH, -1.0f, posz * MAX_SIZMESH);

			// 各頂点の法線の設定(※ベクトルの大きさは1にする必要がある)
			pVtx[i].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			// 頂点カラーの設定
			pVtx[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx[i].tex = D3DXVECTOR2(texU, texV);

		}

		// 頂点座標をアンロック
		mesh->pVtxBuff->Unlock();



		// 頂点座標をロック
		mesh->pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
		int WideMax = 0;
		int WideMin = MESHEND;
		for (int i = 0; i < mesh->nVtx; i++)
		{

			//端っこに違和感があるので計算で端っこのポスをだして床に埋める処理
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

		// 頂点座標をアンロック
		mesh->pVtxBuff->Unlock();



		//インデックスバッファのロック
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
			//縮退ポリゴン設定
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
			//縮退ポリゴン設定
			if (z < mesh->xsiz - 1)
			{
				pIdx[(int)mesh->X * 2 + 0 + linetop] = (WORD)(mesh->xsiz + mesh->X*z);
				pIdx[(int)mesh->X * 2 + 1 + linetop] = (WORD)(mesh->X * 2 + mesh->X * z);
			}
		}

		//---------------------------------------
		//ここから法線
		//---------------------------------------

		//三角の頂点数
		const int nTri = 3;

		D3DXVECTOR3 posLineVec[nTri];//ベクトル

		for (int nCnt = 0; nCnt < mesh->por; nCnt++) // プリミティブの数だけまわす。
		{
			//ベクトルを求める
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
				//AとBの法線を求めるやつ
				D3DXVec3Cross(&Normal, &V2, &V1);
			}
			else
			{
				//AとBの法線を求めるやつ
				D3DXVec3Cross(&Normal, &V1, &V2);
			}

			//Normalをノーマライズして、長さ 1にする。
			D3DXVec3Normalize(&Normal, &Normal);

			for (int i = 0; i < nTri; i++)
			{//法線計算
				pVtx[pIdx[nCnt + i]].nor += Normal;
			}
		}

		for (int nCnt = 0; nCnt < mesh->nVtx; nCnt++)
		{
			//norをノーマライズして、長さ 1にする。
			D3DXVec3Normalize(&pVtx[nCnt].nor, &pVtx[nCnt].nor);
		}

		// 頂点座標をアンロック
		mesh->pIdxBuff->Unlock();

	}
}

//=========================================
// 終了処理
// Author: hamada ryuuga
// Aythor: Yuda Kaito
//=========================================
void UninitMesh(void)
{
	for (int i = 0; i < MAX_TEX; i++)
	{
		MESH* mesh = &s_Mesh[i];
		// 頂点バッファーの解放
		if (mesh->pVtxBuff != NULL)
		{
			mesh->pVtxBuff->Release();
			mesh->pVtxBuff = NULL;
		}

		// メッシュテクスチャの解放
		if (mesh->pTexture != NULL)
		{
			mesh->pTexture->Release();
			mesh->pTexture = NULL;
		}

		// インデックスバッファの解放
		if (mesh->pIdxBuff != NULL)
		{
			mesh->pIdxBuff->Release();
			mesh->pIdxBuff = NULL;
		}

		//デリーと
		if (nPosMesh != NULL)
		{
			free(nPosMesh);
			nPosMesh = NULL;
		}
	}
}

//=========================================
// 更新処理
// Author: hamada ryuuga
// Aythor: Yuda Kaito
//=========================================
void UpdateMesh(void)
{		
}

//=========================================
// 描画処理
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
		D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス

		// ワールドマトリックスの初期化
		// 行列初期化関数(第1引数の行列を単位行列に初期化)
		D3DXMatrixIdentity(&mesh->mtxWorld);

		// 向きを反映
		// 行列回転関数(第1引数にヨー(y)ピッチ(x)ロール(z)方向の回転行列を作成)
		D3DXMatrixRotationYawPitchRoll(&mtxRot, mesh->rot.y, mesh->rot.x, mesh->rot.z);
		// 行列掛け算関数(第2引数×第3引数第を１引数に格納)
		D3DXMatrixMultiply(&mesh->mtxWorld, &mesh->mtxWorld, &mtxRot);

		// 位置を反映
		// 行列移動関数(第１引数にX,Y,Z方向の移動行列を作成)
		D3DXMatrixTranslation(&mtxTrans, mesh->pos.x, mesh->pos.y, mesh->pos.z);
		// 行列掛け算関数(第2引数×第3引数第を１引数に格納)
		D3DXMatrixMultiply(&mesh->mtxWorld, &mesh->mtxWorld, &mtxTrans);

		// ワールド座標行列の設定
		pDevice->SetTransform(D3DTS_WORLD, &mesh->mtxWorld);

		// 頂点バッファをデバイスのデータストリームに設定
		pDevice->SetStreamSource(0, mesh->pVtxBuff, 0, sizeof(VERTEX_3D));

		//インデックスバッファ設定
		pDevice->SetIndices(mesh->pIdxBuff);
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);
		//テクスチャの設定
		pDevice->SetTexture(0, mesh->pTexture);

		// ポリゴンの描画
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, mesh->nVtx, 0, mesh->por);


		//テクスチャの設定
		pDevice->SetTexture(0, NULL);
	}
}

//=========================================
// メッシュ設定
// Author:hamada ryuuga
//=========================================
void SetMesh(int X ,int Z)//場所.回転
{
	for (int i = 0; i < MAX_TEX; i++)
	{
		MESH* mesh = &s_Mesh[i];
		// 頂点バッファーの解放
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

		// 初期化処理
		mesh->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		mesh->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 回転座標

		//初期化
		mesh->xsiz = X;
		mesh->zsiz = Z;

		//辺の頂点数
		mesh->X = mesh->xsiz + 1;//1多い数字
		mesh->Z = mesh->zsiz + 1;//1多い数字

		mesh->nVtx = mesh->X* mesh->Z;//頂点数を使ってるよ

		//インデックス数
		mesh->Index = (2 * mesh->X * mesh->zsiz + 2 * (mesh->zsiz - 1));

		mesh->por = mesh->Index - 2;
		//頂点バッファの生成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * mesh->nVtx,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&mesh->pVtxBuff,
			NULL);

		//インデックスバッファ生成
		pDevice->CreateIndexBuffer(sizeof(WORD) * mesh->Index,
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,
			D3DPOOL_MANAGED,
			&mesh->pIdxBuff,
			NULL);

		VERTEX_3D* pVtx = NULL;

		// 頂点座標をロック
		mesh->pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		for (int i = 0; i < mesh->nVtx; i++)
		{
			float posx = ((i % mesh->X) - 1.0f);
			float posz = ((i / mesh->Z) - 1.0f)*-1.0f;

			float texU = 1.0f / mesh->xsiz*(i % mesh->X);
			float texV = 1.0f / mesh->zsiz*(i / mesh->Z);

			//めっしゅを真ん中にする補正
			mesh->pos = D3DXVECTOR3(-(posx - 1)*MAX_SIZMESH / 2, 0.0f, -posz * MAX_SIZMESH / 2);
			if (i <= mesh->nVtx / 2)
			{
				//pos
				pVtx[i].pos += D3DXVECTOR3(posx*MAX_SIZMESH, (float)sin(i)*60.0f, posz * MAX_SIZMESH);
			}



			// 各頂点の法線の設定(※ベクトルの大きさは1にする必要がある)
			pVtx[i].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// 頂点カラーの設定
			pVtx[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx[i].tex = D3DXVECTOR2(texU, texV);

		}

		//インデックスバッファのロック
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
			//縮退ポリゴン設定
			if (z < mesh->xsiz - 1)
			{
				pIdx[(int)mesh->X * 2 + 0 + linetop] = (WORD)(mesh->xsiz + mesh->X*z);
				pIdx[(int)mesh->X * 2 + 1 + linetop] = (WORD)(mesh->X * 2 + mesh->X * z);
			}
		}
		//三角の頂点数
		const int nTri = 3;

		D3DXVECTOR3 posLineVec[nTri];//ベクトル

		for (int nCnt = 0; nCnt < mesh->por; nCnt++) // プリミティブの数だけまわす。
		{
			//ベクトルを求める
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
				//AとBの法線を求めるやつ
				D3DXVec3Cross(&Normal, &V2, &V1);
			}
			else
			{
				//AとBの法線を求めるやつ
				D3DXVec3Cross(&Normal, &V1, &V2);
			}

			//Normalをノーマライズして、長さ 1にする。
			D3DXVec3Normalize(&Normal, &Normal);

			for (int i = 0; i < nTri; i++)
			{//法線計算
				pVtx[pIdx[nCnt + i]].nor += Normal;
			}
		}

		for (int nCnt = 0; nCnt < mesh->nVtx; nCnt++)
		{
			//norをノーマライズして、長さ 1にする。
			D3DXVec3Normalize(&pVtx[nCnt].nor, &pVtx[nCnt].nor);
		}

		// 頂点座標をアンロック
		mesh->pIdxBuff->Unlock();

		// 頂点座標をアンロック
		mesh->pVtxBuff->Unlock();
	}
}

//=========================================
// ゲット(構造体)
// Author:hamada ryuuga
//=========================================
MESH *GetMesh(void)
{
	return s_Mesh;
}

//=========================================
// 当たり判定
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

		// 頂点座標をロック
		VERTEX_3D* pVtx = NULL;
		mesh->pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//インデックスバッファのロック
		WORD* pIdx;
		mesh->pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

		D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス
		D3DXMATRIX mtxWorld;

		// ワールドマトリックスの初期化
		// 行列初期化関数(第1引数の行列を単位行列に初期化)
		D3DXMatrixIdentity(&mtxWorld);

		// 行列移動関数(第１引数にX,Y,Z方向の移動行列を作成)
		D3DXMatrixTranslation(&mtxTrans, mesh->pos.x, mesh->pos.y, mesh->pos.z);
		// 行列掛け算関数(第2引数×第3引数を第１引数に格納)
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
			{//縮退ポリゴンを省き
				continue;
			}

			for (int i = 0; i < nTri; i++)
			{//ベクトル３座標をマトリックスで変換する（乗算）
				D3DXVec3TransformCoord(&posLineVec[i], &posLineVec[i], &mtxWorld);
			}

			int  LineCout = 0;

			for (int i = 0; i < nTri; i++)
			{
				//ベクトルS2 V2												
				D3DXVECTOR3 vecWall = posLineVec[(i + 1) % nTri] - posLineVec[i];

				//ベクトル現在のPOSと始点までの距離
				D3DXVECTOR3 vecPos = *pPos - posLineVec[i];

				//外積計算//辺１
				float vecLine = Vec2Cross(&vecPos, &vecWall);

				//三角の中に入ってるときの判定
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
				//AとBの法線を求めるやつ
				D3DXVec3Cross(&Normal, &V1, &V2);

				//vecB をノーマライズして、長さ 1にする。
				D3DXVec3Normalize(&Normal, &Normal);

				D3DXVECTOR3 VecA = *pPos - posLineVec[0];
				//プレイヤーの位置補正
				pPos->y = posLineVec[0].y - (Normal.x*(pPos->x - posLineVec[0].x) + Normal.z*(pPos->z - posLineVec[0].z)) / Normal.y;

			}
		}
		// 頂点座標をアンロック
		mesh->pVtxBuff->Unlock();
		// 頂点インデックスをアンロック
		mesh->pIdxBuff->Unlock();
	}
	return bIsLanding;
}

//=========================================
// マップの読み込み
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

		FILE *pFile = NULL;	//ファイルポインタを宣言
		int nCnt;

		VERTEX_3D* pVtx = NULL;
		mesh->pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
		//ファイルを開く

		pFile = fopen(&Filename[0], "r");

		if (pFile != NULL)
		{//ファイルが開いた場合

			for (nCnt = 0; nCnt < mesh->nVtx; nCnt++)
			{//Mapの書き込み
				fscanf(pFile, "%d", &mesh->aMap[nCnt]);
			}
			//ファイルを閉じる
			fclose(pFile);
		}
		else
		{

		}

		for (nCnt = 0; nCnt < mesh->nVtx; nCnt++, pVtx++)
		{//Mapの書き込み
			pVtx[0].pos.y += (5 * 10.0f)*mesh->aMap[nCnt];

		}
		// 頂点座標をアンロック
		mesh->pVtxBuff->Unlock();

		free(mesh->aMap);


		// 頂点座標をロック
		mesh->pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
		int WideMax = 0;
		int WideMin = MESHEND;
		for (int i = 0; i < mesh->nVtx; i++)
		{

			//端っこに違和感があるので計算で端っこのポスをだして床に埋める処理
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

		// 頂点座標をアンロック
		mesh->pVtxBuff->Unlock();

		//インデックスバッファのロック
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
			//縮退ポリゴン設定
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
			//縮退ポリゴン設定
			if (z < mesh->xsiz - 1)
			{
				pIdx[(int)mesh->X * 2 + 0 + linetop] = (WORD)(mesh->xsiz + mesh->X*z);
				pIdx[(int)mesh->X * 2 + 1 + linetop] = (WORD)(mesh->X * 2 + mesh->X * z);
			}
			break;
		}


		//---------------------------------------
		//ここから法線
		//---------------------------------------

		//三角の頂点数
		const int nTri = 3;

		D3DXVECTOR3 posLineVec[nTri];//ベクトル

		for (int nCnt = 0; nCnt < mesh->por; nCnt++) // プリミティブの数だけまわす。
		{
			//ベクトルを求める
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
				//AとBの法線を求めるやつ
				D3DXVec3Cross(&Normal, &V2, &V1);
			}
			else
			{
				//AとBの法線を求めるやつ
				D3DXVec3Cross(&Normal, &V1, &V2);
			}

			//Normalをノーマライズして、長さ 1にする。
			D3DXVec3Normalize(&Normal, &Normal);

			for (int i = 0; i < nTri; i++)
			{//法線計算
				pVtx[pIdx[nCnt + i]].nor += Normal;
			}
		}

		for (int nCnt = 0; nCnt < mesh->nVtx; nCnt++)
		{
			//norをノーマライズして、長さ 1にする。
			D3DXVec3Normalize(&pVtx[nCnt].nor, &pVtx[nCnt].nor);
		}

		// 頂点座標をアンロック
		mesh->pIdxBuff->Unlock();

		mesh->bUse = true;
		break;
	}
}

//=========================================
// マップの書き込み
// Author:hamada ryuuga
//=========================================
void OutputMeshMap(char *Filename)
{
	MESH* mesh = &s_Mesh[0];

	//ファイル開け
	FILE *pFile = fopen(Filename, "w");

	for (int nCnt = 0; nCnt < mesh->nVtx; nCnt++)
	{
		fprintf(pFile, "%d\t", nPosMesh[nCnt]);
	}
	fclose(pFile);
}

//=========================================
// メッシュの作成
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
		// 頂点座標をロック
		mesh->pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//インデックスバッファのロック
		WORD* pIdx;
		mesh->pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

		D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス
		D3DXMATRIX mtxWorld;

		// ワールドマトリックスの初期化
		// 行列初期化関数(第1引数の行列を単位行列に初期化)
		D3DXMatrixIdentity(&mtxWorld);

		// 行列移動関数(第１引数にX,Y,Z方向の移動行列を作成)
		D3DXMatrixTranslation(&mtxTrans, mesh->pos.x, mesh->pos.y, mesh->pos.z);
		// 行列掛け算関数(第2引数×第3引数を第１引数に格納)
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
			{//縮退ポリゴンを省き
				continue;
			}

			for (int i = 0; i < nTri; i++)
			{//ベクトル３座標をマトリックスで変換する（乗算）
				D3DXVec3TransformCoord(&posLineVec[i], &posLineVec[i], &mtxWorld);
			}

			int  LineCout = 0;

			for (int i = 0; i < nTri; i++)
			{
				//ベクトルS2 V2												
				D3DXVECTOR3 vecWall = posLineVec[(i + 1) % nTri] - posLineVec[i];

				//ベクトル現在のPOSと始点までの距離
				D3DXVECTOR3 vecPos = *pPos - posLineVec[i];

				//外積計算//辺１
				float vecLine = Vec2Cross(&vecPos, &vecWall);

				//三角の中に入ってるときの判定
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

		// 頂点座標をアンロック
		mesh->pVtxBuff->Unlock();
		// 頂点座標をアンロック
		mesh->pIdxBuff->Unlock();
	}
	return bIsLanding;
}