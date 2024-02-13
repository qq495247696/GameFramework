//=============================================================================
//
// �e���� [bullet.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"
#include "render.h"
#include "object.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BULLET_NUM		(10)		// �o���b�g��Max��
#define BULLET_SPEED	(10.0f)		// �o���b�g�̈ړ��X�s�[�h


// �o���b�g�\����
class Bullet:public Object
{
public:
	Bullet(const int texNo,DirectXAPI* api ,Render* render,World* world) :Object(texNo,"Bullet",world),_api(api)
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
		_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		_vel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		size = D3DXVECTOR3(50.0f, 50.0f, 50.0f);
		_use = false;
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
	int						shadow;	// �e�̎��ʔԍ�
	D3DXVECTOR3     size;		// �����蔻��p�T�C�Y
	ID3D11Buffer*	_vertexBuffer;


	void Update(double deltaTime) override;
	void Draw() override;
	bool Discard() const override;
private:
	DirectXAPI*					_api;
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

Bullet *GetBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 dir);

