//============================
//
// �A�C�e���ݒ�
// Author: Yuda Kaito
//
//============================

//------------------------------------
// include
//------------------------------------
#include <stdio.h>
#include "item.h"
#include "player.h"
#include "model.h"
#include "input.h"
#include "common.h"
#include "camera.h"

//------------------------------------
// �}�N��
//------------------------------------
#define Attenuation	(0.5f)		//�����W��
#define Speed	(1.0f)			//�X�s�[�h
#define WIDTH (10.0f)			//���f���̔��a
#define Vtx (4)					//���_��

//------------------------------------
// static�ϐ�
//------------------------------------
static bool s_bIsLanding;
static Model s_Model;			// �|���S���̍\����
static int s_nSetModelType;		// �ݒ肷�郂�f���^�C�v

//------------------------------------
// �v���g�^�C�v�錾
//------------------------------------
static void MoveItem(void);
static void SelectItem(void);

//=========================================
// ����������
//=========================================
void InitItem(void)
{
	s_nSetModelType = 0;
	ZeroMemory(&s_Model, sizeof(s_Model));
}

//=========================================
// �I������
//=========================================
void UninitItem(void)
{
	Model* model = &s_Model;

	if (model->pTexture != NULL)
	{
		for (int j = 0; j < (int)model->nNumMat; j++)
		{
			if (model->pTexture[j] != NULL)
			{// �e�N�X�`���̉��
				model->pTexture[j]->Release();
				model->pTexture[j] = NULL;
			}
		}

		delete[]model->pTexture;
		model->pTexture = NULL;
	}

	// ���b�V���̉��
	if (model->pMesh != NULL)
	{
		model->pMesh->Release();
		model->pMesh = NULL;
	}
	// �}�e���A���̉��
	if (model->pBuffMat != NULL)
	{
		model->pBuffMat->Release();
		model->pBuffMat = NULL;
	}
}

//=========================================
// �X�V����
//=========================================
void UpdateItem(void)
{
	Model* model = &s_Model;

	model->pos_old = model->pos;
	model->pos_world = D3DXVECTOR3(model->mtxWorld._41, model->mtxWorld._42, model->mtxWorld._43);

	// �ړ�����
	MoveItem();

	// �v���C���[�Ə��̓����蔻��
	//CollisionMeshField(&pPlayer->pos);

	// �p�x�̐��K��
	NormalizeRot(&model->rot.y);

	// ���f����I�ԏ���
	SelectItem();
}

//=========================================
// �`�揈��
//=========================================
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScale, mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;				// �}�e���A���f�[�^�ւ̃|�C���^

	Model* model = &s_Model;

	if (!model->bUse)
	{
		return;
	}

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&model->mtxWorld);

	// �X�P�[���̔��f
	D3DXMatrixScaling(&mtxScale, model->scale, model->scale, model->scale);
	D3DXMatrixMultiply(&model->mtxWorld, &model->mtxWorld, &mtxScale);					// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)

	// �p�x�̔��f
	if (model->isQuaternion)
	{
		// �N�H�[�^�j�I���̎g�p�����p���̐ݒ�
		D3DXMatrixRotationQuaternion(&mtxRot, &model->quaternion);			// �N�I�[�^�j�I���ɂ��s���]
		D3DXMatrixMultiply(&model->mtxWorld, &model->mtxWorld, &mtxRot);	// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
	}
	else
	{
		// �����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, model->rot.y, model->rot.x, model->rot.z);	// �s���]�֐�(��1�����Ƀ��[(y)�s�b�`(x)���[��(z)�����̉�]�s����쐬)
		D3DXMatrixMultiply(&model->mtxWorld, &model->mtxWorld, &mtxRot);					// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
	}

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, model->pos.x, model->pos.y, model->pos.z);		// �s��ړ��֐�(��P������X,Y,Z�����̈ړ��s����쐬)
	D3DXMatrixMultiply(&model->mtxWorld, &model->mtxWorld, &mtxTrans);				// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)

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

//=========================================
// �ړ�����
//=========================================
static void MoveItem(void)
{
	D3DXVECTOR2 moveInput;
	D3DXVECTOR3 move = ZERO_VECTOR;			// �ړ��ʂ̏�����
	float moveLength = 0.0f;

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
		if (GetKeyboardPress(DIK_UP))
		{
			moveInput.y += 1.0f;
			moveLength = 1.0f;
		}
		if (GetKeyboardPress(DIK_LEFT))
		{
			moveInput.x -= 1.0f;
			moveLength = 1.0f;
		}
		if (GetKeyboardPress(DIK_DOWN))
		{
			moveInput.y -= 1.0f;
			moveLength = 1.0f;
		}
		if (GetKeyboardPress(DIK_RIGHT))
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

	Model* model = &s_Model;

	// �����x�N�g���|����ړ���
	model->pos += move * moveLength;

	if (model->pos.y - model->fLength <= 0.0f)
	{
		model->pos.y = model->fLength;
	}
}

//=========================================
// �I������
//=========================================
static void SelectItem(void)
{
	Model* model = &s_Model;

	if (GetJoypadTrigger(JOYKEY_A))
	{
		//model->nType = s_nSetModelType;
		//model->nIdxModelParent = -2;
		//model->quaternion = ZERO_QUATERNION;
		//model->isQuaternion = true;
		//model->bUse = true;
		//model->pos = model->pos;
	}
	if (GetJoypadTrigger(JOYKEY_RIGHT_SHOULDER))
	{
		if (s_nSetModelType <= 100)
		{
			s_Model = GetModel()[s_nSetModelType];
			s_nSetModelType++;
		}
	}
	if (GetJoypadTrigger(JOYKEY_LEFT_SHOULDER))
	{
		if (s_nSetModelType >= 1)
		{
			s_Model = GetModel()[s_nSetModelType];
			s_nSetModelType--;
		}
	}
}
