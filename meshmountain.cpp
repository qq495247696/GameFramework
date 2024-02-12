//=============================================================================
//
// ���b�V���R���� [meshmountain.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#include "meshmountain.h"
#include "Texture.h"
#include "input.h"
#include "camera.h"
#include "DirectXAPI.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
struct MOUNTAIN_MESH
{
	ID3D11Buffer	*vertexBuffer;	// ���_�o�b�t�@
	ID3D11Buffer	*indexBuffer;	// �C���f�b�N�X�o�b�t�@
	int				numVertex;		//���_��
	int				numIndex;		//�C���f�b�N�X��

	D3DXMATRIX		mtxWorld;
	D3DXVECTOR3		pos;
	D3DXVECTOR3		rot;

	MATERIAL		material;
};

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static MOUNTAIN_MESH	g_Mountain;				// ���b�V�����
static int				g_TexNo;				// �e�N�X�`�����ʎq

int g_nNumBlockH, g_nNumBlockV;					// �u���b�N��
int g_nNumVertexMountain;						// �����_��	
int g_nNumVertexIndexMountain;					// ���C���f�b�N�X��
int g_nNumPolygonMountain;						// ���|���S����
float g_fSizeBlockH, g_fSizeBlockV;				// �u���b�N�T�C�Y

//=============================================================================
// ����������
//=============================================================================
void InitMeshMountain(D3DXVECTOR3 pos, D3DXVECTOR3 rot,
	int numBlockH, int numBlockV, float sizeBlockH, float sizeBlockV,
	float texSizeX, float texSizeZ)
{
	/*ID3D11Device* pDevice = GetDevice();*/

	// �|���S���\���ʒu�̒��S���W��ݒ�
	//g_Mountain.pos = pos;
	//g_Mountain.rot = rot;

	//// �e�N�X�`���̓ǂݍ���
	//g_TexNo = LoadTexture((char*)"data/TEXTURE/mountain001.png");

	////�}�e���A���̏�����
	//ZeroMemory(&g_Mountain.material, sizeof(g_Mountain.material));
	//g_Mountain.material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//// ���_���̐ݒ�
	//g_Mountain.numVertex = (numBlockH + 1) * (numBlockV + 1);

	//// �C���f�b�N�X���̐ݒ�
	//g_Mountain.numIndex = (numBlockH + 1) * (numBlockV * 2) + (numBlockV - 1);

	//// �ꎞ���_�z��𐶐�
	//VERTEX_3D* pVertexWk = new VERTEX_3D[g_Mountain.numVertex];

	//// �ꎞ�C���f�b�N�X�z��𐶐�
	//int* pIndexWk = new int[g_Mountain.numIndex];

	//// ���_�z��̒��g�𖄂߂�
	//VERTEX_3D* pVtx = pVertexWk;
	//const float ANGLE_H = (D3DX_PI * 2) / numBlockH;

	//for (int vt = 0; vt < (numBlockV + 1); vt++) {
	//	for (int hr = 0; hr < (numBlockH + 1); hr++) {
	//		// ���_���W�̐ݒ�
	//		pVtx->Position.x = sinf(ANGLE_H * hr) * sizeBlockH;
	//		pVtx->Position.y = vt * sizeBlockV;
	//		pVtx->Position.z = cosf(ANGLE_H * hr) * sizeBlockH;

	//		// �@���̐ݒ�
	//		pVtx->Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//		// ���ˌ��̐ݒ�
	//		pVtx->Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//		// �e�N�X�`�����W�̐ݒ�
	//		pVtx->TexCoord.x = hr * texSizeX;
	//		pVtx->TexCoord.y = 0.975f - vt * 0.95f * texSizeZ;

	//		pVtx++;
	//	}
	//}

	//// �C���f�b�N�X�z��̒��g�𖄂߂�
	//int* pIdx = pIndexWk;

	//for (int vt = 0; vt < numBlockV; vt++) {
	//	for (int hr = 0; hr < (numBlockH + 1); hr++) {
	//		*pIdx = vt * (numBlockH + 1) + hr;
	//		pIdx++;

	//		*pIdx = (vt + 1) * (numBlockH + 1) + hr;
	//		pIdx++;
	//	}
	//}

	//// ���_�o�b�t�@����
	//D3D11_BUFFER_DESC bd;
	//ZeroMemory(&bd, sizeof(bd));
	//bd.Usage = D3D11_USAGE_DEFAULT;
	//bd.ByteWidth = sizeof(VERTEX_3D) * g_Mountain.numVertex;
	//bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//bd.CPUAccessFlags = 0;

	//D3D11_SUBRESOURCE_DATA sd;
	//ZeroMemory(&sd, sizeof(sd));
	//sd.pSysMem = pVertexWk;

	///*GetDevice()->CreateBuffer(&bd, &sd, &g_Mountain.vertexBuffer);*/


	//// �C���f�b�N�X�o�b�t�@����
	//ZeroMemory(&bd, sizeof(bd));
	//bd.Usage = D3D11_USAGE_DEFAULT;
	//bd.ByteWidth = sizeof(int) * g_Mountain.numIndex;
	//bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	//bd.CPUAccessFlags = 0;

	//ZeroMemory(&sd, sizeof(sd));
	//sd.pSysMem = pIndexWk;

	///*GetDevice()->CreateBuffer(&bd, &sd, &g_Mountain.indexBuffer);*/


	//// �ꎞ�z��̉��
	//delete[] pIndexWk;
	//delete[] pVertexWk;
}

