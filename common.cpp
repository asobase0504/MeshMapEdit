//=========================================
// 
// ���ʏ���
// Author: Yuda Kaito
// Author: hamada ryuuga
// 
//=========================================
#include "common.h"

//=========================================
// �����`�̏�����
// Author: Yuda Kaito
//=========================================
void InitRect(VERTEX_2D * vtx)
{
	// ���_���W�̐ݒ�
	InitRectPos(vtx);

	// ���_�J���[�̐ݒ�
	InitRectColor(vtx);

	// �e�N�X�`�����W�̐ݒ�
	InitRectTex(vtx);

	// rhw �̐ݒ�
	InitRectRhw(vtx);
}

//=========================================
// ���_�o�b�t�@��POS��������
// Author: Yuda Kaito
//=========================================
void InitRectPos(VERTEX_2D * vtx)
{
	vtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=========================================
// ���_���W��POS��ݒ�(���S����)
// Author: Yuda Kaito
//=========================================
void SetRectCenterPos(VERTEX_2D *vtx, D3DXVECTOR3 pos, float fWidth, float fHeigth)
{
	vtx[0].pos.x = pos.x - fWidth;
	vtx[0].pos.y = pos.y - fHeigth;
	vtx[0].pos.z = pos.z + 0.0f;

	vtx[1].pos.x = pos.x + fWidth;
	vtx[1].pos.y = pos.y - fHeigth;
	vtx[1].pos.z = pos.z + 0.0f;

	vtx[2].pos.x = pos.x - fWidth;
	vtx[2].pos.y = pos.y + fHeigth;
	vtx[2].pos.z = pos.z + 0.0f;

	vtx[3].pos.x = pos.x + fWidth;
	vtx[3].pos.y = pos.y + fHeigth;
	vtx[3].pos.z = pos.z + 0.0f;
}

//=========================================
// ���_���W��ݒ�(���S)(�p�x�Ή�)
// Author: Yuda Kaito
//=========================================
void SetRectCenterRotPos(VERTEX_2D * vtx, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fAngle, float fLength)
{
	//���_���W�̐ݒ�
	vtx[0].pos.x = pos.x + sinf(rot.z + (-D3DX_PI + fAngle)) * fLength;
	vtx[0].pos.y = pos.y + cosf(rot.z + (-D3DX_PI + fAngle)) * fLength;
	vtx[0].pos.z = 0.0f;

	vtx[1].pos.x = pos.x + sinf(rot.z + (D3DX_PI - fAngle)) * fLength;
	vtx[1].pos.y = pos.y + cosf(rot.z + (D3DX_PI - fAngle)) * fLength;
	vtx[1].pos.z = 0.0f;

	vtx[2].pos.x = pos.x + sinf(rot.z + (fAngle * -1.0f)) * fLength;
	vtx[2].pos.y = pos.y + cosf(rot.z + (fAngle * -1.0f)) * fLength;
	vtx[2].pos.z = 0.0f;

	vtx[3].pos.x = pos.x + sinf(rot.z + fAngle) * fLength;
	vtx[3].pos.y = pos.y + cosf(rot.z + fAngle) * fLength;
	vtx[3].pos.z = 0.0f;

}

//=========================================
// ���_���W��ݒ�(���ォ��)
// Author: Yuda Kaito
//=========================================
void SetRectUpLeftPos(VERTEX_2D * vtx, D3DXVECTOR3 pos, float fWidth, float fHeigth)
{
	vtx[0].pos.x = pos.x;
	vtx[0].pos.y = pos.y;
	vtx[0].pos.z = pos.z;

	vtx[1].pos.x = pos.x + fWidth;
	vtx[1].pos.y = pos.y;
	vtx[1].pos.z = pos.z + 0.0f;

	vtx[2].pos.x = pos.x;
	vtx[2].pos.y = pos.y + fHeigth;
	vtx[2].pos.z = pos.z + 0.0f;

	vtx[3].pos.x = pos.x + fWidth;
	vtx[3].pos.y = pos.y + fHeigth;
	vtx[3].pos.z = pos.z + 0.0f;
}

//=========================================
// ���_���W��ݒ�(�E�ォ��)
// Author: Yuda Kaito
//=========================================
void SetRectUpRightPos(VERTEX_2D * vtx, D3DXVECTOR3 pos, float fWidth, float fHeigth)
{
	vtx[0].pos.x = pos.x - fWidth;
	vtx[0].pos.y = pos.y;
	vtx[0].pos.z = pos.z;

	vtx[1].pos.x = pos.x;
	vtx[1].pos.y = pos.y;
	vtx[1].pos.z = pos.z;

	vtx[2].pos.x = pos.x - fWidth;
	vtx[2].pos.y = pos.y + fHeigth;
	vtx[2].pos.z = pos.z;

	vtx[3].pos.x = pos.x;
	vtx[3].pos.y = pos.y + fHeigth;
	vtx[3].pos.z = pos.z;
}

//=========================================
// ���_�o�b�t�@�̃J���[��������
// Author: Yuda Kaito
//=========================================
void InitRectColor(VERTEX_2D * vtx)
{
	for (int i = 0; i < 4; ++i)
	{
		vtx->col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vtx++;
	}
}

//=========================================
// ���_�o�b�t�@�̃J���[��ݒ�
// Author: Yuda Kaito
//=========================================
void SetRectColor(VERTEX_2D *vtx, D3DXCOLOR *inColor)
{
	for (int i = 0; i < 4; ++i)
	{
		vtx->col = *inColor;
		vtx++;
	}
}

//=========================================
// ���_�o�b�t�@�̃e�N�X�`�����W�̏�����
// Author: Yuda Kaito
//=========================================
void InitRectTex(VERTEX_2D * vtx)
{
	vtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}

//=========================================
// ���_�o�b�t�@�̃e�N�X�`�����W�̐ݒ�
// Author: Yuda Kaito
//=========================================
void SetRectTex(VERTEX_2D * vtx, float top, float bottom, float left, float right)
{
	vtx[0].tex = D3DXVECTOR2(left, top);
	vtx[1].tex = D3DXVECTOR2(right, top);
	vtx[2].tex = D3DXVECTOR2(left, bottom);
	vtx[3].tex = D3DXVECTOR2(right, bottom);

}

//=========================================
// rhw �̏�����
// Author: Yuda Kaito
//=========================================
void InitRectRhw(VERTEX_2D * vtx)
{
	// rhw �̐ݒ�
	vtx[0].rhw = 1.0f;
	vtx[1].rhw = 1.0f;
	vtx[2].rhw = 1.0f;
	vtx[3].rhw = 1.0f;
}


//=========================================
// �p�x�̐��K��
// Author: Yuda Kaito
//=========================================
float NormalizeRot(float* rot)
{
	if (*rot > D3DX_PI)
	{
		*rot -= D3DX_PI * 2;
	}
	if (*rot < -D3DX_PI)
	{
		*rot += D3DX_PI * 2;
	}

	return *rot;
}

//=========================================
// �`�ʏ����ɑO��Ƃ��ĕK�v�ȕ���
// Author: Yuda Kaito
//=========================================
void InitDraw(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DVERTEXBUFFER9 VtxBuff)
{
	// ���_�o�b�t�@���f�[�^�X�g���[���ݒ�
	pDevice->SetStreamSource(0, VtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
}

//=========================================
// ���Z�����Ȃ��̕`��(�����`)
// Author: Yuda Kaito
//=========================================
void RectDraw(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DTEXTURE9 Texture, int nCnt)
{
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, Texture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt, 2);
}

//=========================================
// ���Z�����L��̕`��(�����`)
// Author: Yuda Kaito
//=========================================
void RectAddDraw(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DTEXTURE9 Texture, int nCnt)
{
	// a�u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	RectDraw(pDevice, Texture, nCnt);

	// a�u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=========================================
// ���f���̃T�C�Y���Z�o
// Author: Yuda Kaito
// ����1 minOut	���f���̍ŏ����_�̏o��
// ����2 maxOut	���f���̍ő咸�_�̏o��
// ����3 mesh	�T�C�Y���v�����郂�f��
//=========================================
void ModelSize(D3DXVECTOR3* minOut, D3DXVECTOR3* maxOut, LPD3DXMESH mesh)
{
	int nNumVtx;		// ���_��
	DWORD sizeFVF;		// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;		// ���_�o�b�t�@�[�ւ̃|�C���g

	nNumVtx = mesh->GetNumVertices();	// ���_���̎擾

	sizeFVF = D3DXGetFVFVertexSize(mesh->GetFVF());	// ���_�t�H�[�}�b�g�̃T�C�Y���擾

	// ������
	*minOut = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);
	*maxOut = D3DXVECTOR3(-FLT_MAX, -FLT_MAX, -FLT_MAX);

	// ���_�o�b�t�@�[�̃��b�N
	mesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		if (vtx.x < minOut->x)
		{
			minOut->x = vtx.x;
		}
		if (vtx.y < minOut->y)
		{
			minOut->y = vtx.y;
		}
		if (vtx.z < minOut->z)
		{
			minOut->z = vtx.z;
		}
		if (vtx.x > maxOut->x)
		{
			maxOut->x = vtx.x;
		}
		if (vtx.y > maxOut->y)
		{
			maxOut->y = vtx.y;
		}
		if (vtx.z > maxOut->z)
		{
			maxOut->z = vtx.z;
		}

		// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		pVtxBuff += sizeFVF;
	}

	// ���_�o�b�t�@�[�̃A�����b�N
	mesh->UnlockVertexBuffer();
}

