//=============================================================================
//
// �J�������� [camera.h]
// Author : 
//
//=============================================================================
#pragma once
#include <d3dx9.h>
#include "render.h"
#include "object.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
class Camera:public  Object
{
public:
	Camera(World* world) :Object( "Camera",world)
	{
		_position = D3DXVECTOR3(0, 50.0f, -100);
		_at = D3DXVECTOR3(0.0f, 50.0f, 100.0f);
		_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		_rotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// ���_�ƒ����_�̋������v�Z
		float vx, vz;
		vx = _position.x - _at.x;
		vz = _position.z - _at.z;
		_len = sqrtf(vx * vx + vz * vz);;
	}
	~Camera(){}
	// ͨ�� Object �̳�
	void Update(double deltaTime) override;
	void Draw() override;
	bool Discard() const override;
	void SetCamera(DirectXAPI* api);
	void SetCameraAt(D3DXVECTOR3 position, bool sw);
private:
	D3DXVECTOR3					_at;				// �J�����̒����_
	D3DXVECTOR3					_up;				// �J�����̏�����x�N�g��
	float						_len;			// �J�����̎��_�ƒ����_�̋���
	D3DXMATRIX					_mtxView;		// �r���[�}�g���b�N�X
	D3DXMATRIX					_mtxInvView;		// �r���[�}�g���b�N�X
	D3DXMATRIX					_mtxProjection;
};