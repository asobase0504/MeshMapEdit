//=========================================
// 
// �Q�[��������
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
// �}�N����`
//------------------------------------
#define MESH_FIELD	"data/TEXTURE/bg001.jpg"
#define CREATE_MAP	"data/map03.txt"

//------------------------------------
// �X�^�e�B�b�N�ϐ�
//------------------------------------

//=========================================
// ������
//=========================================
void InitGame(void)
{
	// ������
	InitPolygon();		// �|���S��
	InitCamera();		// �J����
	InitLight();		// ���C�g
	InitModel();		// ���f��
	InitPlayer();		// �v���C���[
	InitMesh();			// ���b�V��
	InitMap("data/Map.txt");

	// �|���S���̐ݒ菈��
	SetPolygon(&D3DXVECTOR3(0.0f, -200.0f, 0.0f), &D3DXVECTOR3(D3DX_PI * -0.5f, 0.0f, 0.0f), D3DXVECTOR3(100.0f, 0.0f, 100.0f), NULL, "floar");
}

//=========================================
// �I��
//=========================================
void UninitGame(void)
{
	// �I��
	UninitPlayer();			// �v���C���[
	UninitModel();			// ���f��
	UninitPolygon();		// �|���S��
	UninitCamera();			// �J����
	UninitLight();			// ���C�g
	UninitMesh();			// ���b�V��
}

//=========================================
// �X�V
//=========================================
void UpdateGame(void)
{
	// �X�V
	UpdateModel();			// ���f��
	UpdatePlayer();			// �v���C���[
	UpdateGameCamera();		// �J����
	UpdateLight();			// ���C�g
	UpdatePolygon();		// �|���S��
	UpdateMesh();			// ���b�V��

	// �}�b�v�̍X�V
	if (GetJoypadTrigger(JOYKEY_START) || GetKeyboardTrigger(DIK_L))
	{
		OutputMap(CREATE_MAP);
	}
}

//=========================================
// �`��
//=========================================
void DrawGame(int cameraData)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
												
	switch (cameraData)
	{
	case 0:
		// �r���[�{�[�h�̃N���A
		pDevice->SetViewport(&GetCamera(cameraData)->viewport);

		// ��ʃN���A(�o�b�N�o�b�t�@��Z�o�b�t�@�̃N���A)
		pDevice->Clear(0, NULL,
			(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
			D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

		SetCamera(cameraData);			// �J����

		DrawModel();		// ���f��
		DrawPlayer();		// �v���C���[
		DrawPolygonUI();	// �|���S��UI
		DrawMesh();			// ���b�V��

		DrawFPS();		// FPS�̕\��

		break;
	default:
		break;
	}
}