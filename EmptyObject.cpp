#include "EmptyObject.h"
#include "DirectXAPI.h"
#include "model.h"
void EmptyObject::Update(double deltaTime)
{
}

void EmptyObject::Draw()
{
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, oWorldMatrix;
	// ���[���h�}�g���b�N�X�̏������i�P�ʍs������֐��j
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
