//=============================================================================
//
// ���b�V���n�ʂ̏��� [meshfield.cpp]
// Author : 
//
//=============================================================================
#include "input.h"
#include "texture.h"
#include "meshfield.h"
#include "DirectXAPI.h"

FieldMesh::FieldMesh(int texNo,DirectXAPI* api , D3DXVECTOR3 pos, D3DXVECTOR3 rot, int numBlockX, int numBlockZ, D3DXVECTOR2 size, World* world) :Object(texNo, "FieldMesh", world),_size(size),_api(api)
{
	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	_position = pos;
	_rotate = rot;
	_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	
	int yoko = numBlockX;
	int tate = numBlockZ;
	
	//�K�v�Ȓ��_���ƃC���f�b�N�X�����v�Z����
	_numVertex = (yoko + 1) * (tate + 1);
	_numIndex = (yoko + 1) * 2 * tate + (tate - 1) * 2;
	
	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * _numVertex;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	
	_api->GetDevice()->CreateBuffer(&bd, NULL, &_vertexBuffer);
	
	
	// �C���f�b�N�X�o�b�t�@����
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(unsigned short) * _numIndex;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	
	_api->GetDevice()->CreateBuffer(&bd, NULL, &_indexBuffer);
	
	{
	
		// ���_�o�b�t�@�ւ̃|�C���^���擾
		D3D11_MAPPED_SUBRESOURCE msr;
		_api->GetDeviceContext()->Map(_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	
		VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;
	
		for (int y = 0; y < (tate + 1); y++)
		{
			for (int x = 0; x < (yoko + 1); x++)
			{
				//�z��̃C���f�b�N�X���v�Z����
				int i = y * (yoko + 1) + x;
	
				// ���_���W�̐ݒ�
				pVtx[i].Position = D3DXVECTOR3(-(yoko / 2.0f) * _size.x + x * _size.x, 0.0f, (tate / 2.0f) * _size.y - y * _size.y);
				// UV�l�̐ݒ�
				pVtx[i].TexCoord = D3DXVECTOR2(x * 1.0f, y * 1.0f);
	
				// �@���̐ݒ�
				pVtx[i].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				// ���_�J���[�̐ݒ�
				pVtx[i].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
		}
		_api->GetDeviceContext()->Unmap(_vertexBuffer, 0);
	}
	
	{
	
		// �C���f�b�N�X�o�b�t�@�̃|�C���^���擾
		D3D11_MAPPED_SUBRESOURCE msr;
		_api->GetDeviceContext()->Map(_indexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	
		unsigned short *pIdx = (unsigned short*)msr.pData;
	
		int idx = 0;
	
		for (int y = 0; y < tate; y++)
		{
			//y�s�ڂ̃|���S���̃C���f�b�N�X
			for (int x = 0; x < (yoko + 1); x++)
			{
				pIdx[idx] = (yoko + 1) + x + (yoko + 1) * y;
				idx++;
				pIdx[idx] = 0 + x + (yoko + 1) * y;
				idx++;
			}
	
			//�k�ރ|���S�����̃C���f�b�N�X
			if (y < (tate - 1))
			{
				pIdx[idx] = yoko + (yoko + 1) * y;
				idx++;
				pIdx[idx] = (yoko + 1) * 2 + (yoko + 1) * y;
				idx++;
			}
		}
	
		_api->GetDeviceContext()->Unmap(_indexBuffer, 0);
	   }
	
	   //�}�e���A���̏�����
	   ZeroMemory(&_material1, sizeof(MATERIAL));
	   _material1.Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	   _material1.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	   _material1.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

void FieldMesh::Update(double deltaTime)
{
}

void FieldMesh::Draw()
{
	_api->SetCullingMode(CULL_MODE_BACK);
	
	_api->SetLightEnable(false);
	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	_api->GetDeviceContext()->IASetVertexBuffers(0, 1, &_vertexBuffer, &stride, &offset);

	// �C���f�b�N�X�o�b�t�@�ݒ�
	_api->GetDeviceContext()->IASetIndexBuffer(_indexBuffer, DXGI_FORMAT_R16_UINT, 0);

	// �v���~�e�B�u�g�|���W�ݒ�
	_api->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �}�e���A���ݒ�
	_api->SetMaterial(_material1);

	// �e�N�X�`���ݒ�
	_api->GetDeviceContext()->PSSetShaderResources(0, 1, TextureTool::Get()->GetTexture(_texNo));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&_worldMtx);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, _scale.x, _scale.y, _scale.z);
	D3DXMatrixMultiply(&_worldMtx, &_worldMtx, &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, _rotate.y, _rotate.x, _rotate.z);
	D3DXMatrixMultiply(&_worldMtx, &_worldMtx, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, _position.x, _position.y, _position.z);
	D3DXMatrixMultiply(&_worldMtx, &_worldMtx, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	_api->SetWorldMatrix(&_worldMtx);

	// �|���S���̕`��
	_api->GetDeviceContext()->DrawIndexed(_numIndex, 0, 0);
}

bool FieldMesh::Discard() const
{
	return false;
}
