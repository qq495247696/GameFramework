/*********************************************************************
 * \file   Place.h
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#pragma once
#include "object.h"
#include "model.h"
#include "collision.h"
class Place :public Object
{
public:	
	Place(DX11_MODEL* model, Render* render, World* world) :Object(model, render, "Place", world)
	{
		_rotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		color = { 1.0f,1.0f,1.0f,1.0f };
		_box[0]._pos = { -345,0,4310 };
		_box[0]._size = { 80,800,7380 };
		_box[1]._pos = { 370,0,4310 };
		_box[1]._size = { 80,800,7380 };
	}
	~Place(){}
	void Update(double deltaTime) override;
	void Draw() override;
	bool Discard() const override;
	const HitBox* GetBox()const { return _box; }

private:
	D3DXCOLOR		color;
	D3DXVECTOR3		size;
	HitBox			_box[2];
};
