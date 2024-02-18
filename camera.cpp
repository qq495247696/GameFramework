/*********************************************************************
 * \file   camera.cpp
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 18
 *********************************************************************/
#include "input.h"
#include "camera.h"
#include "DirectXAPI.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	position_X_CAM		(0.0f)			// �J�����̏����ʒu(X���W)
#define	position_Y_CAM		(100.0f)		// �J�����̏����ʒu(Y���W)
#define	position_Z_CAM		(-400.0f)		// �J�����̏����ʒu(Z���W)

#define	VIEW_ANGLE		(D3DXToRadian(45.0f))							// �r���[���ʂ̎���p
#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// �r���[���ʂ̃A�X�y�N�g��	
#define	VIEW_NEAR_Z		(0.1f)											// �r���[���ʂ�NearZ�l
#define	VIEW_FAR_Z		(20000.0f)										// �r���[���ʂ�FarZ�l

#define	VALUE_MOVE_CAMERA	(20.0f)										// �J�����̈ړ���
#define	VALUE_rotateATE_CAMERA	(D3DX_PI * 0.01f)							// �J�����̉�]��

void Camera::Update(double deltaTime)
{
	if (GetKeyboardPress(DIK_Z))
	{// ���_����u���v
		_rotate.y += VALUE_rotateATE_CAMERA;
		if (_rotate.y > D3DX_PI)
		{
			_rotate.y -= D3DX_PI * 2.0f;
		}

		_position.x = _at.x - sinf(_rotate.y) * _len;
		_position.z = _at.z - cosf(_rotate.y) * _len;
	}

	if (GetKeyboardPress(DIK_C))
	{// ���_����u�E�v
		_rotate.y -= VALUE_rotateATE_CAMERA;
		if (_rotate.y < -D3DX_PI)
		{
			_rotate.y += D3DX_PI * 2.0f;
		}

		_position.x = _at.x - sinf(_rotate.y) * _len;
		_position.z = _at.z - cosf(_rotate.y) * _len;
	}

	if (GetKeyboardPress(DIK_Y))
	{// ���_�ړ��u��v
		_position.y += VALUE_MOVE_CAMERA;
	}

	if (GetKeyboardPress(DIK_N))
	{// ���_�ړ��u���v
		_position.y -= VALUE_MOVE_CAMERA;
	}

	if (GetKeyboardPress(DIK_Q))
	{// �����_����u���v
		_rotate.y -= VALUE_rotateATE_CAMERA;
		if (_rotate.y < -D3DX_PI)
		{
			_rotate.y += D3DX_PI * 2.0f;
		}

		_at.x = _position.x + sinf(_rotate.y) * _len;
		_at.z = _position.z + cosf(_rotate.y) * _len;
	}

	if (GetKeyboardPress(DIK_E))
	{// �����_����u�E�v
		_rotate.y += VALUE_rotateATE_CAMERA;
		if (_rotate.y > D3DX_PI)
		{
			_rotate.y -= D3DX_PI * 2.0f;
		}

		_at.x = _position.x + sinf(_rotate.y) * _len;
		_at.z = _position.z + cosf(_rotate.y) * _len;
	}

	if (GetKeyboardPress(DIK_T))
	{// �����_�ړ��u��v
		_at.y += VALUE_MOVE_CAMERA;
	}

	if (GetKeyboardPress(DIK_B))
	{// �����_�ړ��u���v
		_at.y -= VALUE_MOVE_CAMERA;
	}

	if (GetKeyboardPress(DIK_U))
	{// �߂Â�
		_len -= VALUE_MOVE_CAMERA;
		_position.x = _at.x - sinf(_rotate.y) * _len;
		_position.z = _at.z - cosf(_rotate.y) * _len;
	}

	if (GetKeyboardPress(DIK_M))
	{// �����
		_len += VALUE_MOVE_CAMERA;
		_position.x = _at.x - sinf(_rotate.y) * _len;
		_position.z = _at.z - cosf(_rotate.y) * _len;
	}

	// �J�����������ɖ߂�
	if (GetKeyboardPress(DIK_P))
	{
		_position = D3DXVECTOR3(0, 0, -100);
		_at = D3DXVECTOR3(0.0f, 100.0f, 0.0f);
		_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		_rotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// ���_�ƒ����_�̋������v�Z
		float vx, vz;
		vx = _position.x - _at.x;
		vz = _position.z - _at.z;
		_len = sqrtf(vx * vx + vz * vz);;
	}
}

void Camera::Draw()
{
	
}

bool Camera::Discard() const
{
	return false;
}

void Camera::SetCamera(DirectXAPI* api)
{
	D3DXMatrixLookAtLH(&_mtxView, &_position, &_at, &_up);
	api->SetViewMatrix(&_mtxView);
	float det;  
	D3DXMatrixInverse(&_mtxInvView, &det, &_mtxView);
	D3DXMatrixPerspectiveFovLH(&_mtxProjection, 1.0f, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, VIEW_NEAR_Z, VIEW_FAR_Z);
	api ->SetProjectionMatrix(&_mtxProjection);
}

void Camera::SetCameraAt(D3DXVECTOR3 position, bool sw)
{
	_at = position;

	if (sw)
	{
		_position.x = _at.x - sinf(_rotate.y) * _len;
		_position.z = _at.z - cosf(_rotate.y) * _len;
	}
}

Vec3& Camera::ScreenToWorldPos(const D3DXVECTOR2& viewPos)
{
	float x = (2.0f * viewPos.x) / 1920 - 1.0f;
	float y = 1.0f - (2.0 * viewPos.y) / 1080;
	D3DXVECTOR4 ndc = D3DXVECTOR4(x,y,1.0f,1.0f);

	D3DXMATRIX	invProjMtx;
	D3DXMatrixInverse(&invProjMtx, NULL, &_mtxProjection);
	D3DXVECTOR4 viewSpace;
	D3DXVec4Transform(&viewSpace, &ndc, &invProjMtx);

	D3DXMATRIX invVeiwMatrix;
	D3DXMatrixInverse(&invVeiwMatrix, NULL, &_mtxView);
	D3DXVECTOR4 worldSpace;
	D3DXVec4Transform(&worldSpace, &viewSpace, &invVeiwMatrix);


	Vec3 worldPos = { worldSpace.x,worldSpace.y,worldSpace.z };
	return worldPos;
}
