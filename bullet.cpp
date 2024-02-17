/*********************************************************************
 * \file   bullet.cpp
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#include "bullet.h"
#include "camera.h"
#include "texture.h"
#include "shadow.h"
#include "World.h"
#include "main.h"



void Bullet::Update(double deltaTime)
{

	//���W�̍X�V
	_position += (_vel * _speed)*deltaTime;
	//�e�̍��W���X�V����
	//SetPositionShadow(_shadow, D3DXVECTOR3(_pos.x, 0.0f, _pos.z));
	
	//���Ԍo��
	frame += 1.0f;
	
}

void Bullet::Draw()
{
	// ���e�X�g��L����
	_api->SetAlphaTestEnable(true);

	// ���C�e�B���O�𖳌�
	_api->SetLightEnable(false);

	D3DXMATRIX mtxView, mtxScale, mtxTranslate;

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	_api->GetDeviceContext()->IASetVertexBuffers(0, 1, &_vertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	_api->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);



	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&_worldMtx);

	Camera* cam = GetWorld()->GetObjectWithTag<Camera>("Camera");

	// �|���S���𐳖ʂɌ�����
		// �r���[�}�g���b�N�X�̋t�s����擾
	_worldMtx = cam->GetInvViewMtx();
	_worldMtx._41 = 0.0f;
	_worldMtx._42 = 0.0f;
	_worldMtx._43 = 0.0f;
	// �r���[�}�g���b�N�X���擾
	D3DXMATRIX mtxView = cam->GetViewMtx();

	_worldMtx._11 = mtxView._11;
	_worldMtx._12 = mtxView._21;
	_worldMtx._13 = mtxView._31;
	_worldMtx._21 = mtxView._12;
	_worldMtx._22 = mtxView._22;
	_worldMtx._23 = mtxView._32;
	_worldMtx._31 = mtxView._13;
	_worldMtx._32 = mtxView._23;
	_worldMtx._33 = mtxView._33;


	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, _position.x,
		_position.y,
		_position.z);
	D3DXMatrixMultiply(&_worldMtx, &_worldMtx, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	_api->SetWorldMatrix(&_worldMtx);

	// �}�e���A���ݒ�
	_api->SetMaterial(_material);

	// �e�N�X�`���ݒ�
	_api->GetDeviceContext()->PSSetShaderResources(0, 1, TextureTool::Get()->GetTexture(_texNo));

	// �|���S���̕`��
	_api->GetDeviceContext()->Draw(4, 0);
	
}

bool Bullet::Discard() const
{
	return frame > 150.0f;
}
