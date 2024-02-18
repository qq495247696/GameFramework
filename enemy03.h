/*********************************************************************
 * \file   enemy.h
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#pragma once
#include "object.h"
#include "AssetManager.h"
//*****************************************************************************
// ƒ}ƒNƒ’è‹`
//*****************************************************************************
#define ENEMY_NUM 20

class Enemy03:public Object
{
public:

	Enemy03(const Vec3& Pos ,Render* render, D3DXVECTOR3* wayLine,World* world) :Object(&AssetManager::Get()->_enemy03, render, "Enemy",world),_wayLine(wayLine), _attackTime(0.0), _atk(80)
	{
		_position = Pos;
		_rotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		_scale = D3DXVECTOR3(3.0f, 3.0f, 3.0f);
		_vel = D3DXVECTOR3(0, 0.0f, 0);
		_speed = 400.0f;
		_use = false;
		_target = 0;
		_hp = 3600;
		_size = D3DXVECTOR3(35.0f, 50.0f, 35.0f);
		//•ûŒü‚ğ’PˆÊƒxƒNƒgƒ‹‰»‚·‚é
		D3DXVec3Normalize(&_vel, &_vel);
	}
	~Enemy03()override
	{
		
	}
	bool			_use;		// •\¦ƒtƒ‰ƒO
	int				_shadow;		// ‰e‚Ì¯•Ê”Ô†
	D3DXVECTOR3     _size;		// “–‚½‚è”»’è—pƒTƒCƒY
	D3DXVECTOR3*	_wayLine;
	int				_target;
	double			_attackTime;
	int				_atk;

	// Í¨¹ı Object ¼Ì³Ğ
	void Update(double deltaTime) override;
	void motor(double deltaTime);
	void Draw()override;
	bool Discard() const override;

};

