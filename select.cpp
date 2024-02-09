//=============================================================================
//
// �|���S���\������ [Select.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "Select.h"
#include "texture.h"
#include "polyline.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static DX11_MODEL	g_Model;	// ���f���ǂݍ���
static Select		g_Select;	// �v���C���[���		
static LIGHT		g_DirectionalLight;	// �f�B���N�V���i�����C�g
static LIGHT		g_PointLight;		// �|�C���g���C�g

//=============================================================================
// ����������
//=============================================================================
HRESULT InitSelect(void)
{
	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	g_Select.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Select.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Select.scl = D3DXVECTOR3(5.0f, 5.0f, 5.0f);
	g_Select.use = false;

	//�����蔻��p�T�C�Y�̏����ݒ�
	g_Select.size = D3DXVECTOR3(10.0f, 10.0f, 10.0f);

	//obj���f���̓ǂݍ���
	LoadModel((char*)"data/MODEL/Select.obj", &g_Model);
	g_Model.SubsetArray->Material.Material.Diffuse = { 0.0,1.0,0.0,0.5 };
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitSelect(void)
{
	//obj���f���̉��
	UnloadModel(&g_Model);
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateSelect(void)
{
	
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawSelect(void)
{
	if(g_Select.use==true)
	{
		D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
		SetLightEnable(false);
		SetCullingMode(CULL_MODE_NONE);
		// ���[���h�}�g���b�N�X�̏������i�P�ʍs������֐��j
		D3DXMatrixIdentity(&g_Select.mtxWorld);

		// �X�P�[���𔽉f
		D3DXMatrixScaling(&mtxScl, g_Select.scl.x, g_Select.scl.y, g_Select.scl.z);
		D3DXMatrixMultiply(&g_Select.mtxWorld, &g_Select.mtxWorld, &mtxScl);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Select.rot.y, g_Select.rot.x, g_Select.rot.z);
		D3DXMatrixMultiply(&g_Select.mtxWorld, &g_Select.mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, g_Select.pos.x, g_Select.pos.y, g_Select.pos.z);
		D3DXMatrixMultiply(&g_Select.mtxWorld, &g_Select.mtxWorld, &mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		SetWorldMatrix(&g_Select.mtxWorld);

		//obj���f���̕`��
		DrawModel(&g_Model);

		//�J�����O�����ɖ߂�
		SetCullingMode(CULL_MODE_BACK);
	}
}


//=============================================================================
// �v���C���[�����擾
//=============================================================================
Select *GetSelect(void)
{
	return &g_Select;
}

DX11_MODEL* GetSelectModel()
{
	return &g_Model;
}

