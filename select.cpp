//=============================================================================
//
// ポリゴン表示処理 [Select.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "Select.h"
#include "texture.h"
#include "polyline.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static DX11_MODEL	g_Model;	// モデル読み込み
static Select		g_Select;	// プレイヤー情報		
static LIGHT		g_DirectionalLight;	// ディレクショナルライト
static LIGHT		g_PointLight;		// ポイントライト

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitSelect(void)
{
	// 位置・回転・スケールの初期設定
	g_Select.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Select.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Select.scl = D3DXVECTOR3(5.0f, 5.0f, 5.0f);
	g_Select.use = false;

	//当たり判定用サイズの初期設定
	g_Select.size = D3DXVECTOR3(10.0f, 10.0f, 10.0f);

	//objモデルの読み込み
	LoadModel((char*)"data/MODEL/Select.obj", &g_Model);
	g_Model.SubsetArray->Material.Material.Diffuse = { 0.0,1.0,0.0,0.5 };
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitSelect(void)
{
	//objモデルの解放
	UnloadModel(&g_Model);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateSelect(void)
{
	
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawSelect(void)
{
	if(g_Select.use==true)
	{
		D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
		SetLightEnable(false);
		SetCullingMode(CULL_MODE_NONE);
		// ワールドマトリックスの初期化（単位行列を作る関数）
		D3DXMatrixIdentity(&g_Select.mtxWorld);

		// スケールを反映
		D3DXMatrixScaling(&mtxScl, g_Select.scl.x, g_Select.scl.y, g_Select.scl.z);
		D3DXMatrixMultiply(&g_Select.mtxWorld, &g_Select.mtxWorld, &mtxScl);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Select.rot.y, g_Select.rot.x, g_Select.rot.z);
		D3DXMatrixMultiply(&g_Select.mtxWorld, &g_Select.mtxWorld, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, g_Select.pos.x, g_Select.pos.y, g_Select.pos.z);
		D3DXMatrixMultiply(&g_Select.mtxWorld, &g_Select.mtxWorld, &mtxTranslate);

		// ワールドマトリックスの設定
		SetWorldMatrix(&g_Select.mtxWorld);

		//objモデルの描画
		DrawModel(&g_Model);

		//カリングを元に戻す
		SetCullingMode(CULL_MODE_BACK);
	}
}


//=============================================================================
// プレイヤー情報を取得
//=============================================================================
Select *GetSelect(void)
{
	return &g_Select;
}

DX11_MODEL* GetSelectModel()
{
	return &g_Model;
}

