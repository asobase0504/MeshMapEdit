//=========================================
// 
// プレイヤー処理関数
// Author YudaKaito
// 
//=========================================
//------------------------------------
// include
//------------------------------------
#include "main.h"
#include "common.h"
#include "player.h"
#include "input.h"
#include "camera.h"
#include "model.h"
#include "mesh.h"
#include <stdio.h>
#include <math.h>

//------------------------------------
// マクロ定義
//------------------------------------
#define PLAYER_MOVE				(1.5f)		// プレイヤーの移動量

//------------------------------------
// 静的変数
//------------------------------------
static Player s_player;			// モデルの構造体
static Model s_getModel;		// くっついたモデル
static int s_nSetModelType;		// 設定するモデルタイプ

//------------------------------------
// プロトタイプ宣言
//------------------------------------
static void SetPlayer(int nType);

//=========================================
// 初期化
//=========================================
void InitPlayer(void)
{
	ZeroMemory(&s_player, sizeof(s_player));
	ZeroMemory(&s_getModel, sizeof(s_getModel));

	s_nSetModelType = 0;

	// モデルの配置
	LoadModel();
	SetPlayer(0);
	LoadMap();
}

//=========================================
// 終了
//=========================================
void UninitPlayer(void)
{

}

//=========================================
// 更新
//=========================================
void UpdatePlayer(void)
{
	Player* pPlayer = &(s_player);

	// 移動処理
	MovePlayer();
	
	// メッシュフィールドの当たり判定
	CollisionMesh(&pPlayer->pos, &ZERO_VECTOR, ZERO_VECTOR);

	CreateMesh(&pPlayer->pos, &ZERO_VECTOR, ZERO_VECTOR);

	// 角度の正規化
	NormalizeRot(&pPlayer->rot.y);
}

//=========================================
// 移動
//=========================================
void MovePlayer()
{
	D3DXVECTOR3 move = ZERO_VECTOR;		// 移動量の初期化
	float moveLength = 0.0f;

	D3DXVECTOR2 moveInput;

	if (IsJoyPadUse(0))
	{// ジョイパッドの使用
		moveInput.x = GetJoypadStick(JOYKEY_LEFT_STICK, 0).x;
		moveInput.y = -GetJoypadStick(JOYKEY_LEFT_STICK, 0).y;

		if (moveInput.x != 0.0f || moveInput.y != 0.0f)
		{
			moveLength = D3DXVec2Length(&moveInput);

			if (moveLength > 1.0f)
			{
				moveLength = 1.0f;
			}
		}
	}
	else
	{
		moveInput.x = 0.0f;
		moveInput.y = 0.0f;

		// モデルの移動
		if (GetKeyboardPress(DIK_W))
		{
			moveInput.y += 1.0f;
			moveLength = 1.0f;
		}
		if (GetKeyboardPress(DIK_A))
		{
			moveInput.x -= 1.0f;
			moveLength = 1.0f;
		}
		if (GetKeyboardPress(DIK_S))
		{
			moveInput.y -= 1.0f;
			moveLength = 1.0f;
		}
		if (GetKeyboardPress(DIK_D))
		{
			moveInput.x += 1.0f;
			moveLength = 1.0f;
		}

	}

	if (moveLength > 0.0f)
	{
		// カメラの角度情報取得
		D3DXVECTOR3* CameraRot = GetRotCamera();

		D3DXVec2Normalize(&moveInput, &moveInput);

		float c = cosf(-CameraRot->y);
		float s = sinf(-CameraRot->y);

		// move の長さは 1 になる。
		move.x = moveInput.x * c - moveInput.y * s;
		move.z = moveInput.x * s + moveInput.y * c;
	}
	else
	{ // 入力されていない。
		return;
	}

	// 方向ベクトル掛ける移動量
	s_player.movevec = move * moveLength * PLAYER_MOVE;
	s_player.pos += s_player.movevec;
}

//=========================================
// モデルパーツの消失
//=========================================
void DeleteModel(void)
{
	for (int j = 0; j < PARTS_NUM; j++)
	{
		Model* model = &s_player.model;

		if (model == NULL)
		{
			continue;
		}

		if (model->nIdxModelParent == -2)
		{
			model->bUse = false;
		}
	}
}

//=========================================
// 描画
//=========================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&s_player.mtxWorld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, s_player.rot.y, s_player.rot.x, s_player.rot.z);	// 行列回転関数(第1引数にヨー(y)ピッチ(x)ロール(z)方向の回転行列を作成)
	D3DXMatrixMultiply(&s_player.mtxWorld, &s_player.mtxWorld, &mtxRot);						// 行列掛け算関数(第2引数×第3引数第を１引数に格納)

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, s_player.pos.x, s_player.pos.y, s_player.pos.z);	// 行列移動関数(第１引数にX,Y,Z方向の移動行列を作成)
	D3DXMatrixMultiply(&s_player.mtxWorld, &s_player.mtxWorld, &mtxTrans);				// 行列掛け算関数(第2引数×第3引数第を１引数に格納)

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &s_player.mtxWorld);

	D3DXMATRIX mtxScale = {};
	mtxRot = {};
	mtxTrans = {};
	D3DMATERIAL9 matDef;		// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;			// マテリアルデータへのポインタ

	Model* model = &(s_player.model);

	if (!model->bUse)
	{
		return;
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

	// モデルのマトリックスとプレイヤーのマトリックスの掛け算(親子関係の構築)
	D3DXMatrixMultiply(&model->mtxWorld, &model->mtxWorld, &s_player.mtxWorld);

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

//--------------------------------------------------
// 取得
//--------------------------------------------------
Player *GetPlayer(void)
{
	return &s_player;
}

//--------------------------------------------------
// 設定
//--------------------------------------------------
void SetPlayer(int nType)
{
	s_player.model = *GetModel(nType);

	s_player.model.nIdxModelParent = -1;
	s_player.model.bUse = true;
	s_player.model.quaternion = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);	// クォータニオン
}
