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
// �o���b�g�\����
class Bullet:public Object
{
public:
	Bullet(const int texNo, DirectXAPI* api, World* world, Vec3 pos, Vec3 vel) :Object(texNo, "Bullet", world), _api(api), _attack(70)
	{
		// ���_�o�b�t�@����
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(VERTEX_3D) * 4;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		_api->GetDevice()->CreateBuffer(&bd, NULL, &_vertexBuffer);


		// ���_�o�b�t�@�ɒl���Z�b�g����
		{
			D3D11_MAPPED_SUBRESOURCE msr;
			_api->GetDeviceContext()->Map(_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

			VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

			float width = 50.0f;
			float height = 50.0f;

			// ���_���W�̐ݒ�
			vertex[0].Position = D3DXVECTOR3(-width / 2.0f, 0.0f, 0.0f);
			vertex[1].Position = D3DXVECTOR3(-width / 2.0f, height, 0.0f);
			vertex[2].Position = D3DXVECTOR3(width / 2.0f, 0.0f, 0.0f);
			vertex[3].Position = D3DXVECTOR3(width / 2.0f, height, 0.0f);

			// ���_�J���[�̐ݒ�
			vertex[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			vertex[0].TexCoord = D3DXVECTOR2(0.0f, 1.0f);
			vertex[1].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
			vertex[2].TexCoord = D3DXVECTOR2(1.0f, 1.0f);
			vertex[3].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

			_api->GetDeviceContext()->Unmap(_vertexBuffer, 0);
		}


		// �}�e���A��������
		ZeroMemory(&_material, sizeof(MATERIAL));
		_material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// ������
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
		{// ���_�o�b�t�@�̉��
			_vertexBuffer->Release();
			_vertexBuffer = NULL;
		}
	}
	float					frame;	// �t���[����
	D3DXVECTOR3				size;		// �����蔻��p�T�C�Y
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

