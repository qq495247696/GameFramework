//=============================================================================
//
// ’n–Êˆ— [enemy.h]
// Author : 
//
//=============================================================================
#pragma once

#include <d3dx9.h>
#include "object.h"

//*****************************************************************************
// ƒ}ƒNƒ’è‹`
//*****************************************************************************
#define ENEMY_NUM 20

class Enemy:public Object
{
public:

	Enemy(DX11_MODEL* model,const Vec3& Pos ,Render* render, D3DXVECTOR3* wayLine,World* world) :Object(model, render, "Enemy",world),_wayLine(wayLine)
	{
		_position = Pos;
		_rotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		_vel = D3DXVECTOR3(0, 0.0f, 0);
		_speed = 350.0f;
		_use = false;
		_target = 0;
		_size = D3DXVECTOR3(35.0f, 50.0f, 35.0f);
		//•ûŒü‚ğ’PˆÊƒxƒNƒgƒ‹‰»‚·‚é
		D3DXVec3Normalize(&_vel, &_vel);
	}
	~Enemy()override
	{
		
	}
	bool			_use;		// •\¦ƒtƒ‰ƒO
	int				_shadow;		// ‰e‚Ì¯•Ê”Ô†
	D3DXVECTOR3     _size;		// “–‚½‚è”»’è—pƒTƒCƒY
	D3DXVECTOR3*	_wayLine;
	int				_target;

	// Í¨¹ı Object ¼Ì³Ğ
	void Update(double deltaTime) override;
	void motor(double deltaTime);
	void Draw()override;
	bool Discard() const override;

};

