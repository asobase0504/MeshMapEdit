//=========================================
// 
// �v���C���[�����֐�
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
// �}�N����`
//------------------------------------
#define PLAYER_MOVE				(1.5f)		// �v���C���[�̈ړ���

//------------------------------------
// �ÓI�ϐ�
//------------------------------------
static Player s_player;			// ���f���̍\����
static Model s_getModel;		// �����������f��
static int s_nSetModelType;		// �ݒ肷�郂�f���^�C�v

//------------------------------------
// �v���g�^�C�v�錾
//------------------------------------
static void SetPlayer(int nType);

//=========================================
// ������
//=========================================
void InitPlayer(void)
{
	ZeroMemory(&s_player, sizeof(s_player));
	ZeroMemory(&s_getModel, sizeof(s_getModel));

	s_nSetModelType = 0;

	// ���f���̔z�u
	LoadModel();
	SetPlayer(0);
	LoadMap();
}

//=========================================
// �I��
//=========================================
void UninitPlayer(void)
{

}

//=========================================
// �X�V
//=========================================
void UpdatePlayer(void)
{
	Player* pPlayer = &(s_player);

	// �ړ�����
	MovePlayer();
	
	// ���b�V���t�B�[���h�̓����蔻��
	CollisionMesh(&pPlayer->pos, &ZERO_VECTOR, ZERO_VECTOR);

	CreateMesh(&pPlayer->pos, &ZERO_VECTOR, ZERO_VECTOR);

	// �p�x�̐��K��
	NormalizeRot(&pPlayer->rot.y);
}

//=========================================
// �ړ�
//=========================================
void MovePlayer()
{
	D3DXVECTOR3 move = ZERO_VECTOR;		// �ړ��ʂ̏�����
	float moveLength = 0.0f;

	D3DXVECTOR2 moveInput;

	if (IsJoyPadUse(0))
	{// �W���C�p�b�h�̎g�p
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

		// ���f���̈ړ�
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
		// �J�����̊p�x���擾
		D3DXVECTOR3* CameraRot = GetRotCamera();

		D3DXVec2Normalize(&moveInput, &moveInput);

		float c = cosf(-CameraRot->y);
		float s = sinf(-CameraRot->y);

		// move �̒����� 1 �ɂȂ�B
		move.x = moveInput.x * c - moveInput.y * s;
		move.z = moveInput.x * s + moveInput.y * c;
	}
	else
	{ // ���͂���Ă��Ȃ��B
		return;
	}

	// �����x�N�g���|����ړ���
	s_player.movevec = move * moveLength * PLAYER_MOVE;
	s_player.pos += s_player.movevec;
}

//=========================================
// ���f���p�[�c�̏���
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
// �`��
//=========================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&s_player.mtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, s_player.rot.y, s_player.rot.x, s_player.rot.z);	// �s���]�֐�(��1�����Ƀ��[(y)�s�b�`(x)���[��(z)�����̉�]�s����쐬)
	D3DXMatrixMultiply(&s_player.mtxWorld, &s_player.mtxWorld, &mtxRot);						// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, s_player.pos.x, s_player.pos.y, s_player.pos.z);	// �s��ړ��֐�(��P������X,Y,Z�����̈ړ��s����쐬)
	D3DXMatrixMultiply(&s_player.mtxWorld, &s_player.mtxWorld, &mtxTrans);				// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &s_player.mtxWorld);

	D3DXMATRIX mtxScale = {};
	mtxRot = {};
	mtxTrans = {};
	D3DMATERIAL9 matDef;		// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;			// �}�e���A���f�[�^�ւ̃|�C���^

	Model* model = &(s_player.model);

	if (!model->bUse)
	{
		return;
	}

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&model->mtxWorld);

	// �X�P�[���̔��f
	D3DXMatrixScaling(&mtxScale, model->scale, model->scale, model->scale);
	D3DXMatrixMultiply(&model->mtxWorld, &model->mtxWorld, &mtxScale);			// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, model->rot.y, model->rot.x, model->rot.z);	// �s���]�֐�(��1�����Ƀ��[(y)�s�b�`(x)���[��(z)�����̉�]�s����쐬)
	D3DXMatrixMultiply(&model->mtxWorld, &model->mtxWorld, &mtxRot);					// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, model->pos.x, model->pos.y, model->pos.z);		// �s��ړ��֐�(��P������X,Y,Z�����̈ړ��s����쐬)
	D3DXMatrixMultiply(&model->mtxWorld, &model->mtxWorld, &mtxTrans);				// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)

	// ���f���̃}�g���b�N�X�ƃv���C���[�̃}�g���b�N�X�̊|���Z(�e�q�֌W�̍\�z)
	D3DXMatrixMultiply(&model->mtxWorld, &model->mtxWorld, &s_player.mtxWorld);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &model->mtxWorld);

	// ���݂̃}�e���A����ێ�
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)model->pBuffMat->GetBufferPointer();

	for (int j = 0; j < (int)model->nNumMat; j++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[j].MatD3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, model->pTexture[j]);

		// ���f���p�[�c�̕`��
		model->pMesh->DrawSubset(j);
	}

	// �ێ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//--------------------------------------------------
// �擾
//--------------------------------------------------
Player *GetPlayer(void)
{
	return &s_player;
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
void SetPlayer(int nType)
{
	s_player.model = *GetModel(nType);

	s_player.model.nIdxModelParent = -1;
	s_player.model.bUse = true;
	s_player.model.quaternion = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);	// �N�H�[�^�j�I��
}
