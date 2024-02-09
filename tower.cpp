//=============================================================================
//
// �|���S���\������ [Tower.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "Tower.h"
#include "texture.h"
#include "Enemybullet.h"
#include "shadow.h"
#include "polyline.h"
#include "sound.h"
#include "BattlePhase.h"
#include "PreparationPhase.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static Tower		g_Tower[100];	// �v���C���[���		
static LIGHT		g_DirectionalLight;	// �f�B���N�V���i�����C�g
static LIGHT		g_PointLight;		// �|�C���g���C�g
static int			g_AxisLine[3]; //�|�����C���p���ʎq
static int			g_time;
static DX11_MODEL  g_ModelData[3];
//=============================================================================
// ����������
//=============================================================================
HRESULT InitTower(void)
{

	LoadModel((char*)"data/MODEL/Tower.obj", &g_ModelData[0]);
	LoadModel((char*)"data/MODEL/Tower2.obj", &g_ModelData[1]);
	LoadModel((char*)"data/MODEL/Tower3.obj", &g_ModelData[2]);
	for (int i = 0; i < 100; i++)
	{
		// �ʒu�E��]�E�X�P�[���̏����ݒ�
		g_Tower[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Tower[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Tower[i].scl = D3DXVECTOR3(5.0f, 5.0f, 5.0f);
		g_Tower[i].use = false;
		g_Tower[i].time = 0;
		//������i][����p�T�C�Y�̏����ݒ�
		g_Tower[i].size = D3DXVECTOR3(100.0f, 100.0f, 100.0f); 
		g_Tower[i].model = &g_ModelData[0];
		//g_Tower[i].shadow = SetShadow(D3DXVECTOR3(g_Tower[i].pos.x, 0.0f, g_Tower[i].pos.z), 80.0f);
	}
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTower(void)
{
	//obj���f���̉��
	UnloadModel(&g_ModelData[0]);
	UnloadModel(&g_ModelData[1]);
	UnloadModel(&g_ModelData[2]);
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTower(void)
{
	D3DXVECTOR3 x = { 0.0,0.0,1.0 };


	for (int i = 0; i < 100; i++)
	{
		if (g_Tower[i].use == true)
		{
			g_Tower[i].time++;
			if (g_Tower[i].time>80)
			{
			D3DXVECTOR4 pOut;
			D3DXMATRIX rot;
			D3DXMatrixIdentity(&rot);
			D3DXMatrixRotationY(&rot, g_Tower[i].rot.y);
			D3DXVec3Transform(&pOut, &x, &rot);
			SetEnemyBullet(g_Tower[i].pos, { pOut.x,0,pOut.z});
			g_Tower[i].time = 0;
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTower(void)
{
	for(int i=0;i<100;i++)
	{
		if (g_Tower[i].use == true)
		{
			D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
			SetLightEnable(true);
			// ���[���h�}�g���b�N�X�̏������i�P�ʍs������֐��j
			D3DXMatrixIdentity(&g_Tower[i].mtxWorld);

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScl, g_Tower[i].scl.x, g_Tower[i].scl.y, g_Tower[i].scl.z);
			D3DXMatrixMultiply(&g_Tower[i].mtxWorld, &g_Tower[i].mtxWorld, &mtxScl);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Tower[i].rot.y, g_Tower[i].rot.x, g_Tower[i].rot.z);
			D3DXMatrixMultiply(&g_Tower[i].mtxWorld, &g_Tower[i].mtxWorld, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, g_Tower[i].pos.x, g_Tower[i].pos.y, g_Tower[i].pos.z);
			D3DXMatrixMultiply(&g_Tower[i].mtxWorld, &g_Tower[i].mtxWorld, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			SetWorldMatrix(&g_Tower[i].mtxWorld);

			//�J�����O�Ȃ�(�~�N���񃂃f���̔��̑Ή�)
			SetCullingMode(CULL_MODE_NONE);

			//obj���f���̕`��
			DrawModel(g_Tower[i].model);

			//�J�����O�����ɖ߂�
			SetCullingMode(CULL_MODE_BACK);
		}
	}
}


//=============================================================================
// �v���C���[�����擾
//=============================================================================
Tower *GetTower(void)
{
	return &g_Tower[0];
}

void SetTower(D3DXVECTOR3 _pos, D3DXVECTOR3 _rot, TowerType type)
{
	for (int i = 0; i < 100; i++)
	{
		if (g_Tower[i].use == false)
		{
			g_Tower[i].pos = _pos;
			g_Tower[i].rot = _rot;
			g_Tower[i].time = 0;
			g_Tower[i].use = true;

			switch (type)
			{
			case Normal:
				g_Tower[i].model = &g_ModelData[0];
				break;
			case Fire:
				g_Tower[i].model = &g_ModelData[1];
				break;
			case Light:
				g_Tower[i].model = &g_ModelData[2];
				break;
			default:
				break;
			}
			break;
		}
	}
}

