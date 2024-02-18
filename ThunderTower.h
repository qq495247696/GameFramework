/*********************************************************************
 * \file   ThunderTower.h
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#pragma once
#include "object.h"
class ThunderTower :public Object
{
public:
	ThunderTower(DX11_MODEL* model, Render* render, World* world) :Object(model, render, "ThunderTower", world), _finded(false)
		, _attackSpeed(0.5), _attack(120.0f), _attackDistance(550.0f)
	{
		_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		_rotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		_scale = D3DXVECTOR3(5.0f, 5.0f, 5.0f);
		_time = 0;
		_timeValue = 0.5f;
		_attackTime = 0.0f;
		size = D3DXVECTOR3(100.0f, 100.0f, 100.0f);
	}
	~ThunderTower()
	{
	}
	// Õ®π˝ Object ºÃ≥–
	void Update(double deltaTime) override;
	void Draw() override;
	bool Discard() const override;
private:
	int				shadow;		// âeÇÃéØï î‘çÜ
	double			_time;
	double			_attackTime;
	float			_timeValue ;
	bool			_finded;
	float			_attackSpeed;
	float			_attack;
	float			_attackDistance;
	D3DXVECTOR3     size;		// ìñÇΩÇËîªíËópÉTÉCÉY
};
