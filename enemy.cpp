//=============================================================================
//
// 億儕僑儞昞帵張棟 [enemy.cpp]
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
// 儅僋儘掕媊
//*****************************************************************************
#define	VALUE_MOVE		(5.0f)						// 堏摦検
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)			// 夞揮検


//*****************************************************************************
// 僾儘僩僞僀僾愰尵
//*****************************************************************************


//*****************************************************************************
// 僌儘乕僶儖曄悢
//*****************************************************************************
static DX11_MODEL	g_Model;			// 儌僨儖撉傒崬傒
static Enemy		g_Enemy[ENEMY_NUM];	// 僄僱儈乕忣曬		
static float        g_Rot;				// 僉儍儔僋僞乕偺岦偒
int g_turn;
static int g_time;
int g_pauseTime;
int g_createCount;
bool g_pause;

//=============================================================================
// 弶婜壔張棟
//=============================================================================
HRESULT InitEnemy(void)
{
	g_createCount = 0;
	g_pauseTime = 1000;
	g_pause = false;
	g_turn = 0;
	g_time = 0;
	// 埵抲丒夞揮丒僗働乕儖偺弶婜愝掕
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		g_Enemy[i].pos = D3DXVECTOR3(0, 0.0f, 0);
		g_Enemy[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[i].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_Enemy[i].vel = D3DXVECTOR3(0, 0.0f, 0);
		g_Enemy[i].spd = 25.0f;
		g_Enemy[i].use = false;

		g_Enemy[i].size = D3DXVECTOR3(35.0f, 50.0f, 35.0f);

		//曽岦傪扨埵儀僋僩儖壔偡傞
		D3DXVec3Normalize(&g_Enemy[i].vel, &g_Enemy[i].vel);

		//塭偺僙僢僩
		//g_Enemy[i].shadow = SetShadow(D3DXVECTOR3(g_Enemy[i].pos.x, 0.0f, g_Enemy[i].pos.z), 80.0f);
	}

	//obj儌僨儖偺撉傒崬傒
	LoadModel((char*)"data/MODEL/Enemy01.obj", &g_Model);

	return S_OK;
}

//=============================================================================
// 廔椆張棟
//=============================================================================
void UninitEnemy(void)
{
	//obj儌僨儖偺夝曻
	UnloadModel(&g_Model);
}

//=============================================================================
// 峏怴張棟
//=============================================================================
void UpdateEnemy(void)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	// 定义范围在-60到60之间的均匀分布
	std::uniform_int_distribution<> distrib(-300, 300);

	// 生成随机数
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
		//use僼儔僌偑僆僼偺応崌偼僗僉僢僾偡傞
		if (g_Enemy[i].use == false)
			continue;

		//嵗昗偺峏怴
		g_Enemy[i].pos += g_Enemy[i].vel * g_Enemy[i].spd;

		//夞揮偺峏怴
	/*	g_Enemy[i].rot.x += 0.05f;
		g_Enemy[i].rot.y += 0.05f;*/
		//塭偺嵗昗傪峏怴偡傞
		SetPositionShadow(g_Enemy[i].shadow, D3DXVECTOR3(g_Enemy[i].pos.x, 0.0f, g_Enemy[i].pos.z));
	}
}

//=============================================================================
// 昤夋張棟
//=============================================================================
void DrawEnemy(void)
{
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	//SetCullingMode(CULL_MODE_NONE);
	SetLightEnable(false);
	SetAlphaTestEnable(false);
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		//use僼儔僌偑僆僼偺応崌偼僗僉僢僾偡傞
		if (g_Enemy[i].use == false)
			continue;

		// 儚乕儖僪儅僩儕僢僋僗偺弶婜壔乮扨埵峴楍傪嶌傞娭悢乯
		D3DXMatrixIdentity(&g_Enemy[i].mtxWorld);

		// 僗働乕儖傪斀塮
		D3DXMatrixScaling(&mtxScl, g_Enemy[i].scl.x, g_Enemy[i].scl.y, g_Enemy[i].scl.z);
		D3DXMatrixMultiply(&g_Enemy[i].mtxWorld, &g_Enemy[i].mtxWorld, &mtxScl);

		// 夞揮傪斀塮
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy[i].rot.y, g_Enemy[i].rot.x, g_Enemy[i].rot.z);
		D3DXMatrixMultiply(&g_Enemy[i].mtxWorld, &g_Enemy[i].mtxWorld, &mtxRot);

		// 堏摦傪斀塮
		D3DXMatrixTranslation(&mtxTranslate, g_Enemy[i].pos.x, g_Enemy[i].pos.y, g_Enemy[i].pos.z);
		D3DXMatrixMultiply(&g_Enemy[i].mtxWorld, &g_Enemy[i].mtxWorld, &mtxTranslate);

		// 儚乕儖僪儅僩儕僢僋僗偺愝掕
		SetWorldMatrix(&g_Enemy[i].mtxWorld);

		//obj儌僨儖偺昤夋
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
// 僄僱儈乕忣曬傪庢摼
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
