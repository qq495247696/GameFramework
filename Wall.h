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
		_box1._pos = { -1660,0,4310 };
		_box1._size = { 2450,800,7480 };
		_box2._pos = { 1660,0,4310 };
		_box2._size = { 2450,800,7480 };
		_box3._pos = { -1662.5,0,150 };
		_box3._size = { 825,800,840 };
		_box4._pos = { 1662.5,0,150 };
		_box4._size = { 825,800,840 };

		_model->SubsetArray->Material.Material.Diffuse = {1.0,1.0,1.0,1.0};
		_model->SubsetArray->Material.Material.Ambient = { 1.0,1.0,1.0,1.0 };
		_model->SubsetArray->Material.Material.Specular = { 1.0,1.0,1.0,1.0 };
	}
	~Wall(){}
	void Update(double deltaTime) override;
	void Draw() override;
	bool Discard() const override;
	const HitBox& GetBox1()const { return _box1; }
	const HitBox& GetBox2()const { return _box2; }
	const HitBox& GetBox3()const { return _box3; }
	const HitBox& GetBox4()const { return _box4; }
private:
	D3DXCOLOR		color;
	D3DXVECTOR3		size;
	HitBox			_box1;
	HitBox			_box2;
	HitBox			_box3;
	HitBox			_box4;
};
