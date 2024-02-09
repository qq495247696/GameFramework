//=============================================================================
//
// ポリゴン表示処理 [Tower.cpp]
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
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static Tower		g_Tower[100];	// プレイヤー情報		
static LIGHT		g_DirectionalLight;	// ディレクショナルライト
static LIGHT		g_PointLight;		// ポイントライト
static int			g_AxisLine[3]; //ポリライン用識別子
static int			g_time;
static DX11_MODEL  g_ModelData[3];
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTower(void)
{

	LoadModel((char*)"data/MODEL/Tower.obj", &g_ModelData[0]);
	LoadModel((char*)"data/MODEL/Tower2.obj", &g_ModelData[1]);
	LoadModel((char*)"data/MODEL/Tower3.obj", &g_ModelData[2]);
	for (int i = 0; i < 100; i++)
	{
		// 位置・回転・スケールの初期設定
		g_Tower[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Tower[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Tower[i].scl = D3DXVECTOR3(5.0f, 5.0f, 5.0f);
		g_Tower[i].use = false;
		g_Tower[i].time = 0;
		//当たりi][判定用サイズの初期設定
		g_Tower[i].size = D3DXVECTOR3(100.0f, 100.0f, 100.0f); 
		g_Tower[i].model = &g_ModelData[0];
		//g_Tower[i].shadow = SetShadow(D3DXVECTOR3(g_Tower[i].pos.x, 0.0f, g_Tower[i].pos.z), 80.0f);
	}
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTower(void)
{
	//objモデルの解放
	UnloadModel(&g_ModelData[0]);
	UnloadModel(&g_ModelData[1]);
	UnloadModel(&g_ModelData[2]);
}

//=============================================================================
// 更新処理
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
// 描画処理
//=============================================================================
void DrawTower(void)
{
	for(int i=0;i<100;i++)
	{
		if (g_Tower[i].use == true)
		{
			D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
			SetLightEnable(true);
			// ワールドマトリックスの初期化（単位行列を作る関数）
			D3DXMatrixIdentity(&g_Tower[i].mtxWorld);

			// スケールを反映
			D3DXMatrixScaling(&mtxScl, g_Tower[i].scl.x, g_Tower[i].scl.y, g_Tower[i].scl.z);
			D3DXMatrixMultiply(&g_Tower[i].mtxWorld, &g_Tower[i].mtxWorld, &mtxScl);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Tower[i].rot.y, g_Tower[i].rot.x, g_Tower[i].rot.z);
			D3DXMatrixMultiply(&g_Tower[i].mtxWorld, &g_Tower[i].mtxWorld, &mtxRot);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, g_Tower[i].pos.x, g_Tower[i].pos.y, g_Tower[i].pos.z);
			D3DXMatrixMultiply(&g_Tower[i].mtxWorld, &g_Tower[i].mtxWorld, &mtxTranslate);

			// ワールドマトリックスの設定
			SetWorldMatrix(&g_Tower[i].mtxWorld);

			//カリングなし(ミクさんモデルの髪の対応)
			SetCullingMode(CULL_MODE_NONE);

			//objモデルの描画
			DrawModel(g_Tower[i].model);

			//カリングを元に戻す
			SetCullingMode(CULL_MODE_BACK);
		}
	}
}


//=============================================================================
// プレイヤー情報を取得
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

