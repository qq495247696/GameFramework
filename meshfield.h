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
		//ƒCƒ“ƒfƒbƒNƒXƒoƒbƒtƒ@‚Ì‰ğ•ú
		if (_indexBuffer != NULL)
		{
			_indexBuffer->Release();
			_indexBuffer = NULL;
		}

		//’¸“_ƒoƒbƒtƒ@‚Ì‰ğ•ú
		if (_vertexBuffer != NULL)
		{
			_vertexBuffer->Release();
			_vertexBuffer = NULL;
		}
	}

	// Í¨¹ı Object ¼Ì³Ğ
	void Update(double deltaTime) override;
	void Draw() override;
	bool Discard() const override;

	ID3D11Buffer*		 _vertexBuffer;	//’¸“_ƒoƒbƒtƒ@
	ID3D11Buffer*		 _indexBuffer;	//ƒCƒ“ƒfƒbƒNƒXƒoƒbƒt
private:
	D3DXVECTOR2			_size;
	int					_numVertex;		//’¸“_”
	int					_numIndex;		//ƒCƒ“ƒfƒbƒNƒX”
	MATERIAL			_material1;
	DirectXAPI* _api;
};
