/*********************************************************************
 * \file   NormalTower.h
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#pragma once
#include "StateMachine.h"
#include "object.h"

//*****************************************************************************
// É}ÉNÉçíËã`
//*****************************************************************************

enum TowerType
{
	Normal,
	Fire,
	Thunder,
};

class NormalTower:public Object
{
public:
	NormalTower(DX11_MODEL* model, Render* render, World* world) :Object(model, render, "NormalTower", world)
		, _finded(false), _attackSpeed(1.5), _attack(100.0f), _attackDistance(850.0f)
	{
		_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		_rotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		_scale = D3DXVECTOR3(5.0f, 5.0f, 5.0f);
		time = 0;
		size = D3DXVECTOR3(100.0f, 100.0f, 100.0f);
	}
	~NormalTower()
	{
	}
	// Õ®π˝ Object ºÃ≥–
	void Update(double deltaTime) override;
	void Draw() override;
	bool Discard() const override;
private:
	void Attack(double deltaTime);
	void NoFoundedEnemy();
	void FoundedEnemy(float deltaTime);
	int				shadow;		// âeÇÃéØï î‘çÜ
	bool			_finded;
	double			time;
	float			_attackSpeed;
	float			_attack;
	float			_attackDistance;
	D3DXVECTOR3     size;		// ìñÇΩÇËîªíËópÉTÉCÉY
};
