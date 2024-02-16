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


//=============================================================================
// 弾のパラメータをセット
//=============================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 dir)
{
	//		// 当たり判定用サイズを設定
	//		_size = D3DXVECTOR3(50.0f, 50.0f, 50.0f);

	//		// 影の設定
	//		_shadow = SetShadow(D3DXVECTOR3(_pos.x, 0.0f, _pos.z), 50.0f);
}


void Bullet::Update(double deltaTime)
{
	if (_use)
	{
		//消滅処理
		if (frame > 100.0f)
		{
			//_use = false;

			//影を消す
			//ReleaseShadow(_shadow);
		}

		//座標の更新
		_position += (_vel * _speed)*deltaTime;

		//影の座標を更新する
		//SetPositionShadow(_shadow, D3DXVECTOR3(_pos.x, 0.0f, _pos.z));

		//時間経過
		frame += 1.0f;
	}
}

void Bullet::Draw()
{
	// αテストを有効に
	_api->SetAlphaTestEnable(true);

	// ライティングを無効
	_api->SetLightEnable(false);

	D3DXMATRIX mtxView, mtxScale, mtxTranslate;

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	_api->GetDeviceContext()->IASetVertexBuffers(0, 1, &_vertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	_api->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	if (_use)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&_worldMtx);

		Camera* cam = GetWorld()->GetObjectWithTag<Camera>("Camera");

		// ポリゴンを正面に向ける
			// ビューマトリックスの逆行列を取得
		_worldMtx = cam->GetInvViewMtx();
		_worldMtx._41 = 0.0f;
		_worldMtx._42 = 0.0f;
		_worldMtx._43 = 0.0f;
		// ビューマトリックスを取得
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


		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, _position.x,
			_position.y,
			_position.z);
		D3DXMatrixMultiply(&_worldMtx, &_worldMtx, &mtxTranslate);

		// ワールドマトリックスの設定
		_api->SetWorldMatrix(&_worldMtx);

		// マテリアル設定
		_api->SetMaterial(_material);

		// テクスチャ設定
		_api->GetDeviceContext()->PSSetShaderResources(0, 1, TextureTool::Get()->GetTexture(_texNo));

		// ポリゴンの描画
		_api->GetDeviceContext()->Draw(4, 0);
	}
}

bool Bullet::Discard() const
{
	return false;
}
