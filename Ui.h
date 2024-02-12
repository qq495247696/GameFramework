#pragma once
#include "render.h"
#include "texture.h"
#include "DirectXAPI.h"
#include "main.h"
#include "object.h"
class Ui
{
public:
	Ui()
	{
		//
		//D3D11_BUFFER_DESC bd;
		//ZeroMemory(&bd, sizeof(bd));
		//bd.Usage = D3D11_USAGE_DYNAMIC;
		//bd.ByteWidth = sizeof(VERTEX_3D) * 4;
		//bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		//bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		//GetDevice()->CreateBuffer(&bd, NULL, &_vertexBuffer);

		//{
		//	D3D11_MAPPED_SUBRESOURCE msr;
		//	GetDeviceContext()->Map(_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		//	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		//	float width = 1920.0f;
		//	float height = 1080.0f;

		//	// 頂点座標の設定
		//	vertex[0].Position = D3DXVECTOR3(-width / 2.0f, 0.0f, 0.0f);
		//	vertex[1].Position = D3DXVECTOR3(-width / 2.0f, height, 0.0f);
		//	vertex[2].Position = D3DXVECTOR3(width / 2.0f, 0.0f, 0.0f);
		//	vertex[3].Position = D3DXVECTOR3(width / 2.0f, height, 0.0f);

		//	// 頂点カラーの設定
		//	vertex[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//	vertex[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//	vertex[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//	vertex[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//	// テクスチャ座標の設定
		//	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 1.0f);
		//	vertex[1].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
		//	vertex[2].TexCoord = D3DXVECTOR2(1.0f, 1.0f);
		//	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

		//	GetDeviceContext()->Unmap(_vertexBuffer, 0);
		//}
		//_texNo = LoadTexture((char*)"data/TEXTURE/Ui.png");
		//ZeroMemory(&_material, sizeof(_material));
		//_material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		
	}

	~Ui()
	{

		if (_vertexBuffer)
		{
			_vertexBuffer->Release();
			_vertexBuffer = nullptr;
		}
	}
	void Update();
	void Draw();
private:
	ID3D11Buffer* _vertexBuffer=nullptr;
	D3DXMATRIX	  _mtxWorld;
	D3DXVECTOR3	  _position;
	MATERIAL	  _material;
	int			  _texNo;
};
