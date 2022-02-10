//=========================================
// 
// ���ʏ���(�w�b�_�[�t�@�C��)
// Author YudaKaito
// 
//=========================================
#ifndef _COMMON_H_
#define _COMMON_H_

#include "main.h"

#define Vtx (4)		//���_��
#define RET (D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f))
#define WHITE (D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f))

float SeteaseIn(float X);//�ꏊ.��]
//------------------------------------
// �v���g�^�C�v�錾
//------------------------------------

// �������n��

// �����`����(2D)
void InitRect(VERTEX_2D *vtx);	// �����`�̏�����
void InitRectPos(VERTEX_2D *vtx);	// ���_���W������
void SetRectCenterPos(VERTEX_2D *vtx, D3DXVECTOR3 pos, float fWidth, float fHeigth);						// ���S���W�����S�ɂ������ꍇ�̒��_�o�b�t�@�̍��W�ݒ�
void SetRectCenterRotPos(VERTEX_2D *vtx, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fAngle, float fLength);	// ���S���W�����S�ɂ������ꍇ�̒��_�o�b�t�@�̍��W�ݒ�(�p�x�̕ω��ɑΉ�)
void SetRectUpLeftPos(VERTEX_2D *vtx, D3DXVECTOR3 pos, float fWidth, float fHeigth);						// ���S���W������ɂ������ꍇ�̒��_�o�b�t�@�̍��W�ݒ�
void SetRectUpRightPos(VERTEX_2D *vtx, D3DXVECTOR3 pos, float fWidth, float fHeigth);						// ���S���W���E��ɂ������ꍇ�̒��_�o�b�t�@�̍��W�ݒ�

void InitRectColor(VERTEX_2D *vtx);						// ���_�o�b�t�@�̐F�̏�����
void SetRectColor(VERTEX_2D *vtx, D3DXCOLOR *inColor);	// ���_�o�b�t�@�̐F�ݒ�

void InitRectTex(VERTEX_2D *vtx);															// ���_�o�b�t�@�̃e�N�X�`�����W�̏�����
void SetRectTex(VERTEX_2D *vtx, float top, float bottom, float left, float right);			// ���_�o�b�t�@�̃e�N�X�`�����W�̐ݒ�

void InitRectRhw(VERTEX_2D *vtx);

// ���f���n��
void ModelSize(D3DXVECTOR3* minOut, D3DXVECTOR3* maxOut, const LPD3DXMESH mesh);	// ���f���̃T�C�Y���Z�o

// ���K���n��
float NormalizeRot(float* rot);	// �p�x�̐��K��

// �`��n��
void InitDraw(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DVERTEXBUFFER9 VtxBuff);		// �`�ʑO�̏���
void RectDraw(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DTEXTURE9 Texture, int nCnt);	// �ʏ�̕`��
void RectAddDraw(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DTEXTURE9 Texture, int nCnt);	// ���Z�����̕`��

// �Z�o�n��
float Vec2Cross(D3DXVECTOR3* v1, D3DXVECTOR3* v2);	// 2D�̊O��
float Vec2Dot(D3DXVECTOR3* v1, D3DXVECTOR3* v2);	// 2D�̓���
bool isSharpAngle(D3DXVECTOR3* pos1, D3DXVECTOR3* pos2, D3DXVECTOR3* pos3);	// �s�p���ۂ�
float CalculateDistPointLine(D3DXVECTOR3* posPoint, D3DXVECTOR3* posLine, D3DXVECTOR3* vecLine, D3DXVECTOR3* posDist, float* fLength);	// �_�Ɛ����̍ŒZ�������Z�o
float CalculateDistPointSegment(D3DXVECTOR3* posPoint, Segment* segment, D3DXVECTOR3* vecLine, D3DXVECTOR3* posDist, float* fLength);	// �_�Ɛ����̍ŒZ�������Z�o

#endif // !_COMMON_H_
