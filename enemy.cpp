//=============================================================================
//
// �|���S���\������ [enemy.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "enemy.h"
#include "texture.h"
#include "model.h"
#include "player.h"
#include "shadow.h"
#include <random>
#include "BattlePhase.h"
#include "PreparationPhase.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	VALUE_MOVE		(5.0f)						// �ړ���
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)			// ��]��


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static DX11_MODEL	g_Model;			// ���f���ǂݍ���
static Enemy		g_Enemy[ENEMY_NUM];	// �G�l�~�[���		
static float        g_Rot;				// �L�����N�^�[�̌���
int g_turn;
static int g_time;
int g_pauseTime;
int g_createCount;
bool g_pause;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemy(void)
{
	g_createCount = 0;
	g_pauseTime = 1000;
	g_pause = false;
	g_turn = 0;
	g_time = 0;
	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		g_Enemy[i].pos = D3DXVECTOR3(0, 0.0f, 0);
		g_Enemy[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[i].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_Enemy[i].vel = D3DXVECTOR3(0, 0.0f, 0);
		g_Enemy[i].spd = 25.0f;
		g_Enemy[i].use = false;

		g_Enemy[i].size = D3DXVECTOR3(35.0f, 50.0f, 35.0f);

		//������P�ʃx�N�g��������
		D3DXVec3Normalize(&g_Enemy[i].vel, &g_Enemy[i].vel);

		//�e�̃Z�b�g
		//g_Enemy[i].shadow = SetShadow(D3DXVECTOR3(g_Enemy[i].pos.x, 0.0f, g_Enemy[i].pos.z), 80.0f);
	}

	//obj���f���̓ǂݍ���
	LoadModel((char*)"data/MODEL/Enemy01.obj", &g_Model);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy(void)
{
	//obj���f���̉��
	UnloadModel(&g_Model);
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy(void)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	// ���巶Χ��-60��60֮��ľ��ȷֲ�
	std::uniform_int_distribution<> distrib(-300, 300);

	// ���������
	int randomNumber = distrib(gen);

	if (g_turn % 4 == 0&& g_pause==false)
	{
		SetEnemy({ (float)(randomNumber),0,10000 }, { 0,-D3DX_PI,0 }, {0,0,-1}, 150-(g_turn*10));
	}
	else if (g_turn % 4 == 1 && g_pause == false)
	{
		SetEnemy({ 3500,0,(float)(randomNumber) }, { 0,-D3DX_PI/2,0 }, { -1,0,0 }, 150- (g_turn * 10));
	}
	else if (g_turn % 4 == 2 && g_pause == false)
	{
		SetEnemy({ (float)(randomNumber),0,-3500 }, { 0,D3DX_PI,0 }, { 0,0,1 }, 150- (g_turn * 10));
	}
	else if (g_turn % 4 == 3 && g_pause == false)
	{
		SetEnemy({ -3500,0,(float)(randomNumber) }, { 0,D3DX_PI / 2,0 }, { 1,0,0 }, 150- (g_turn * 10));
	}


	if (g_pause == false&& GetPlayer()->fsm.GetCurrentState()!= BattlePhase::Instance())
	{
		GetPlayer()->fsm.ChangeState(BattlePhase::Instance());
	}
	else if(g_pause==true&& GetPlayer()->fsm.GetCurrentState()== BattlePhase::Instance())
	{
		GetPlayer()->fsm.ChangeState(PreparationPhase::Instance());
	}


	if (g_createCount >= 15)
	{
		g_pause = true;
		g_time = 0;
		g_pauseTime--;
		if(g_pauseTime <= 0)
		{
			g_createCount = 0;
			g_turn++;
			g_pauseTime = 600;
			g_pause = false;
			g_time = 0;
		}
	}

	if (g_pause==false)
	{
		g_time++;
	}

	for (int i = 0; i < ENEMY_NUM; i++)
	{
		//use�t���O���I�t�̏ꍇ�̓X�L�b�v����
		if (g_Enemy[i].use == false)
			continue;

		//���W�̍X�V
		g_Enemy[i].pos += g_Enemy[i].vel * g_Enemy[i].spd;

		//��]�̍X�V
	/*	g_Enemy[i].rot.x += 0.05f;
		g_Enemy[i].rot.y += 0.05f;*/
		//�e�̍��W���X�V����
		SetPositionShadow(g_Enemy[i].shadow, D3DXVECTOR3(g_Enemy[i].pos.x, 0.0f, g_Enemy[i].pos.z));
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy(void)
{
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	//SetCullingMode(CULL_MODE_NONE);
	SetLightEnable(false);
	SetAlphaTestEnable(false);
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		//use�t���O���I�t�̏ꍇ�̓X�L�b�v����
		if (g_Enemy[i].use == false)
			continue;

		// ���[���h�}�g���b�N�X�̏������i�P�ʍs������֐��j
		D3DXMatrixIdentity(&g_Enemy[i].mtxWorld);

		// �X�P�[���𔽉f
		D3DXMatrixScaling(&mtxScl, g_Enemy[i].scl.x, g_Enemy[i].scl.y, g_Enemy[i].scl.z);
		D3DXMatrixMultiply(&g_Enemy[i].mtxWorld, &g_Enemy[i].mtxWorld, &mtxScl);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy[i].rot.y, g_Enemy[i].rot.x, g_Enemy[i].rot.z);
		D3DXMatrixMultiply(&g_Enemy[i].mtxWorld, &g_Enemy[i].mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, g_Enemy[i].pos.x, g_Enemy[i].pos.y, g_Enemy[i].pos.z);
		D3DXMatrixMultiply(&g_Enemy[i].mtxWorld, &g_Enemy[i].mtxWorld, &mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		SetWorldMatrix(&g_Enemy[i].mtxWorld);

		//obj���f���̕`��
		DrawModel(&g_Model);
		//SetCullingMode(CULL_MODE_BACK);
	}
}

void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot,D3DXVECTOR3 dir,int time)
{
	if (g_time % time == 0)
	{
		for (int i = 0; i < ENEMY_NUM; i++)
		{
			if (g_Enemy[i].use != true)
			{
				g_Enemy[i].pos = pos;
				g_Enemy[i].rot = rot;
				g_Enemy[i].vel = dir;
				g_Enemy[i].spd = (g_turn+1) * 5;
				g_Enemy[i].use = true;
				g_createCount++;
				break;
			}
		}
	}
}


//=============================================================================
// �G�l�~�[�����擾
//=============================================================================
Enemy *GetEnemy(void)
{
	return g_Enemy;
}

void Enemy::Update()
{

	pos += vel*spd* (1000 / 60);
}

void Enemy::Draw()
{
}
