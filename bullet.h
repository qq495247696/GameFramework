//=============================================================================
//
// 弾処理 [bullet.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BULLET_NUM		(10)		// バレットのMax数
#define BULLET_SPEED	(10.0f)		// バレットの移動スピード


// バレット構造体
class Bullet
{
public:
	D3DXMATRIX				mtxWorld;
	bool					use;	// true:使っている  false:未使用
	D3DXVECTOR3				pos;	// バレットの座標
	D3DXVECTOR3				dir;	// バレットの移動方向
	float					speed;	// バレットの移動スピード
	float					frame;	// フレーム数
	int						shadow;	// 影の識別番号

	D3DXVECTOR3     size;		// 当たり判定用サイズ
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

Bullet *GetBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 dir);

