//=============================================================================
//
// 地面処理 [Tower.h]
// Author : 
//
//=============================================================================
#pragma once

#include <d3dx9.h>
#include "StateMachine.h"
#include "object.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

enum TowerType
{
	Normal,
	Fire,
	Light,
};

class Tower:public Object
{
public:
	Tower(DX11_MODEL* model, Render* render, World* world) :Object(model, render, "NormalTower", world)
	{
		_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		_rotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		_scale = D3DXVECTOR3(5.0f, 5.0f, 5.0f);
		time = 0;
		size = D3DXVECTOR3(100.0f, 100.0f, 100.0f);
	}
	~Tower()
	{
	}
	// ﾍｨｹ� Object ｼﾌｳﾐ
	void Update(double deltaTime) override;
	void Draw() override;
	bool Discard() const override;
private:
	int				shadow;		// 影の識別番号
	double			time;
	D3DXVECTOR3     size;		// 当たり判定用サイズ
};
