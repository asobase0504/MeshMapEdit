//=========================================
// 
// �Q�[��������
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
// �}�N���錾
//------------------------------------
#define DEBUG_NUM	(13)

//------------------------------------
// �ÓI�ϐ��錾
//------------------------------------
static LPD3DXFONT s_pFont = NULL;	// �t�H���g�ւ̃|�C���^

//------------------------------------
// �v���g�^�C�v�錾
//------------------------------------

//=========================================
// FPS�\���̏�����
//=========================================
void InitFPS(void)
{
	// �f�o�b�O�\���p�t�H���g�̐���
	D3DXCreateFont(GetDevice(), 32, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "UD �f�W�^�� ���ȏ��� NP-B", &s_pFont);
}

//=========================================
// FPS�\���̏I������
//=========================================
void UninitFPS(void)
{
	// �f�o�b�O�\���p�t�H���g�̔j��
	if (s_pFont != NULL)
	{
		s_pFont->Release();
		s_pFont = NULL;
	}
}

//=========================================
// FPS�̕\��
//=========================================
void DrawFPS(void)
{
	char aStr[DEBUG_NUM][256];	// �\������

	// ���̎擾
	D3DXVECTOR3 camerarot = *GetRotCamera();
	Player* player = GetPlayer();
	Camera* camera = GetCamera(0);
	D3DXVECTOR3 stickL = GetJoypadStick(JOYKEY_LEFT_STICK, 0);
	D3DXVECTOR3 stickR = GetJoypadStick(JOYKEY_RIGHT_STICK, 0);

	// ������ɑ��
	wsprintf(&aStr[0][0], "FPS: %d\n", GetFPS());

	// ������ɑ��
	sprintf(&aStr[1][0],	"�v���C���[���");
	sprintf(&aStr[2][0],	"name    : %s\n", player->model.name);
	sprintf(&aStr[3][0],	"pos     : %.3f|%.3f|%.3f\n", player->pos.x, player->pos.y, player->pos.z);
	sprintf(&aStr[4][0],	"rot     : %f\n", player->rot.y);
	sprintf(&aStr[5][0],	"");
	sprintf(&aStr[6][0],	"");
	sprintf(&aStr[7][0],	" W ,A , S ,D : �ړ�\n");
	sprintf(&aStr[8][0],	" ��,��,��,��  : ������(0.01f)\n");
	sprintf(&aStr[9][0],	"    Q , R       : ���f����]\n");
	sprintf(&aStr[10][0],	"    Z , C       : �J������]");
	sprintf(&aStr[11][0], "    1 , 2       : ���f���̕ύX");
	sprintf(&aStr[12][0], "    ENTER       : ���f���̐ݒu");

	// �\���̈�̍쐬
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	for (int i = 0; i < DEBUG_NUM; i++)
	{
		// �e�L�X�g�̕`��
		rect = { 0,i * 30,SCREEN_WIDTH,SCREEN_HEIGHT };

		s_pFont->DrawText(NULL, &aStr[i][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(0, 0, 255, 255));

	}
}