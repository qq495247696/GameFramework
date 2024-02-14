//=============================================================================
//
// ���b�V����̏��� [meshsky.h]
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
		// ���񕔕����b�V���̉��
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

		// �V���������b�V���̉��
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
	ID3D11Buffer*			_sky_VertexBuffer;	// ���_�o�b�t�@
	ID3D11Buffer*			_sky_IndexBuffer;	// �C���f�b�N�X�o�b�t�@
	ID3D11Buffer*			_skyTop_VertexBuffer;
	ID3D11Buffer*			_skyTop_IndexBuffer;	
	int						_numVertex;		//���_��
	int						_numIndex;		//�C���f�b�N�X��
	MATERIAL				_material;
};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitMeshSky(D3DXVECTOR3 pos, D3DXVECTOR3 rot,
	float radius, int numBlockX, int numBlockZ, bool reverse = false);
void UninitMeshSky(void);
void UpdateMeshSky(void);
void DrawMeshSky(void);
