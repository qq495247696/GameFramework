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
// マクロ定義
//*****************************************************************************
#define	position_X_CAM		(0.0f)			// カメラの初期位置(X座標)
#define	position_Y_CAM		(100.0f)		// カメラの初期位置(Y座標)
#define	position_Z_CAM		(-400.0f)		// カメラの初期位置(Z座標)

#define	VIEW_ANGLE		(D3DXToRadian(45.0f))							// ビュー平面の視野角
#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// ビュー平面のアスペクト比	
#define	VIEW_NEAR_Z		(0.1f)											// ビュー平面のNearZ値
#define	VIEW_FAR_Z		(20000.0f)										// ビュー平面のFarZ値

#define	VALUE_MOVE_CAMERA	(20.0f)										// カメラの移動量
#define	VALUE_rotateATE_CAMERA	(D3DX_PI * 0.01f)							// カメラの回転量

void Camera::Update(double deltaTime)
{
	if (GetKeyboardPress(DIK_Z))
	{// 視点旋回「左」
		_rotate.y += VALUE_rotateATE_CAMERA;
		if (_rotate.y > D3DX_PI)
		{
			_rotate.y -= D3DX_PI * 2.0f;
		}

		_position.x = _at.x - sinf(_rotate.y) * _len;
		_position.z = _at.z - cosf(_rotate.y) * _len;
	}

	if (GetKeyboardPress(DIK_C))
	{// 視点旋回「右」
		_rotate.y -= VALUE_rotateATE_CAMERA;
		if (_rotate.y < -D3DX_PI)
		{
			_rotate.y += D3DX_PI * 2.0f;
		}

		_position.x = _at.x - sinf(_rotate.y) * _len;
		_position.z = _at.z - cosf(_rotate.y) * _len;
	}

	if (GetKeyboardPress(DIK_Y))
	{// 視点移動「上」
		_position.y += VALUE_MOVE_CAMERA;
	}

	if (GetKeyboardPress(DIK_N))
	{// 視点移動「下」
		_position.y -= VALUE_MOVE_CAMERA;
	}

	if (GetKeyboardPress(DIK_Q))
	{// 注視点旋回「左」
		_rotate.y -= VALUE_rotateATE_CAMERA;
		if (_rotate.y < -D3DX_PI)
		{
			_rotate.y += D3DX_PI * 2.0f;
		}

		_at.x = _position.x + sinf(_rotate.y) * _len;
		_at.z = _position.z + cosf(_rotate.y) * _len;
	}

	if (GetKeyboardPress(DIK_E))
	{// 注視点旋回「右」
		_rotate.y += VALUE_rotateATE_CAMERA;
		if (_rotate.y > D3DX_PI)
		{
			_rotate.y -= D3DX_PI * 2.0f;
		}

		_at.x = _position.x + sinf(_rotate.y) * _len;
		_at.z = _position.z + cosf(_rotate.y) * _len;
	}

	if (GetKeyboardPress(DIK_T))
	{// 注視点移動「上」
		_at.y += VALUE_MOVE_CAMERA;
	}

	if (GetKeyboardPress(DIK_B))
	{// 注視点移動「下」
		_at.y -= VALUE_MOVE_CAMERA;
	}

	if (GetKeyboardPress(DIK_U))
	{// 近づく
		_len -= VALUE_MOVE_CAMERA;
		_position.x = _at.x - sinf(_rotate.y) * _len;
		_position.z = _at.z - cosf(_rotate.y) * _len;
	}

	if (GetKeyboardPress(DIK_M))
	{// 離れる
		_len += VALUE_MOVE_CAMERA;
		_position.x = _at.x - sinf(_rotate.y) * _len;
		_position.z = _at.z - cosf(_rotate.y) * _len;
	}

	// カメラを初期に戻す
	if (GetKeyboardPress(DIK_P))
	{
		_position = D3DXVECTOR3(0, 0, -100);
		_at = D3DXVECTOR3(0.0f, 100.0f, 0.0f);
		_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		_rotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// 視点と注視点の距離を計算
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
