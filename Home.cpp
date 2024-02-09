#include "Home.h"
#include "main.h"
#include "input.h"
#include "camera.h"
#include "player.h"
#include "texture.h"
#include "model.h"
#include "bullet.h"
#include "shadow.h"
#include "polyline.h"
#include "scene.h"
#include "sound.h"


static DX11_MODEL	g_Model;	// ���f���ǂݍ���
static Home			g_Home;	// �v���C���[���		
static float        g_Rot;		// �L�����N�^�[�̌���
static LIGHT		g_DirectionalLight;	// �f�B���N�V���i�����C�g
static LIGHT		g_PointLight;		// �|�C���g���C�g

static int			g_AxisLine[5]; //�|�����C���p���ʎq

HRESULT InitHome(void)
{
	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	g_Home.pos = D3DXVECTOR3(0.0f, 0.0f, -1200.0f);
	g_Home.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Home.scl = D3DXVECTOR3(20.0f, 20.0f, 20.0f);
	g_Home.use = true;
	g_Home.hitedSound = LoadSound((char*)"data/SE/defend001.wav");
	g_Home.hp = 5;

	//�����蔻��p�T�C�Y�̏����ݒ�
	g_Home.size = D3DXVECTOR3(120.0f, 210.0f, 120.0f);

	//obj���f���̓ǂݍ���
	LoadModel((char*)"data/MODEL/home.obj", &g_Model);
	// �e�̃Z�b�g�i�e�͍�����0�ɂ��ĕ\��������j


	// �|�����C���̃Z�b�g
	g_AxisLine[0] = SetPolyLine(D3DXVECTOR3(-150.0f, 300.0f, -900.0f), D3DXVECTOR3(150.0f, 300.0f, -900.0f), 30.0f);
	SetColorPolyLine(g_AxisLine[0], D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.8f));
	return S_OK;
}

void UninitHome(void)
{
	UnloadModel(&g_Model);
}

void UpdateHome(void)
{
	SetPositionPolyLine(0, { -150.0f, 500.0f, -900.0f }, { -150.0f + (300 / 5) * g_Home.hp, 500.0f, -900.0f });
	if (g_Home.hp <= 0)
	{
		SetScene(SCENE_RESULT);
		StopSoundAll();
	}
}

void DrawHome(void)
{
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	SetLightEnable(true);
	SetCullingMode(CULL_MODE_NONE);
	SetDepthEnable(true);
	// ���[���h�}�g���b�N�X�̏������i�P�ʍs������֐��j
	D3DXMatrixIdentity(&g_Home.mtxWorld);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, g_Home.scl.x, g_Home.scl.y, g_Home.scl.z);
	D3DXMatrixMultiply(&g_Home.mtxWorld, &g_Home.mtxWorld, &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Home.rot.y, g_Home.rot.x, g_Home.rot.z);
	D3DXMatrixMultiply(&g_Home.mtxWorld, &g_Home.mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, g_Home.pos.x, g_Home.pos.y, g_Home.pos.z);
	D3DXMatrixMultiply(&g_Home.mtxWorld, &g_Home.mtxWorld, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(&g_Home.mtxWorld);

	DirectX::XMMATRIX inverse= DirectX::XMMatrixSet(g_Home.mtxWorld._11, g_Home.mtxWorld._12, g_Home.mtxWorld._13, g_Home.mtxWorld._14, g_Home.mtxWorld._21, g_Home.mtxWorld._22, g_Home.mtxWorld._23, g_Home.mtxWorld._24, g_Home.mtxWorld._31, g_Home.mtxWorld._32, g_Home.mtxWorld._33, g_Home.mtxWorld._34, g_Home.mtxWorld._41, g_Home.mtxWorld._42, g_Home.mtxWorld._43, g_Home.mtxWorld._44);
	SetInverseMatrix(inverse);
	//obj���f���̕`��
	DrawModel(&g_Model);

	//�J�����O�����ɖ߂�
	SetCullingMode(CULL_MODE_BACK);
}

Home* GetHome(void)
{
    return &g_Home;
}
