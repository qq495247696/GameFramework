#pragma once
#ifndef Render2D_H
#define Render2D_H
#include "Render.h"
#include"main.h"

//渲染插件用于渲染2D平脕E
class Render2D:public Render
{
public:
	Render2D(DirectXAPI* api, Anchor anchor);
	
	~Render2D()override
	{
		if (_vertexBuffer)
		{
			_vertexBuffer->Release();
			_vertexBuffer = NULL;
		}
	}
	void DrawCenter(Object* object);
	void DrawLeftTop(Object* object);
	void Draw(Object* object) override;

	D3DXVECTOR2		_pos;
	Anchor			_anchor;
	D3DXCOLOR		_color;
	D3DXVECTOR2		_UV;
	float			_UW;
	float			_VH;
	float			_rotate;
	float			_width;
	float			_height;
private:
	ID3D11Buffer*	_vertexBuffer = NULL;	
	MATERIAL		_material;	
};

#endif // !Render2D_H