//=============================================================================
// �I������
//=============================================================================
void UninitMeshMountain(void)
{
	//�C���f�b�N�X�o�b�t�@�̉��
	if (g_Mountain.indexBuffer != NULL)
	{
		g_Mountain.indexBuffer->Release();
		g_Mountain.indexBuffer = NULL;
	}

	//���_�o�b�t�@�̉��
	if (g_Mountain.vertexBuffer != NULL)
	{
		g_Mountain.vertexBuffer->Release();
		g_Mountain.vertexBuffer = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMeshMountain(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMeshMountain(void)
{
	// ���_�o�b�t�@�ݒ�
	//UINT stride = sizeof(VERTEX_3D);
	//UINT offset = 0;
	//GetDeviceContext()->IASetVertexBuffers(0, 1, &g_Mountain.vertexBuffer, &stride, &offset);

	//// �C���f�b�N�X�o�b�t�@�ݒ�
	//GetDeviceContext()->IASetIndexBuffer(g_Mountain.indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	//// �v���~�e�B�u�g�|���W�ݒ�
	//GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//// �}�e���A���ݒ�
	//SetMaterial(g_Mountain.material);

	//// �e�N�X�`���ݒ�
	//GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_TexNo));


	//D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	//// ���[���h�}�g���b�N�X�̏�����
	//D3DXMatrixIdentity(&g_Mountain.mtxWorld);

	//// ��]�𔽉f
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Mountain.rot.y, g_Mountain.rot.x, g_Mountain.rot.z);
	//D3DXMatrixMultiply(&g_Mountain.mtxWorld, &g_Mountain.mtxWorld, &mtxRot);

	//// �ړ��𔽉f
	//D3DXMatrixTranslation(&mtxTranslate, g_Mountain.pos.x, g_Mountain.pos.y, g_Mountain.pos.z);
	//D3DXMatrixMultiply(&g_Mountain.mtxWorld, &g_Mountain.mtxWorld, &mtxTranslate);

	//// ���[���h�}�g���b�N�X�̐ݒ�
	//SetWorldMatrix(&g_Mountain.mtxWorld);

	//// �|���S���̕`��
	//GetDeviceContext()->DrawIndexed(g_Mountain.numIndex, 0, 0);
}
