//=============================================================================
//
// 地面処理 [player.h]
// Author : 
//
//=============================================================================
#pragma once

#include <d3dx9.h>
#include "renderer.h"
#include "StateMachine.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************




class Player
{
public:
	D3DXVECTOR3		pos;		// 位置
	D3DXVECTOR3		rot;		// 向き(回転)
	D3DXVECTOR3		scl;		// 大きさ(スケール)
	float			spd;		// 移動スピード
	bool			use;		// 表示フラグ
	int				shadow;		// 影の識別番号

	D3DXVECTOR3     size;		// 当たり判定用サイズ

	D3DXMATRIX		mtxWorld;	// ワールドマトリックス
	int				currency;
	int				se;
	float 		frame;

	void DrawAnim(float* frame, D3DXVECTOR3& rot, D3DXVECTOR3& pos);
	StateMachine<Player> fsm{this};
};
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player *GetPlayer(void);
