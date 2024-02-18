/*********************************************************************
 * \file   FireTower.h
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#pragma once
#include "object.h"
class FireTower :public Object
{
public:
	FireTower(DX11_MODEL* model, Render* render, World* world) :Object(model, render, "FireTower", world)
		, _finded(false), _attackSpeed(7.5), _attack(1000.0f), _attackDistance(1550.0f)
	{
		_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		_rotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		_scale = D3DXVECTOR3(5.0f, 5.0f, 5.0f);
		time = 0;
		size = D3DXVECTOR3(100.0f, 100.0f, 100.0f);
	}
	~FireTower()
	{
	}
	

	void Update(double deltaTime) override;
	void Draw() override;
	bool Discard() const override;
private:
	void Attack(double deltaTime, Vec3 vel);
	void NoFoundedEnemy();
	void FoundedEnemy(double deltaTime);
	int				shadow;		// 影の識別番号
	double			time;
	bool			_finded;
	float			_attackSpeed;
	float			_attack;
	float			_attackDistance;
	D3DXVECTOR3     size;		// 当たり判定用サイズ
};
