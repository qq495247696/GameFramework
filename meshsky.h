/*********************************************************************
 * \file   meshsky.h
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#pragma once
#include "object.h"
class DirectXAPI;
class World;
struct SkyMesh
{
	D3DXVECTOR3					_pos;
	D3DXVECTOR3					_rot;
	MATERIAL					_material;
	ID3D11Buffer*				_vertexBuffer;	// 頂点バッファ
	ID3D11Buffer*				_indexBuffer;	// インデックスバッファ
	int							_numVertex;		//頂点数
	int							_numIndex;		//インデックス
	D3DXMATRIX					_mtxWorld;
};


class SkyBox:public Object
{
public:
	SkyBox(int texNo,DirectXAPI* api,D3DXVECTOR3 pos, D3DXVECTOR3 rot,
		float radius, int numBlockX, int numBlockZ,World* world,bool reverse = false);
	~SkyBox()
	{
		// 周回部分メッシュの解放
		if (_sky._indexBuffer != NULL)
		{
			_sky._indexBuffer->Release();
			_sky._indexBuffer = NULL;
		}

		if (_sky._vertexBuffer != NULL)
		{
			_sky._vertexBuffer->Release();
			_sky._vertexBuffer = NULL;
		}

		// 天頂部分メッシュの解放
		if (_skyTop._indexBuffer != NULL)
		{
			_skyTop._indexBuffer->Release();
			_skyTop._indexBuffer = NULL;
		}

		if (_skyTop._vertexBuffer != NULL)
		{
			_skyTop._vertexBuffer->Release();
			_skyTop._vertexBuffer = NULL;
		}
	}

private:
	SkyMesh							_sky;
	SkyMesh							_skyTop;
	DirectXAPI*						_api;
	bool							_transParent;
	bool							_reverse;

	// Object を介して継承されました
	void Update(double deltaTime) override;
	void Draw() override;
	bool Discard() const override;
};

