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
		//�C���f�b�N�X�o�b�t�@�̉��
		if (_indexBuffer != NULL)
		{
			_indexBuffer->Release();
			_indexBuffer = NULL;
		}

		//���_�o�b�t�@�̉��
		if (_vertexBuffer != NULL)
		{
			_vertexBuffer->Release();
			_vertexBuffer = NULL;
		}
	}

	// ͨ�� Object �̳�
	void Update(double deltaTime) override;
	void Draw() override;
	bool Discard() const override;

	ID3D11Buffer*		 _vertexBuffer;	//���_�o�b�t�@
	ID3D11Buffer*		 _indexBuffer;	//�C���f�b�N�X�o�b�t
private:
	D3DXVECTOR2			_size;
	int					_numVertex;		//���_��
	int					_numIndex;		//�C���f�b�N�X��
	MATERIAL			_material1;
	DirectXAPI* _api;
};
