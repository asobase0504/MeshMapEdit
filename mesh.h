//============================
//
// メッシュ設定ヘッター
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
// ポリゴンの構造体を定義
//------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;						// 頂点座標
	D3DXVECTOR3 rot;						// 回転座標
	D3DXMATRIX mtxWorld;					// ワールドマトリックス
	LPDIRECT3DTEXTURE9 pTexture;			// テクスチャ
	LPDIRECT3DINDEXBUFFER9 pIdxBuff;		//インデックスバッファ
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;		// 頂点バッファーへのポインタ
	int xsiz;								// 面数
	int zsiz;								// 面数
	int X;									// 辺の頂点数
	int Z;									// 辺の頂点数
	int nVtx;								// 頂点数
	int Index;								// インデックス
	int por;
	int* aMap;							// マップチップ
	bool bUse;								// 使用状況
} MESH;


//プロトタイプ宣言
void InitMesh(void);//初期化
void UninitMesh(void);//破棄
void UpdateMesh(void);//更新
void DrawMesh(void);//描画
void SetMesh(int X ,int Z);//場所.回転
bool CollisionMesh(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 Siz);
bool CreateMesh(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 Siz);
MESH *GetMesh(void);
void InitMap(char *Filename);
void OutputMeshMap(char *Filename);
#endif