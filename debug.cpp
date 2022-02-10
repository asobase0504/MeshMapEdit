//=========================================
// 
// ゲーム内処理
// Author YudaKaito
// 
//=========================================
//------------------------------------
// include
//------------------------------------
#include "main.h"
#include "debug.h"
#include <stdio.h>
#include "polygon.h"
#include "input.h"
#include "player.h"
#include "camera.h"
#include "light.h"
#include "model.h"
#include "mesh_field.h"
#include <stdio.h>

//------------------------------------
// マクロ宣言
//------------------------------------
#define DEBUG_NUM	(13)

//------------------------------------
// 静的変数宣言
//------------------------------------
static LPD3DXFONT s_pFont = NULL;	// フォントへのポインタ

//------------------------------------
// プロトタイプ宣言
//------------------------------------

//=========================================
// FPS表示の初期化
//=========================================
void InitFPS(void)
{
	// デバッグ表示用フォントの生成
	D3DXCreateFont(GetDevice(), 32, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "UD デジタル 教科書体 NP-B", &s_pFont);
}

//=========================================
// FPS表示の終了処理
//=========================================
void UninitFPS(void)
{
	// デバッグ表示用フォントの破棄
	if (s_pFont != NULL)
	{
		s_pFont->Release();
		s_pFont = NULL;
	}
}

//=========================================
// FPSの表示
//=========================================
void DrawFPS(void)
{
	char aStr[DEBUG_NUM][256];	// 表示文字

	// 情報の取得
	D3DXVECTOR3 camerarot = *GetRotCamera();
	Player* player = GetPlayer();
	Camera* camera = GetCamera(0);
	D3DXVECTOR3 stickL = GetJoypadStick(JOYKEY_LEFT_STICK, 0);
	D3DXVECTOR3 stickR = GetJoypadStick(JOYKEY_RIGHT_STICK, 0);

	// 文字列に代入
	wsprintf(&aStr[0][0], "FPS: %d\n", GetFPS());

	// 文字列に代入
	sprintf(&aStr[1][0],	"プレイヤー情報");
	sprintf(&aStr[2][0],	"name    : %s\n", player->model.name);
	sprintf(&aStr[3][0],	"pos     : %.3f|%.3f|%.3f\n", player->pos.x, player->pos.y, player->pos.z);
	sprintf(&aStr[4][0],	"rot     : %f\n", player->rot.y);
	sprintf(&aStr[5][0],	"");
	sprintf(&aStr[6][0],	"");
	sprintf(&aStr[7][0],	" W ,A , S ,D : 移動\n");
	sprintf(&aStr[8][0],	" ↑,←,↓,→  : 微調整(0.01f)\n");
	sprintf(&aStr[9][0],	"    Q , R       : モデル回転\n");
	sprintf(&aStr[10][0],	"    Z , C       : カメラ回転");
	sprintf(&aStr[11][0], "    1 , 2       : モデルの変更");
	sprintf(&aStr[12][0], "    ENTER       : モデルの設置");

	// 表示領域の作成
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	for (int i = 0; i < DEBUG_NUM; i++)
	{
		// テキストの描画
		rect = { 0,i * 30,SCREEN_WIDTH,SCREEN_HEIGHT };

		s_pFont->DrawText(NULL, &aStr[i][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(0, 0, 255, 255));

	}
}