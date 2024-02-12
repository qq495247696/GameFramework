#pragma once
#include "DirectXAPI.h"
#include "object.h"
enum class Anchor
{
	LeftTop,
	Center
};
//渲染插件用于渲染2D平面
class Render2D:public Render
{
public:
	Render2D(DirectXAPI* api, Anchor anchor) :Render(api), _pos(0, 0), _anchor(_anchor), _color({ 1.0f,1.0f,1.0f,1.0f }), _UV({0.0f,0.0f}),
		_UW(1.0f), _VH(1.0f), _rotate(0.0f), _width(1920), _height(1080)
	{
		ID3D11Device *pDevice = _dApi->GetDevice().Get();

		// 捀揰僶僢僼傽惗惉
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(VERTEX_3D) * 4;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		pDevice->CreateBuffer(&bd, NULL, &_vertexBuffer);
		
		//儅僥儕傾儖偺弶婜壔
		ZeroMemory(&_material, sizeof(_material));
		_material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

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

