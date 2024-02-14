//=============================================================================
//
// メッシュ空の処理 [meshsky.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"

class SkyBox
{
public:
	SkyBox();
	~SkyBox()
	{
		// 周回部分メッシュの解放
		if (_sky_IndexBuffer != NULL)
		{
			_sky_IndexBuffer->Release();
			_sky_IndexBuffer = NULL;
		}

		if (_sky_VertexBuffer != NULL)
		{
			_sky_VertexBuffer->Release();
			_sky_VertexBuffer = NULL;
		}

		// 天頂部分メッシュの解放
		if (_skyTop_IndexBuffer != NULL)
		{
			_skyTop_IndexBuffer->Release();
			_skyTop_IndexBuffer = NULL;
		}

		if (_skyTop_VertexBuffer != NULL)
		{
			_skyTop_VertexBuffer->Release();
			_skyTop_VertexBuffer = NULL;
		}
	}

private:
	ID3D11Buffer*			_sky_VertexBuffer;	// 頂点バッファ
	ID3D11Buffer*			_sky_IndexBuffer;	// インデックスバッファ
	ID3D11Buffer*			_skyTop_VertexBuffer;
	ID3D11Buffer*			_skyTop_IndexBuffer;	
	int						_numVertex;		//頂点数
	int						_numIndex;		//インデックス数
	MATERIAL				_material;
};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitMeshSky(D3DXVECTOR3 pos, D3DXVECTOR3 rot,
	float radius, int numBlockX, int numBlockZ, bool reverse = false);
void UninitMeshSky(void);
void UpdateMeshSky(void);
void DrawMeshSky(void);
