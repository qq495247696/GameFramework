/*********************************************************************
 * \file   meshfield.h
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#pragma once
#include "object.h"
class DirectXAPI;
class FieldMesh:public Object
{
public:
	FieldMesh(int texNo, DirectXAPI* api ,D3DXVECTOR3 pos, D3DXVECTOR3 rot, int numBlockX, int numBlockZ, D3DXVECTOR2 size,World *world);
	~FieldMesh()
	{
		//インデックスバッファの解放
		if (_indexBuffer != NULL)
		{
			_indexBuffer->Release();
			_indexBuffer = NULL;
		}

		//頂点バッファの解放
		if (_vertexBuffer != NULL)
		{
			_vertexBuffer->Release();
			_vertexBuffer = NULL;
		}
	}

	// ﾍｨｹ� Object ｼﾌｳﾐ
	void Update(double deltaTime) override;
	void Draw() override;
	bool Discard() const override;

	ID3D11Buffer*		 _vertexBuffer;	//頂点バッファ
	ID3D11Buffer*		 _indexBuffer;	//インデックスバッフ
private:
	D3DXVECTOR2			_size;
	int					_numVertex;		//頂点数
	int					_numIndex;		//インデックス数
	MATERIAL			_material1;
	DirectXAPI* _api;
};
