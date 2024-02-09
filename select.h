//=============================================================================
//
// 地面処理 [Select.h]
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
class Select
{
public:
	D3DXVECTOR3		pos;		// 位置
	D3DXVECTOR3		rot;		// 向き(回転)
	D3DXVECTOR3		scl;		// 大きさ(スケール)
	bool			use;		// 表示フラグ
	D3DXVECTOR3     size;		// 当たり判定用サイズ

	D3DXMATRIX		mtxWorld;	// ワールドマトリックス
};
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSelect(void);
void UninitSelect(void);
void UpdateSelect(void);
void DrawSelect(void);
Select *GetSelect(void);
DX11_MODEL* GetSelectModel(void);
