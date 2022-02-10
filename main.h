//=========================================
// 
// ���C���̃w�b�_�[�t�@�C��
// Author YudaKaito
// 
//=========================================
#ifndef _MAIN_H_	// ���̃}�N����`������ĂȂ�������
#define _MAIN_H_	// 2�d�C���N���[�h�h�~�̃}�N����`


//------------------------------------
// include
//------------------------------------
#include <windows.h>
#include "d3dx9.h"						// �`�揈���ɕK�v
#define DIRECTINPUT_VERSION	(0x0800)	// �r���h���̌x���Ώ��p�}�N��
#include "dinput.h"						// ���͏����ɕK�v
#include "xaudio2.h"					// ���y�����ɕK�v
#include "Xinput.h"						// �W���C�p�b�g�����ɕK�v

//------------------------------------
// ���C�u�����̃����N
//------------------------------------
#pragma comment(lib,"d3d9.lib")		// �`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")	// [3d9.lib]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")	// DirectX�R���|�[�l���g(���i)�g�p�ɕK�v
#pragma comment(lib,"winmm.lib")	// �V�X�e�������擾�ɕK�v
#pragma comment(lib,"dinput8.lib")	// ���͏����ɕK�v
#pragma comment(lib,"xinput.lib")	// �W���C�p�b�g�����ɕK�v

#define SCREEN_WIDTH	(80 * 16)			// �E�B���h�E�̕�
#define SCREEN_HEIGHT	(80 * 9)			// �E�C���h�E�̍���

#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)				// ���W�E�J���[�E�e�N�X�`�����W
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)	// ���W�E�@���E�J���[�E�e�N�X�`�����W
#define FVF_VERTEX_LINE		(D3DFVF_XYZ | D3DFVF_DIFFUSE)							// ���_�t�H�[�}�b�g[��] �ʒu�E�J���[

#define ZERO_VECTOR		(D3DXVECTOR3(0.0f, 0.0f, 0.0f))		// �[���x�N�g��
#define ZERO_QUATERNION	(D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f))

//------------------------------------
// ���_���[2D]�̍\���̂��`
//------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	float rhw;			// ���W�ϊ��p�W���i1.0f�ŌŒ�)
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`���̍��W
} VERTEX_2D;

//------------------------------------
// ���_���[3D]�̍\���̂��`
//------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	D3DXVECTOR3 nor;	// �@���x�N�g��
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`���̍��W
} VERTEX_3D;

//------------------------------------
// ���̍\���̂��`
//------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	D3DCOLOR col;		// ���_�J���[
}VERTEX_LINE;

//------------------------------------
// ���(���[�h)�̎��
//------------------------------------
typedef enum
{
	MODE_TITLE = 0,	// �^�C�g�����
	MODE_GAME,		// �Q�[�����
	MODE_TUTORIAL,	// �`���[�g���A�����
	MODE_RESULT,	// �����L���O���
	MODE_MAX
}MODE;

//------------------------------------
// �����̍\���̂��`
//------------------------------------
typedef struct
{
	D3DXVECTOR3 s;		// ���_���W
	D3DXVECTOR3 v;		// ���_���W
}Segment;

//------------------------------------
// �v���g�^�C�v�錾
//------------------------------------
LPDIRECT3DDEVICE9 GetDevice(void);	// �f�o�C�X�̎擾
void SetMode(MODE mode);
MODE GetMode(void);
int GetFPS(void);

#endif	// !_MAIN_H_