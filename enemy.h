//=============================================================================
//
// 地面処理 [enemy.h]
// Author : 
//
//=============================================================================
#pragma once

#include <d3dx9.h>
#include "object.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ENEMY_NUM 20

class Enemy:public Object
{
public:

	Enemy(DX11_MODEL* model, Render* render, World* world) :Object(model, render, "Enemy",world)
	{
		//g_createCount = 0;
		//g_pauseTime = 1000;
		//g_pause = false;
		//g_turn = 0;
		//g_time = 0;
		_position = D3DXVECTOR3(0, 0.0f, 0);
		_rotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		_vel = D3DXVECTOR3(0, 0.0f, 0);
		_speed = 25.0f;
		_use = false;
		size = D3DXVECTOR3(35.0f, 50.0f, 35.0f);
		//方向を単位ベクトル化する
		D3DXVec3Normalize(&_vel, &_vel);
	}
	~Enemy()override
	{
		UnloadModel(_model);
	}
	bool			use;		// 表示フラグ
	int				shadow;		// 影の識別番号
	D3DXVECTOR3     size;		// 当たり判定用サイズ


	// ﾍｨｹ� Object ｼﾌｳﾐ
	void Update(double deltaTime) override;
	void Draw()override;
	bool Discard() const override;

};

