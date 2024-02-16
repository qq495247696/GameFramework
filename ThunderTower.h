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
	// ͨ�� Object �̳�
	void Update(double deltaTime) override;
	void Draw() override;
	bool Discard() const override;
private:
	int				shadow;		// �e�̎��ʔԍ�
	double			time;
	D3DXVECTOR3     size;		// �����蔻��p�T�C�Y
};
