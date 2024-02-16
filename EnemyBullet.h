/*********************************************************************
 * \file   EnemyBullet.h
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#pragma once
#include "object.h"
class EnemyBullet:public Object
{
public:
	EnemyBullet(DX11_MODEL* model, Render* render, World* world) :Object(model, render, "EnemyBullet", world)
	{
		_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		_vel = D3DXVECTOR3(0.0f, 0.0f, 100.0f);
		_scale = D3DXVECTOR3(10.0f, 10.0f, 10.0f);
		_rotate = { 0,0,0 };
		_use = true;
		_speed = 3;
		frame = 0;
	/*	size = D3DXVECTOR3(10.0f, 10.0f, 10.0f);*/
	}
	~EnemyBullet(){}

	float					frame;	// ÉtÉåÅ[ÉÄêî
	void Update(double deltaTime) override;
	void Draw() override;
	bool Discard() const override;

};
