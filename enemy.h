//=============================================================================
//
// 地面処理 [enemy.h]
// Author : 
//
//=============================================================================
#pragma once

#include <d3dx9.h>
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ENEMY_NUM 20

class Enemy
{
public:

	Enemy() = default;
	~Enemy(){}
	void Update();
	void Draw();
	D3DXVECTOR3		pos;		// 位置
	D3DXVECTOR3		rot;		// 向き(回転)
	D3DXVECTOR3		scl;		// 大きさ(スケール)
	D3DXVECTOR3		vel;		// 移動方向
	float			spd;		// 移動スピード
	bool			use;		// 表示フラグ
	int				shadow;		// 影の識別番号
	D3DXVECTOR3     size;		// 当たり判定用サイズ



	D3DXMATRIX		mtxWorld;	// ワールドマトリックス


};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 dir, int time);

Enemy *GetEnemy(void);
