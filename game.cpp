//=========================================
// 
// ゲーム内処理
// Author YudaKaito
// 
//=========================================
//------------------------------------
// include
//------------------------------------
#include "game.h"
#include "main.h"
#include "input.h"
#include "polygon.h"
#include "player.h"
#include "camera.h"
#include "light.h"
#include "model.h"
#include "mesh.h"
#include "fade.h"
#include "debug.h"
#include "item.h"

//------------------------------------
// マクロ定義
//------------------------------------
#define MESH_FIELD	"data/TEXTURE/bg001.jpg"
#define CREATE_MAP	"data/map03.txt"

//------------------------------------
// スタティック変数
//------------------------------------

//=========================================
// 初期化
//=========================================
void InitGame(void)
{
	// 初期化
	InitPolygon();		// ポリゴン
	InitCamera();		// カメラ
	InitLight();		// ライト
	InitModel();		// モデル
	InitPlayer();		// プレイヤー
	InitMesh();			// メッシュ
	InitMap("data/Map.txt");

	// ポリゴンの設定処理
	SetPolygon(&D3DXVECTOR3(0.0f, -200.0f, 0.0f), &D3DXVECTOR3(D3DX_PI * -0.5f, 0.0f, 0.0f), D3DXVECTOR3(100.0f, 0.0f, 100.0f), NULL, "floar");
}

//=========================================
// 終了
//=========================================
void UninitGame(void)
{
	// 終了
	UninitPlayer();			// プレイヤー
	UninitModel();			// モデル
	UninitPolygon();		// ポリゴン
	UninitCamera();			// カメラ
	UninitLight();			// ライト
	UninitMesh();			// メッシュ
}

//=========================================
// 更新
//=========================================
void UpdateGame(void)
{
	// 更新
	UpdateModel();			// モデル
	UpdatePlayer();			// プレイヤー
	UpdateGameCamera();		// カメラ
	UpdateLight();			// ライト
	UpdatePolygon();		// ポリゴン
	UpdateMesh();			// メッシュ

	// マップの更新
	if (GetJoypadTrigger(JOYKEY_START) || GetKeyboardTrigger(DIK_L))
	{
		OutputMap(CREATE_MAP);
	}
}

//=========================================
// 描画
//=========================================
void DrawGame(int cameraData)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
												
	switch (cameraData)
	{
	case 0:
		// ビューボードのクリア
		pDevice->SetViewport(&GetCamera(cameraData)->viewport);

		// 画面クリア(バックバッファ＆Zバッファのクリア)
		pDevice->Clear(0, NULL,
			(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
			D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

		SetCamera(cameraData);			// カメラ

		DrawModel();		// モデル
		DrawPlayer();		// プレイヤー
		DrawPolygonUI();	// ポリゴンUI
		DrawMesh();			// メッシュ

		DrawFPS();		// FPSの表示

		break;
	default:
		break;
	}
}