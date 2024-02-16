#pragma once
#include "object.h"
class FireTower :public Object
{
public:
	FireTower(DX11_MODEL* model, Render* render, World* world) :Object(model, render, "FireTower", world)
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
	// Í¨¹ı Object ¼Ì³Ğ
	void Update(double deltaTime) override;
	void Draw() override;
	bool Discard() const override;
private:
	int				shadow;		// ‰e‚Ì¯•Ê”Ô†
	double			time;
	D3DXVECTOR3     size;		// “–‚½‚è”»’è—pƒTƒCƒY
};
