#pragma once
#include "object.h"
class ThunderTower :public Object
{
public:
	ThunderTower(DX11_MODEL* model, Render* render, World* world) :Object(model, render, "ThunderTower", world)
	{
		_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		_rotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		_scale = D3DXVECTOR3(5.0f, 5.0f, 5.0f);
		time = 0;
		size = D3DXVECTOR3(100.0f, 100.0f, 100.0f);
	}
	~ThunderTower()
	{
	}
	// Ν¨Ήύ Object ΌΜ³Π
	void Update(double deltaTime) override;
	void Draw() override;
	bool Discard() const override;
private:
	int				shadow;		// eΜ―ΚΤ
	double			time;
	D3DXVECTOR3     size;		// ½θ»θpTCY
};
