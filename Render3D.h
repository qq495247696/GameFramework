#pragma once
#include "Render.h"
//��Ⱦ���������Ⱦ3D
class Render3D:public Render
{
public:
	Render3D(DirectXAPI* api) :Render(api)
	{
	}

	~Render3D()
	{
	}
	// ͨ�� Render �̳�
	void Draw(Object* object) override;
};
