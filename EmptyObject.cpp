#include "EmptyObject.h"
#include "DirectXAPI.h"
#include "model.h"
void EmptyObject::Update(double deltaTime)
{
}

void EmptyObject::Draw()
{
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, oWorldMatrix;
	// ワールドマトリックスの初期化（単位行列を作る関数）
	D3DXMatrixIdentity(&_worldMtx);

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, _scale.x, _scale.y, _scale.z);
	D3DXMatrixMultiply(&_worldMtx, &_worldMtx, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, _rotate.y, _rotate.x, _rotate.z);
	D3DXMatrixMultiply(&_worldMtx, &_worldMtx, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, _position.x, _position.y, _position.z);
	D3DXMatrixMultiply(&_worldMtx, &_worldMtx, &mtxTranslate);

	// ワールドマトリックスの設定
	_api->SetWorldMatrix(&_worldMtx);
	DrawModel(_model,_api);
	
}

bool EmptyObject::Discard() const
{
	if (_use==false)
	{
		return true;
	}
	else
	{
		return false;
	}
}
