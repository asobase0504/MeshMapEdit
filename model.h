//=========================================
// 
// モデルの作成(ヘッダーファイル)
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
// モデルの構造体定義
//------------------------------------
typedef struct
{
	// 基本情報
	char name[255];		// 名前
	float sizeCriter;	// くっつくサイズの制限
	float sizeAdd;		// くっついたときに加算するサイズ量
	int nType;			// モデルタイプ
	D3DXVECTOR3 pos;				// 位置
	D3DXVECTOR3 pos_old;			// 前回位置
	D3DXVECTOR3 pos_world;			// ワールド位置
	D3DXVECTOR3 rot;				// 角度

	// 当たり判定情報
	COLLISION_TYPE typeCollision;	// 当たり判定の種類
	D3DXVECTOR3 pos_Collision;		// 当たり判定の基準値
	float fLength;					// 球の当たり判定の大きさ

	// モデル情報
	LPD3DXMESH pMesh;				// メッシュ情報へのポインタ		// 頂点の集まりのこと
	LPD3DXBUFFER pBuffMat;			// マテリアル情報へのポインタ	// 1つのXファイルに複数のマテリアルが入っている
	LPDIRECT3DTEXTURE9 *pTexture;	// テクスチャへのポインタ
	DWORD nNumMat;					// マテリアル情報の数
	D3DXMATRIX mtxWorld;			// ワールドマトリックス
	float scale;					// モデルスケール

	// クオータニオン情報
	D3DXQUATERNION quaternion;		// クオータニオン
	bool isQuaternion;				// クオータニオンを使用するかどうか。

	D3DXVECTOR3 movevec;			// ベクトル
	float moverot;					// 移動時の回転量
	D3DXVECTOR3 move;				// 移動量
	D3DXVECTOR3 MinVtx;				// 頂点の最小値
	D3DXVECTOR3 MaxVtx;				// 頂点の最大値
	int nIdxModelParent;			// 親モデルのインデックス
	bool bUse;						// 使用状況
}Model;

//------------------------------------
// プロトタイプ宣言
//------------------------------------
void InitModel(void);				// モデルの初期化処理
void UninitModel(void);				// モデルの終了処理
void UpdateModel(void);				// モデルの更新処理
void DrawModel(void);				// モデルの描画処理
Model* GetModel(void);				// モデルの取得処理
Model* GetModel(int nType);			// モデルの取得処理
void LoadModel(void);				// モデルの読み込み処理
void LoadMap(void);					// モデルマップの読み込み処理
Model* SetModel(Model* model);		// モデルの設定(読み込みされたモデル参照)
Model* SetModel(int nType);			// モデルの設定(読み込みされたモデル参照)
void OutputMap(char *Filename);		// アイテムの設置

#endif // !_MODEL_H_
