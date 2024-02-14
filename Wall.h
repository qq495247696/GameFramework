#pragma once
#include <d3dx9.h>
#include "object.h"
#include "model.h"
class Wall :public Object
{
public:	
	Wall(DX11_MODEL* model, Render* render, World* world) :Object(model, render, "Wall", world)
	{
		_rotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		color = { 1.0f,1.0f,1.0f,1.0f };

		_model->SubsetArray->Material.Material.Diffuse = {1.0,1.0,1.0,1.0};
		_model->SubsetArray->Material.Material.Ambient = { 1.0,1.0,1.0,1.0 };
		_model->SubsetArray->Material.Material.Specular = { 1.0,1.0,1.0,1.0 };
	}
	~Wall(){}
	void Update(double deltaTime) override;
	void Draw() override;
	bool Discard() const override;
private:
	D3DXCOLOR		color;
	D3DXVECTOR3		size;

};
