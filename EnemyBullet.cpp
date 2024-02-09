#include "EnemyBullet.h"
#include "model.h"


static DX11_MODEL		g_Model;	// ���f���ǂݍ���
static EnemyBullet		g_Ebullet[100];	// �v���C���[���	
void InitEnemyBullet(void)
{
	LoadModel((char*)"data/MODEL/EnemyBullet.obj", &g_Model);
	for (int i = 0; i < 100; i++)
	{
		// �ʒu�E��]�E�X�P�[���̏����ݒ�
		g_Ebullet[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Ebullet[i].dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Ebullet[i].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_Ebullet[i].use = false;
		g_Ebullet[i].speed = 3;
		g_Ebullet[i].frame = 0;
		//������i][����p�T�C�Y�̏����ݒ�
		g_Ebullet[i].size = D3DXVECTOR3(10.0f, 10.0f, 10.0f);
	}
}

void UninitEnemyBullet(void)
{
	UnloadModel(&g_Model);
}

void UpdateEnemyBullet(void)
{
	for (int i = 0; i < 100; i++)
	{
		if (g_Ebullet[i].use)
		{
			//���ŏ���
			if (g_Ebullet[i].frame > 500.0f)
			{
				g_Ebullet[i].use = false;
				g_Ebullet[i].frame = 0;
			}

			//���W�̍X�V
			g_Ebullet[i].pos += g_Ebullet[i].dir * g_Ebullet[i].speed;
			//���Ԍo��
			g_Ebullet[i].frame += 1.0f;
		}
	}

}

void DrawEnemyBullet(void)
{
	for(int i=0;i<100;i++)
	{
		if(g_Ebullet[i].use)
		{
			D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
			SetLightEnable(true);
			// ���[���h�}�g���b�N�X�̏������i�P�ʍs������֐��j
			D3DXMatrixIdentity(&g_Ebullet[i].mtxWorld);

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScl, g_Ebullet[i].scl.x, g_Ebullet[i].scl.y, g_Ebullet[i].scl.z);
			D3DXMatrixMultiply(&g_Ebullet[i].mtxWorld, &g_Ebullet[i].mtxWorld, &mtxScl);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Ebullet[i].rot.y, g_Ebullet[i].rot.x, g_Ebullet[i].rot.z);
			D3DXMatrixMultiply(&g_Ebullet[i].mtxWorld, &g_Ebullet[i].mtxWorld, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, g_Ebullet[i].pos.x, g_Ebullet[i].pos.y, g_Ebullet[i].pos.z);
			D3DXMatrixMultiply(&g_Ebullet[i].mtxWorld, &g_Ebullet[i].mtxWorld, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			SetWorldMatrix(&g_Ebullet[i].mtxWorld);

			//�J�����O�Ȃ�(�~�N���񃂃f���̔��̑Ή�)
			SetCullingMode(CULL_MODE_NONE);

			//obj���f���̕`��
			DrawModel(&g_Model);

			//�J�����O�����ɖ߂�
			SetCullingMode(CULL_MODE_BACK);
		}
	}

}

EnemyBullet* GetEnemyBullet(void)
{
	return g_Ebullet;
}

void SetEnemyBullet(D3DXVECTOR3 _pos, D3DXVECTOR3 _dir)
{
	for (int i = 0; i < 100; i++)
	{
		if (g_Ebullet[i].use == false)
		{
			g_Ebullet[i].pos = _pos;
			g_Ebullet[i].dir = _dir;
			g_Ebullet[i].use = true;
			break;
		}
	}
}
