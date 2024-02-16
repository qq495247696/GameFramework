//=============================================================================
//
// ƒJƒƒ‰ˆ— [camera.h]
// Author : 
//
//=============================================================================
#pragma once
#include <d3dx9.h>
#include "object.h"
#include "DirectXAPI.h"
//*****************************************************************************
// ƒ}ƒNƒ’è‹`
//*****************************************************************************
class Camera:public  Object
{
public:
	Camera(World* world) :Object( "Camera",world)
	{
		_position = D3DXVECTOR3(0, 150.0f, -400);
		_at = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		_rotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// ‹“_‚Æ’‹“_‚Ì‹——£‚ğŒvZ
		float vx, vz;
		vx = _position.x - _at.x;
		vz = _position.z - _at.z;
		_len = sqrtf(vx * vx + vz * vz);;
	}
	~Camera(){}
	// Í¨¹ı Object ¼Ì³Ğ
	void Update(double deltaTime) override;
	void Draw() override;
	bool Discard() const override;
	void SetCamera(DirectXAPI* api);
	void SetCameraAt(D3DXVECTOR3 position, bool sw);
	const D3DXMATRIX& GetViewMtx()const { return _mtxView; }
	const D3DXMATRIX& GetInvViewMtx()const { return _mtxInvView; }
	Vec3& ScreenToWorldPos(const D3DXVECTOR2& viewPos);
private:
	D3DXVECTOR3					_at;				// ƒJƒƒ‰‚Ì’‹“_
	D3DXVECTOR3					_up;				// ƒJƒƒ‰‚Ìã•ûŒüƒxƒNƒgƒ‹
	float						_len;			// ƒJƒƒ‰‚Ì‹“_‚Æ’‹“_‚Ì‹——£
	D3DXMATRIX					_mtxView;		// ƒrƒ…[ƒ}ƒgƒŠƒbƒNƒX
	D3DXMATRIX					_mtxInvView;		// ƒrƒ…[ƒ}ƒgƒŠƒbƒNƒX
	D3DXMATRIX					_mtxProjection;
};
