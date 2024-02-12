//=============================================================================
//
// �e���� [shadow.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "render.h"
#include "shadow.h"
#include "texture.h"
#include "DirectXAPI.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	SHADOW_SIZE_X		(1.0f)			// ���_�T�C�Y
#define	SHADOW_SIZE_Z		(1.0f)			// ���_�T�C�Y

#define	MAX_SHADOW			(1024)			// �e�ő吔

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXMATRIX	mtxWorld;	// ���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;		// ��]
	D3DXVECTOR3 scl;		// �X�P�[��
	MATERIAL	material;	// �}�e���A��
	bool		use;		// �g�p���Ă��邩�ǂ���

} SHADOW;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer		*g_VertexBuffer = NULL;	// ���_���

static SHADOW			g_Shadow[MAX_SHADOW];	// �e���[�N
static int				g_TexNo;				// �e�N�X�`�����ʎq

//=============================================================================
// ����������
//=============================================================================
void InitShadow(void)
{
	//// ���_�o�b�t�@����
	//D3D11_BUFFER_DESC bd;
	//ZeroMemory(&bd, sizeof(bd));
	//bd.Usage = D3D11_USAGE_DYNAMIC;
	//bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	//bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	//GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);

	//{//���_�o�b�t�@�̒��g�𖄂߂�
	//	D3D11_MAPPED_SUBRESOURCE msr;
	//	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	//	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	//	// ���_���W�̐ݒ�
	//	vertex[0].Position = D3DXVECTOR3(-SHADOW_SIZE_X / 2, 0.0f, SHADOW_SIZE_Z / 2);
	//	vertex[1].Position = D3DXVECTOR3(SHADOW_SIZE_X / 2, 0.0f, SHADOW_SIZE_Z / 2);
	//	vertex[2].Position = D3DXVECTOR3(-SHADOW_SIZE_X / 2, 0.0f, -SHADOW_SIZE_Z / 2);
	//	vertex[3].Position = D3DXVECTOR3(SHADOW_SIZE_X / 2, 0.0f, -SHADOW_SIZE_Z / 2);

	//	// �@���̐ݒ�
	//	vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//	vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//	vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//	vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//	// ���_�J���[�̐ݒ�
	//	vertex[0].Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
	//	vertex[1].Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
	//	vertex[2].Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
	//	vertex[3].Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);

	//	// �e�N�X�`�����W�̐ݒ�
	//	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
	//	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);
	//	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);
	//	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	//	GetDeviceContext()->Unmap(g_VertexBuffer, 0);
	//}

	//// �e�N�X�`������
	//g_TexNo = LoadTexture((char*)"data/TEXTURE/shadow000.jpg");

	//// �e���[�N������
	//for(int i = 0; i < MAX_SHADOW; i++)
	//{
	//	ZeroMemory(&g_Shadow[i].material, sizeof(g_Shadow[i].material));
	//	g_Shadow[i].material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//	g_Shadow[i].pos = D3DXVECTOR3(0.0f, 0.1f, 0.0f);
	//	g_Shadow[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//	g_Shadow[i].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	//	g_Shadow[i].use = false;
	//}
}

//=============================================================================
// �I������
//=============================================================================
void UninitShadow(void)
{
	// ���_�o�b�t�@�̉��
	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateShadow(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawShadow(void)
{
	// ���Z����
	//SetBlendState(BLEND_MODE_SUBTRACT);

	//// Z��r�Ȃ�
	//SetDepthEnable(false);

	//// ���_�o�b�t�@�ݒ�
	//UINT stride = sizeof(VERTEX_3D);
	//UINT offset = 0;
	//GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	//// �v���~�e�B�u�g�|���W�ݒ�
	//GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//// �e�N�X�`���ݒ�
	//GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_TexNo));

	//D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	//for(int i = 0; i < MAX_SHADOW; i++)
	//{
	//	if(g_Shadow[i].use)
	//	{
	//		// ���[���h�}�g���b�N�X�̏�����
	//		D3DXMatrixIdentity(&g_Shadow[i].mtxWorld);

	//		// �X�P�[���𔽉f
	//		D3DXMatrixScaling(&mtxScl, g_Shadow[i].scl.x, g_Shadow[i].scl.y, g_Shadow[i].scl.z);
	//		D3DXMatrixMultiply(&g_Shadow[i].mtxWorld, &g_Shadow[i].mtxWorld, &mtxScl);

	//		// ��]�𔽉f
	//		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Shadow[i].rot.y, g_Shadow[i].rot.x, g_Shadow[i].rot.z);
	//		D3DXMatrixMultiply(&g_Shadow[i].mtxWorld, &g_Shadow[i].mtxWorld, &mtxRot);

	//		// �ړ��𔽉f
	//		D3DXMatrixTranslation(&mtxTranslate, g_Shadow[i].pos.x, g_Shadow[i].pos.y, g_Shadow[i].pos.z);
	//		D3DXMatrixMultiply(&g_Shadow[i].mtxWorld, &g_Shadow[i].mtxWorld, &mtxTranslate);

	//		// ���[���h�}�g���b�N�X�̐ݒ�
	//		SetWorldMatrix(&g_Shadow[i].mtxWorld);

	//		// �}�e���A���̐ݒ�
	//		SetMaterial(g_Shadow[i].material);

	//		// �|���S���̕`��
	//		GetDeviceContext()->Draw(4, 0);
	//	}
	//}

	//// �ʏ�u�����h
	//SetBlendState(BLEND_MODE_ALPHABLEND);
	//
	//// Z��r����
	//SetDepthEnable(true);
}

//=============================================================================
// �e�̍쐬
//=============================================================================
int SetShadow(D3DXVECTOR3 pos, float size)
{
	int index = -1;

	for(int i = 0; i < MAX_SHADOW; i++)
	{
		// ���g�p�ifalse�j�������炻����g��
		if(!g_Shadow[i].use)
		{
			g_Shadow[i].pos = pos;
			g_Shadow[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Shadow[i].scl = D3DXVECTOR3(size, 1.0f, size);
			g_Shadow[i].material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_Shadow[i].use = true;

			index = i;	// ���ꂪIndex�ԍ�
			break;
		}
	}

	return index;	// Index�ԍ���Ԃ��Ă���
}

//=============================================================================
// �}�e���A���J���[�̐ݒ�
//=============================================================================
void SetColorShadow(int index, D3DXCOLOR col)
{
	if (index >= 0 && index < MAX_SHADOW)
	{
		g_Shadow[index].material.Diffuse = col;
	}
}

//=============================================================================
// �e�̔j��
//=============================================================================
void ReleaseShadow(int index)
{
	if(index >= 0 && index < MAX_SHADOW)
	{
		g_Shadow[index].use = false;
	}
}

//=============================================================================
// �ʒu�̐ݒ�
//=============================================================================
void SetPositionShadow(int index, D3DXVECTOR3 pos)
{
	if (index >= 0 && index < MAX_SHADOW)
	{
		g_Shadow[index].pos = pos;
	}
}
