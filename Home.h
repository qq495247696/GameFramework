#pragma once

#include <d3dx9.h>
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
struct Home
{
	D3DXVECTOR3		pos;		// 位置
	D3DXVECTOR3		rot;		// 向き(回転)
	D3DXVECTOR3		scl;		// 大きさ(スケール)
	bool			use;		// 表示フラグ
	int				hp;
	unsigned int    hitedSound;

	D3DXVECTOR3     size;		// 当たり判定用サイズ

	D3DXMATRIX		mtxWorld;	// ワールドマトリックス
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitHome(void);
void UninitHome(void);
void UpdateHome(void);
void DrawHome(void);

Home* GetHome(void);
