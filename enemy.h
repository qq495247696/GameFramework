/*********************************************************************
 * \file   enemy.h
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#pragma once
#include "object.h"

//*****************************************************************************
// マクロ定義
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
		//方向を単位ベクトル化する
		D3DXVec3Normalize(&_vel, &_vel);
	}
	~Enemy()override
	{
		
	}
	bool			_use;		// 表示フラグ
	int				_shadow;		// 影の識別番号
	D3DXVECTOR3     _size;		// 当たり判定用サイズ
	D3DXVECTOR3*	_wayLine;
	int				_target;
	int				_hp;

	// ﾍｨｹ� Object ｼﾌｳﾐ
	void Update(double deltaTime) override;
	void motor(double deltaTime);
	void Draw()override;
	bool Discard() const override;

};

