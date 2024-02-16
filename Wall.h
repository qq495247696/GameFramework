#pragma once
#include <d3dx9.h>
#include "object.h"
#include "model.h"
#include "collision.h"
class Wall :public Object
{
public:	
	Wall(DX11_MODEL* model, Render* render, World* world) :Object(model, render, "Wall", world)
	{
		_rotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		color = { 1.0f,1.0f,1.0f,1.0f };
		_box[0]._pos = { -1660,0,4310 };
		_box[0]._size = { 2450,800,7480 };
		_box[1]._pos = { 1660,0,4310 };
		_box[1]._size = { 2450,800,7480 };
		_box[2]._pos = { -1662.5,0,150 };
		_box[2]._size = { 825,800,840 };
		_box[3]._pos = { 1662.5,0,150 };
		_box[3]._size = { 825,800,840 };
		_box[4]._pos = { -2487,0,-690 };
		_box[4]._size = { 825,800,840 };
		_box[5]._pos = { 2487,0,-690 };
		_box[5]._size = { 825,800,840 };
		_box[6]._pos = { -1662.5,0,-1530 };
		_box[6]._size = { 825,800,840 };
		_box[7]._pos = { 1662.5,0,-1530 };
		_box[7]._size = { 825,800,840 };
		_box[8]._pos = {0,0,-2350 };
		_box[8]._size = { 10000,800,840 };
		_box[9]._pos = { 0,0,8470 };
		_box[9]._size = { 10000,800,840 };
		_model->SubsetArray->Material.Material.Diffuse = {1.0,1.0,1.0,1.0};
		_model->SubsetArray->Material.Material.Ambient = { 1.0,1.0,1.0,1.0 };
		_model->SubsetArray->Material.Material.Specular = { 1.0,1.0,1.0,1.0 };
	}
	~Wall(){}
	void Update(double deltaTime) override;
	void Draw() override;
	bool Discard() const override;
	const HitBox* GetBox()const { return _box; }

private:
	D3DXCOLOR		color;
	D3DXVECTOR3		size;
	HitBox			_box[10];
};
