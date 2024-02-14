//=============================================================================
//
// カメラ処理 [camera.h]
// Author : 
//
//=============================================================================
#pragma once
#include <d3dx9.h>
#include "object.h"
#include "DirectXAPI.h"
//*****************************************************************************
// マクロ定義
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

		// 視点と注視点の距離を計算
		float vx, vz;
		vx = _position.x - _at.x;
		vz = _position.z - _at.z;
		_len = sqrtf(vx * vx + vz * vz);;
	}
	~Camera(){}
	// ﾍｨｹ� Object ｼﾌｳﾐ
	void Update(double deltaTime) override;
	void Draw() override;
	bool Discard() const override;
	void SetCamera(DirectXAPI* api);
	void SetCameraAt(D3DXVECTOR3 position, bool sw);
	const D3DXMATRIX& GetViewMtx()const { return _mtxView; }
	const D3DXMATRIX& GetInvViewMtx()const { return _mtxInvView; }

private:
	D3DXVECTOR3					_at;				// カメラの注視点
	D3DXVECTOR3					_up;				// カメラの上方向ベクトル
	float						_len;			// カメラの視点と注視点の距離
	D3DXMATRIX					_mtxView;		// ビューマトリックス
	D3DXMATRIX					_mtxInvView;		// ビューマトリックス
	D3DXMATRIX					_mtxProjection;
};
