/*********************************************************************
 * \file   Render3D.cpp
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#include "Render3D.h"
#include "RenderInfo.h"
#include "object.h"
#include "model.h"
#include "DirectXAPI.h"

void Render3D::Draw(Object* object)
{
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate,oWorldMatrix;
	// ワールドマトリックスの初期化（単位行列を作る関数）
	D3DXMatrixIdentity(object->GetWorldMatrix());

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, object->GetScale().x, object->GetScale().y, object->GetScale().z);
	D3DXMatrixMultiply(object->GetWorldMatrix(), object->GetWorldMatrix(), &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, object->GetRotation().y, object->GetRotation().x, object->GetRotation().z);
	D3DXMatrixMultiply(object->GetWorldMatrix(), object->GetWorldMatrix(), &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, object->GetPosition().x, object->GetPosition().y, object->GetPosition().z);
	D3DXMatrixMultiply(object->GetWorldMatrix(), object->GetWorldMatrix(), &mtxTranslate);
	
	// ワールドマトリックスの設定
	_dApi->SetWorldMatrix(object->GetWorldMatrix());


	DrawModel(object->GetModel(), _dApi);
}
