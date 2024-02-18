/*********************************************************************
 * \file   bullet.h
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#pragma once
#include "object.h"
#include "DirectXAPI.h"
class World;
// バレット構造体
class Bullet:public Object
{
public:
	Bullet(const int texNo, DirectXAPI* api, World* world, Vec3 pos, Vec3 vel) :Object(texNo, "Bullet", world), _api(api), _attack(70)
	{
		// 頂点バッファ生成
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(VERTEX_3D) * 4;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		_api->GetDevice()->CreateBuffer(&bd, NULL, &_vertexBuffer);


		// 頂点バッファに値をセットする
		{
			D3D11_MAPPED_SUBRESOURCE msr;
			_api->GetDeviceContext()->Map(_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

			VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

			float width = 50.0f;
			float height = 50.0f;

			// 頂点座標の設定
			vertex[0].Position = D3DXVECTOR3(-width / 2.0f, 0.0f, 0.0f);
			vertex[1].Position = D3DXVECTOR3(-width / 2.0f, height, 0.0f);
			vertex[2].Position = D3DXVECTOR3(width / 2.0f, 0.0f, 0.0f);
			vertex[3].Position = D3DXVECTOR3(width / 2.0f, height, 0.0f);

			// 頂点カラーの設定
			vertex[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			vertex[0].TexCoord = D3DXVECTOR2(0.0f, 1.0f);
			vertex[1].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
			vertex[2].TexCoord = D3DXVECTOR2(1.0f, 1.0f);
			vertex[3].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

			_api->GetDeviceContext()->Unmap(_vertexBuffer, 0);
		}


		// マテリアル初期化
		ZeroMemory(&_material, sizeof(MATERIAL));
		_material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// 初期化
		_position = pos;
		_vel = vel;
		size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		_speed = 750;
		_use = true;
		frame = 0;
	};
	~Bullet()override 
	{
		if (_vertexBuffer != NULL)
		{// 頂点バッファの解放
			_vertexBuffer->Release();
			_vertexBuffer = NULL;
		}
	}
	float					frame;	// フレーム数
	D3DXVECTOR3				size;		// 当たり判定用サイズ
	int						_attack;


	void Update(double deltaTime) override;
	void Draw() override;
	bool Discard() const override;
private:
	MATERIAL					_material;
	ID3D11Buffer*				_vertexBuffer=NULL;
	DirectXAPI*					_api;
};

\

