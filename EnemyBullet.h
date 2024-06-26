/*********************************************************************
 * \file   EnemyBullet.h
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#pragma once
#include "AssetManager.h"
#include "object.h"
class EnemyBullet:public Object
{
public:
	EnemyBullet(Vec3 pos, Vec3 vel, int atk, Render* render, World* world) :Object(&AssetManager::Get()->_enemyBullet, render, "EnemyBullet", world), _attack(atk)
	{
		_position = pos;
		_vel = vel;
		_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		_rotate = { 0,0,0 };
		_use = true;
		_speed = 250;
	}
	~EnemyBullet(){}

	void Update(double deltaTime) override;
	void Draw() override;
	bool Discard() const override;
	int				_attack;
};
