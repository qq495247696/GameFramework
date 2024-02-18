/*********************************************************************
 * \file   TBullet.h
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#pragma once
#include "AssetManager.h"
#include "object.h"
class TBullet:public Object
{
public:
	TBullet(DX11_MODEL* model, Vec3 pos, Vec3 vel, float speed, int atk, Render* render, World* world) :Object(model, render, "TBullet", world), _attack(atk)
	{
		_position = pos;
		_vel = vel;
		_scale = D3DXVECTOR3(5.0f, 5.0f, 5.0f);
		_rotate = { 0,0,0 };
		_use = true;
		_speed = speed;
	}
	~TBullet(){}

	void Update(double deltaTime) override;
	void Draw() override;
	bool Discard() const override;
	int				_attack;
};