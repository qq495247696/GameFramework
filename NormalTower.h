//=============================================================================
//
// ínñ èàóù [NormalTower.h]
// Author : 
//
//=============================================================================
#pragma once

#include <d3dx9.h>
#include "StateMachine.h"
#include "object.h"

//*****************************************************************************
// É}ÉNÉçíËã`
//*****************************************************************************

enum TowerType
{
	Normal,
	Fire,
	Light,
};

class NormalTower:public Object
{
public:
	NormalTower(DX11_MODEL* model, Render* render, World* world) :Object(model, render, "NormalTower", world)
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
	int				shadow;		// âeÇÃéØï î‘çÜ
	double			time;
	D3DXVECTOR3     size;		// ìñÇΩÇËîªíËópÉTÉCÉY
};
