//=============================================================================
//
// ポリゴン表示処理 [enemy.cpp]
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
// マクロ定義
//*****************************************************************************
#define	VALUE_MOVE		(5.0f)						// 移動量
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)			// 回転量


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static DX11_MODEL	g_Model;			// モデル読み込み
static Enemy		g_Enemy[ENEMY_NUM];	// エネミー情報		
static float        g_Rot;				// キャラクターの向き
int g_turn;
static int g_time;
int g_pauseTime;
int g_createCount;
bool g_pause;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemy(void)
{
	g_createCount = 0;
	g_pauseTime = 1000;
	g_pause = false;
	g_turn = 0;
	g_time = 0;
	// 位置・回転・スケールの初期設定
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		g_Enemy[i].pos = D3DXVECTOR3(0, 0.0f, 0);
		g_Enemy[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[i].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_Enemy[i].vel = D3DXVECTOR3(0, 0.0f, 0);
		g_Enemy[i].spd = 25.0f;
		g_Enemy[i].use = false;

		g_Enemy[i].size = D3DXVECTOR3(35.0f, 50.0f, 35.0f);

		//方向を単位ベクトル化する
		D3DXVec3Normalize(&g_Enemy[i].vel, &g_Enemy[i].vel);

		//影のセット
		//g_Enemy[i].shadow = SetShadow(D3DXVECTOR3(g_Enemy[i].pos.x, 0.0f, g_Enemy[i].pos.z), 80.0f);
	}

	//objモデルの読み込み
	LoadModel((char*)"data/MODEL/Enemy01.obj", &g_Model);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy(void)
{
	//objモデルの解放
	UnloadModel(&g_Model);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy(void)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	// ｶｨﾒ蟾ｶﾎｧﾔﾚ-60ｵｽ60ﾖｮｼ莊ﾄｾ�ﾔﾈｷﾖｲｼ
	std::uniform_int_distribution<> distrib(-300, 300);

	// ﾉ�ｳﾉﾋ貊�ﾊ�
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
		//useフラグがオフの場合はスキップする
		if (g_Enemy[i].use == false)
			continue;

		//座標の更新
		g_Enemy[i].pos += g_Enemy[i].vel * g_Enemy[i].spd;

		//回転の更新
	/*	g_Enemy[i].rot.x += 0.05f;
		g_Enemy[i].rot.y += 0.05f;*/
		//影の座標を更新する
		SetPositionShadow(g_Enemy[i].shadow, D3DXVECTOR3(g_Enemy[i].pos.x, 0.0f, g_Enemy[i].pos.z));
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemy(void)
{
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	//SetCullingMode(CULL_MODE_NONE);
	SetLightEnable(false);
	SetAlphaTestEnable(false);
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		//useフラグがオフの場合はスキップする
		if (g_Enemy[i].use == false)
			continue;

		// ワールドマトリックスの初期化（単位行列を作る関数）
		D3DXMatrixIdentity(&g_Enemy[i].mtxWorld);

		// スケールを反映
		D3DXMatrixScaling(&mtxScl, g_Enemy[i].scl.x, g_Enemy[i].scl.y, g_Enemy[i].scl.z);
		D3DXMatrixMultiply(&g_Enemy[i].mtxWorld, &g_Enemy[i].mtxWorld, &mtxScl);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy[i].rot.y, g_Enemy[i].rot.x, g_Enemy[i].rot.z);
		D3DXMatrixMultiply(&g_Enemy[i].mtxWorld, &g_Enemy[i].mtxWorld, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, g_Enemy[i].pos.x, g_Enemy[i].pos.y, g_Enemy[i].pos.z);
		D3DXMatrixMultiply(&g_Enemy[i].mtxWorld, &g_Enemy[i].mtxWorld, &mtxTranslate);

		// ワールドマトリックスの設定
		SetWorldMatrix(&g_Enemy[i].mtxWorld);

		//objモデルの描画
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
// エネミー情報を取得
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
