//=============================================================================
//
// �|�����C������ [polyline.cpp]
// Author : 
//
//=============================================================================
#include "polyline.h"
#include "texture.h"
#include "camera.h"
#include "DirectXAPI.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_POLYLINE	(512)	// �|�����C���ő吔


//*****************************************************************************
// �\���̒�`
//*****************************************************************************
struct POLYLINE
{
	D3DXMATRIX	mtxWorld;	// ���[���h�}�g���b�N�X

	D3DXVECTOR3 begin;		// �|�����C���n�_
	D3DXVECTOR3 end;		// �|�����C���I�_
	float		width;		// �|�����C���̕�
	MATERIAL	material;	// �}�e���A��

	bool		use;		// �g�p���Ă��邩�ǂ���
};


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer*	g_VertexBuffer;				// ���_�o�b�t�@
static POLYLINE			g_Polyline[MAX_POLYLINE];	// �|�����C���z��
static int				g_TexNo;					// �e�N�X�`�����ʎq


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
static void CalcVertexBuffer(int idx);


//=============================================================================
// ����������
//=============================================================================
void InitPolyLine()
{
	//ID3D11Device* pDevice = GetDevice();

	//// ���_�o�b�t�@����
	//D3D11_BUFFER_DESC bd;
	//ZeroMemory(&bd, sizeof(bd));
	//bd.Usage = D3D11_USAGE_DYNAMIC;
	//bd.ByteWidth = sizeof(VERTEX_3D) * 6;//���_��6�ŌŒ�
	//bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	//GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);

	//// �e�N�X�`���ǂݍ���
	//g_TexNo = LoadTexture((char*)"data/TEXTURE/polyline000.png");

	//// �|�����C���z�񏉊���
	//for (int i = 0; i < MAX_POLYLINE; i++)
	//{
	//	D3DXMatrixIdentity(&g_Polyline[i].mtxWorld);

	//	g_Polyline[i].begin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//	g_Polyline[i].end = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//	g_Polyline[i].width = 1.0f;

	//	g_Polyline[i].use = false;

	//	// �}�e���A���̏����ݒ�
	//	ZeroMemory(&g_Polyline[i].material, sizeof(MATERIAL));
	//	g_Polyline[i].material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//	g_Polyline[i].material.Polyline = 1;

	//}
}

