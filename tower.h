//=============================================================================
//
// 地面処理 [Tower.h]
// Author : 
//
//=============================================================================
#pragma once

#include <d3dx9.h>
#include "renderer.h"
#include "StateMachine.h"
#include "model.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

enum TowerType
{
	Normal,
	Fire,
	Light,
};

class Tower
{
public:
	D3DXVECTOR3		pos;		// 位置
	D3DXVECTOR3		rot;		// 向き(回転)
	D3DXVECTOR3		scl;		// 大きさ(スケール)
	float			spd;		// 移動スピード
	bool			use;		// 表示フラグ
	int				shadow;		// 影の識別番号
	int				time;
	D3DXVECTOR3     size;		// 当たり判定用サイズ
	DX11_MODEL*     model;

	D3DXMATRIX		mtxWorld;	// ワールドマトリックス
};
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTower(void);
void UninitTower(void);
void UpdateTower(void);
void DrawTower(void);
Tower *GetTower(void);
void SetTower(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TowerType type);