//=========================================
// �s�p���ۂ�
// Author: Yuda Kaito
// ����1	pos1	�_�̈ʒu
// ����2	pos2	�����̈ʒu
// ����3	pos3	�����̃x�N�g��
// �Ԃ�l	�s�p���A�ۂ�
//=========================================
bool isSharpAngle(D3DXVECTOR3* pos1, D3DXVECTOR3* pos2, D3DXVECTOR3* pos3)
{
	D3DXVECTOR3 vec1 = *pos2 - *pos1;
	D3DXVECTOR3 vec2 = *pos2 - *pos3;
	D3DXVec3Dot(&vec1, &vec2);
	return false;
}

//=========================================
// �_�ƒ����̍ŒZ�������Z�o
// Author: Yuda Kaito
// ����1	posPoint	�_�̈ʒu
// ����2	posLine		�����̈ʒu
// ����3	vecLine		�����̃x�N�g��
// ����3	posDist		�ŒZ�����̈ʒu
// ����3	fLength		�T�C�Y���v�����郂�f��(�֐����ŁA����������)
// �Ԃ�l	�ŒZ�����̒���
//=========================================
float CalculateDistPointLine(D3DXVECTOR3* posPoint, D3DXVECTOR3* posLine, D3DXVECTOR3* vecLine, D3DXVECTOR3* posDist, float* fLength)
{
	float fVecLineLength = D3DXVec3LengthSq(vecLine);
	*fLength = 0.0f;
	if (fVecLineLength > 0.0f)
	{
		D3DXVECTOR3 vec = *posPoint - *posLine;
		*fLength = D3DXVec3Dot(vecLine, &vec);
	}
	D3DXVECTOR3 vec = *posPoint - *posDist;
	return D3DXVec3Length(&vec);
}

//=========================================
// �C�[�W���O�֐�
// Author: hamada ryuuga
//=========================================
float SeteaseIn(float x)
{
	return x * x;
}

//=========================================
// 2D�x�N�g���̊O��
// Author: Yuda Kaito
//=========================================
float Vec2Cross(D3DXVECTOR3* v1, D3DXVECTOR3* v2)
{
	return v1->x * v2->z - v1->z * v2->x;
}

//=========================================
// 2D�x�N�g���̓���
// Author: hamada ryuuga
//=========================================
float Vec2Dot(D3DXVECTOR3* v1, D3DXVECTOR3* v2)
{
	return v1->x * v2->x + v1->z * v2->z;
}