//=============================================================================
// �I������
//=============================================================================
void UninitPolyLine()
{
	//���_�o�b�t�@�̉��
	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePolyLine(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPolyLine(void)
{
	//�J�����O�Ȃ�
	//SetCullingMode(CULL_MODE_NONE);

	////���Z����
	//SetBlendState(BLEND_MODE_ADD);

	//// Z��r�Ȃ�
	//SetDepthEnable(false);

	////���C�e�B���O����
	//SetLightEnable(false);

	//// ���_�o�b�t�@�ݒ�
	//UINT stride = sizeof(VERTEX_3D);
	//UINT offset = 0;
	//GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	//// �v���~�e�B�u�g�|���W�ݒ�
	//GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//// �e�N�X�`���ݒ�
	//GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_TexNo));

	//for (int i = 0; i < MAX_POLYLINE; i++)
	//{
	//	// �g�p���̂��̂������s����
	//	if (g_Polyline[i].use != true)
	//		continue;

	//	// ���_�o�b�t�@�X�V
	//	CalcVertexBuffer(i);

	//	// �}�e���A���ݒ�
	//	SetMaterial(g_Polyline[i].material);

	//	// ���[���h�}�g���b�N�X�̏�����
	//	D3DXMatrixIdentity(&g_Polyline[i].mtxWorld);

	//	// ���[���h�}�g���b�N�X�̐ݒ�
	//	SetWorldMatrix(&g_Polyline[i].mtxWorld);

	//	// �|���S���̕`��
	//	GetDeviceContext()->Draw(6, 0);
	//}

	////�e�ݒ�����ɖ߂�
	//SetCullingMode(CULL_MODE_BACK);
	//SetDepthEnable(true);
	//SetLightEnable(true);
	//SetBlendState(BLEND_MODE_ALPHABLEND);
}

//=============================================================================
// �|�����C���̍쐬
//=============================================================================
int SetPolyLine(D3DXVECTOR3 begin, D3DXVECTOR3 end, float width)
{
	int index = -1;

	for (int i = 0; i < MAX_POLYLINE; i++)
	{
		// use�t���O�����g�p�ifalse�j�������炻����g��
		if (g_Polyline[i].use == false)
		{
			g_Polyline[i].begin = begin;
			g_Polyline[i].end = end;
			g_Polyline[i].width = width;

			g_Polyline[i].material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_Polyline[i].use = true;

			index = i;	// ����g�p���ꂽIndex�ԍ�
			break;
		}
	}

	return index;	// Index�ԍ���Ԃ��i-1�Ȃ�o�^���s�ƂȂ�j
}

//=============================================================================
// �}�e���A���J���[�̐ݒ�
//=============================================================================
void SetColorPolyLine(int index, D3DXCOLOR col)
{
	if (index >= 0 && index < MAX_POLYLINE)
	{
		g_Polyline[index].material.Diffuse = col;
	}
}

//=============================================================================
// ���W�̍Đݒ�
//=============================================================================
void SetPositionPolyLine(int index, D3DXVECTOR3 begin, D3DXVECTOR3 end)
{
	if (index >= 0 && index < MAX_POLYLINE)
	{
		g_Polyline[index].begin = begin;
		g_Polyline[index].end = end;
	}
}

//=============================================================================
// �|�����C���j��
//=============================================================================
void ReleasePolyLine(int index)
{
	if (index >= 0 && index < MAX_POLYLINE)
	{
		g_Polyline[index].use = false;
	}
}

//=============================================================================
// ���_�o�b�t�@�X�V
//=============================================================================
void CalcVertexBuffer(int idx)
{
	//VERTEX_3D vertex[6];

	////�n�_�̒��_�f�[�^���쐬����
	//{
	//	//�n�_����J�����ւ̃x�N�g�������߂�
	//	D3DXVECTOR3 eye = GetCamera()->pos - g_Polyline[idx].begin;

	//	//�n�_����I�_�ւ̃x�N�g�������߂�
	//	D3DXVECTOR3 line = g_Polyline[idx].end - g_Polyline[idx].begin;

	//	//��L2�̃x�N�g������n�_�ƂȂ钸�_�f�[�^���쐬����
	//	//�@�^�E    �E
	//	//�Z  |  �^ | �^�E
	//	//    �E    �E
	//	D3DXVECTOR3 cross;
	//	D3DXVec3Cross(&cross, &line, &eye);
	//	D3DXVec3Cross(&cross, &eye, &cross);
	//	D3DXVec3Normalize(&cross, &cross);

	//	vertex[0].Position.x = g_Polyline[idx].begin.x - cross.x * g_Polyline[idx].width;
	//	vertex[0].Position.y = g_Polyline[idx].begin.y - cross.y * g_Polyline[idx].width;
	//	vertex[0].Position.z = g_Polyline[idx].begin.z - cross.z * g_Polyline[idx].width;
	//	vertex[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//	vertex[0].TexCoord.x = 0.0f;
	//	vertex[0].TexCoord.y = 0.0f;
	//	vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//}

	//// �n�_���㉺�ƏI�_���㉺�̒��_�f�[�^���쐬����
	//{
	//	//�n�_����J�����ւ̃x�N�g�������߂�
	//	D3DXVECTOR3 eye = GetCamera()->pos - g_Polyline[idx].begin;

	//	//�n�_����I�_�ւ̃x�N�g�������߂�
	//	D3DXVECTOR3 line = g_Polyline[idx].end - g_Polyline[idx].begin;

	//	// ���_�x�N�g�����璼�������P�ʃx�N�g�����쐬����
	//	D3DXVECTOR3 cross;
	//	D3DXVec3Cross(&cross, &line, &eye);
	//	D3DXVec3Normalize(&cross, &cross);

	//	// �n�_���㉺�̒��_�f�[�^�쐬
	//	//�@�^�Z    �E
	//	//�E  |  �^ | �^�E
	//	//    �Z    �E
	//	vertex[1].Position.x = g_Polyline[idx].begin.x + cross.x * g_Polyline[idx].width;
	//	vertex[1].Position.y = g_Polyline[idx].begin.y + cross.y * g_Polyline[idx].width;
	//	vertex[1].Position.z = g_Polyline[idx].begin.z + cross.z * g_Polyline[idx].width;
	//	vertex[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//	vertex[1].TexCoord.x = 0.5f;
	//	vertex[1].TexCoord.y = 0.0f;
	//	vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//	vertex[2].Position.x = g_Polyline[idx].begin.x - cross.x * g_Polyline[idx].width;
	//	vertex[2].Position.y = g_Polyline[idx].begin.y - cross.y * g_Polyline[idx].width;
	//	vertex[2].Position.z = g_Polyline[idx].begin.z - cross.z * g_Polyline[idx].width;
	//	vertex[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//	vertex[2].TexCoord.x = 0.0f;
	//	vertex[2].TexCoord.y = 0.5f;
	//	vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//	// �I�_���㉺�̒��_�f�[�^�쐬
	//	//�@�^�E    �Z
	//	//�E  |  �^ | �^�E
	//	//    �E    �Z
	//	vertex[3].Position.x = g_Polyline[idx].end.x + cross.x * g_Polyline[idx].width;
	//	vertex[3].Position.y = g_Polyline[idx].end.y + cross.y * g_Polyline[idx].width;
	//	vertex[3].Position.z = g_Polyline[idx].end.z + cross.z * g_Polyline[idx].width;
	//	vertex[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//	vertex[3].TexCoord.x = 1.0f;
	//	vertex[3].TexCoord.y = 0.5f;
	//	vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//	vertex[4].Position.x = g_Polyline[idx].end.x - cross.x * g_Polyline[idx].width;
	//	vertex[4].Position.y = g_Polyline[idx].end.y - cross.y * g_Polyline[idx].width;
	//	vertex[4].Position.z = g_Polyline[idx].end.z - cross.z * g_Polyline[idx].width;
	//	vertex[4].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//	vertex[4].TexCoord.x = 0.5f;
	//	vertex[4].TexCoord.y = 1.0f;
	//	vertex[4].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//}

	////�I�_�̒��_�f�[�^���쐬����
	//{
	//	//�I�_����J�����ւ̃x�N�g�������߂�
	//	D3DXVECTOR3 eye = GetCamera()->pos - g_Polyline[idx].end;

	//	//�n�_����I�_�ւ̃x�N�g�������߂�
	//	D3DXVECTOR3 line = g_Polyline[idx].end - g_Polyline[idx].begin;

	//	//��L2�̃x�N�g������I�_�ƂȂ钸�_�f�[�^���쐬����
	//	//�@�^�E    �E
	//	//�E  |  �^ | �^�Z
	//	//    �E    �E
	//	D3DXVECTOR3 cross;
	//	D3DXVec3Cross(&cross, &line, &eye);
	//	D3DXVec3Cross(&cross, &eye, &cross);
	//	D3DXVec3Normalize(&cross, &cross);

	//	vertex[5].Position.x = g_Polyline[idx].end.x + cross.x * g_Polyline[idx].width;
	//	vertex[5].Position.y = g_Polyline[idx].end.y + cross.y * g_Polyline[idx].width;
	//	vertex[5].Position.z = g_Polyline[idx].end.z + cross.z * g_Polyline[idx].width;
	//	vertex[5].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//	vertex[5].TexCoord.x = 1.0f;
	//	vertex[5].TexCoord.y = 1.0f;
	//	vertex[5].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//}

	//// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	//D3D11_MAPPED_SUBRESOURCE msr;
	//HRESULT hr = GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	//if (SUCCEEDED(hr)) {
	//	// ���_�f�[�^���㏑��
	//	rsize_t len = sizeof(VERTEX_3D) * 6;
	//	memcpy_s(msr.pData, len, vertex, len);
	//	// ���_�f�[�^���A�����b�N����
	//	GetDeviceContext()->Unmap(g_VertexBuffer, 0);
	//}
}

