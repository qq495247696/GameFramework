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
	ID3D11Buffer*				_vertexBuffer;	// ���_�o�b�t�@
	ID3D11Buffer*				_indexBuffer;	// �C���f�b�N�X�o�b�t�@
	int							_numVertex;		//���_��
	int							_numIndex;		//�C���f�b�N�X
	D3DXMATRIX					_mtxWorld;
};


class SkyBox:public Object
{
public:
	SkyBox(int texNo,DirectXAPI* api,D3DXVECTOR3 pos, D3DXVECTOR3 rot,
		float radius, int numBlockX, int numBlockZ,World* world,bool reverse = false);
	~SkyBox()
	{
		// ���񕔕����b�V���̉��
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

		// �V���������b�V���̉��
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

	// Object ����Čp������܂���
	void Update(double deltaTime) override;
	void Draw() override;
	bool Discard() const override;
};

