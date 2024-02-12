#pragma once
#include "Render.h"
//渲染插件用于渲染3D
class Render3D:public Render
{
public:
	Render3D(DirectXAPI* api) :Render(api)
	{
	}

	~Render3D()
	{
	}
	// 通过 Render 继承
	void Draw(Object* object) override;
};
