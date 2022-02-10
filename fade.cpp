//====================================
// 
// ��ʑJ�ڂ̏���
// Author Yuda Kaito
// 
//====================================

//------------------------------------
// include
//------------------------------------
#include "main.h"
#include "fade.h"
#include "common.h"
#include "camera.h"

//------------------------------------
// �O���[�o���ϐ�
//------------------------------------
static LPDIRECT3DVERTEXBUFFER9 s_pVtxBuff = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
static FADE s_fade;									// �t�F�[�h�̏��
static MODE s_modeNext;								// ���̉��(���[�h)
static D3DXCOLOR s_colorFade;						// �|���S��(�t�F�[�h)�̐F

//====================================
// ��ʑJ�ڂ̏���������
//====================================
void InitFade(MODE modeNext)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	s_fade = FADE_IN;		// �t�F�[�h�C����Ԃ�
	s_modeNext = modeNext;	// ���̉��(���[�h)��ݒ�
	s_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);	// �����|���S��(�s����)�ɂ��Ă���

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&s_pVtxBuff,
		NULL);

	VERTEX_2D *pVtx;		// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	SetRectUpLeftPos(pVtx, D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT);

	// rhw�̐ݒ�
	InitRectRhw(pVtx);

	// ���_�J���[�̐ݒ�
	SetRectColor(pVtx, &(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)));

	// �e�N�X�`�����W�̐ݒ�
	InitRectTex(pVtx);

	// ���_�o�b�t�@���A�����b�N����
	s_pVtxBuff->Unlock();

	// ���[�h�̐ݒ�
	SetMode(s_modeNext);
}

//====================================
// ��ʑJ�ڂ̏I������
//====================================
void UninitFade(void)
{
	// ���_�o�b�t�@�̔j��
	if (s_pVtxBuff != NULL)
	{
		s_pVtxBuff->Release();
		s_pVtxBuff = NULL;
	}
}

//====================================
// ��ʑJ�ڂ̍X�V����
//====================================
void UpdateFade(void)
{
	if (s_fade != FADE_NONE)
	{
		if (s_fade == FADE_IN)
		{// �t�F�[�h�C�����
			s_colorFade.a -= 0.01f;	// �|���S���𓧖��ɂ��Ă���

			if (s_colorFade.a <= 0.0f)
			{
				s_colorFade.a = 0.0f;
				s_fade = FADE_NONE;	// �������Ă��Ȃ���Ԃ�
			}

		}
		else if (s_fade == FADE_OUT)
		{// �t�F�[�h�A�E�g���
			s_colorFade.a += 0.01f;

			if (s_colorFade.a >= 1.0f)
			{
				s_colorFade.a = 1.0f;
				s_fade = FADE_IN;	// �t�F�[�h�C����u��

				// ���[�h�ݒ�(���̉�ʂɈڍs)
				SetMode(s_modeNext);
			}

		}

		VERTEX_2D *pVtx;		// ���_���ւ̃|�C���^

		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_�J���[�̐ݒ�
		SetRectColor(pVtx, &(s_colorFade));

		// ���_�o�b�t�@���A�����b�N����
		s_pVtxBuff->Unlock();
	}
}

//====================================
// ��ʑJ�ڂ̕`�揈��
//====================================
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	// �`�揈��
	InitDraw(pDevice, s_pVtxBuff);

	// �e�N�X�`���̕`��
	RectDraw(pDevice, NULL, 0);
}

//====================================
// ��ʑJ�ڂ̐ݒ菈��
//====================================
void SetFade(MODE modeNext)
{
	if (s_modeNext != modeNext)
	{
		s_fade = FADE_OUT;		// �t�F�[�h�A�E�g��Ԃ�
		s_modeNext = modeNext;	// ���̉��(���[�h)��ݒ�
		s_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	// �����|���S��(����)�ɂ��Ă���
	}
}

//====================================
// ��ʑJ�ڂ̋����ݒ菈��
//====================================
void ResetFade(MODE modeNext)
{
	s_fade = FADE_OUT;		// �t�F�[�h�A�E�g��Ԃ�
	s_modeNext = modeNext;	// ���̉��(���[�h)��ݒ�
	s_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	// �����|���S��(����)�ɂ��Ă���
}

//====================================
// ��ʑJ�ڂ̎擾����
//====================================
FADE GetFade(void)
{
	return s_fade;
}