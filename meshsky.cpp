/*********************************************************************
 * \file   meshsky.cpp
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#include "meshsky.h"
#include "Texture.h"
#include "input.h"
#include "DirectXAPI.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	SKY_HEIGHT_RATE			(2.0f)		// 空ドームの高さ係数
#define	TEX_COUNT_LOOP			(1)			// テクスチャの繰り返し回数


SkyBox::SkyBox(int texNo, DirectXAPI* api, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float radius, int numBlockH, int numBlockV, World* world, bool reverse):
	Object(texNo,"SkyBox",world),_api(api),_reverse(reverse), _transParent(false)
{
	ComPtr<ID3D11Device> pDevice =api->GetDevice();
	// ポリゴン表示位置の中心座標を設定
	_sky._pos = pos;
	_sky._rot = rot;
	_skyTop._pos = pos;
	_skyTop._rot = rot;


	// テクスチャの読み込み

	//マテリアルの初期化
	ZeroMemory(&_sky._material, sizeof(MATERIAL));
	_sky._material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	ZeroMemory(&_skyTop._material, sizeof(MATERIAL));
	_skyTop._material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// 頂点数の設定
	_sky._numVertex = (numBlockH + 1) * (numBlockV + 1);
	_skyTop._numVertex = numBlockH + 1;

	// インデックス数の設定
	_sky._numIndex = (numBlockH * (numBlockV * 2) + numBlockV * 2 + (numBlockV - 1) * 2);
	_skyTop._numIndex = numBlockH * 3;

	// 一時頂点配列を生成
	VERTEX_3D* pVertexWk = new VERTEX_3D[_sky._numVertex];
	VERTEX_3D* pVertexTopWk = new VERTEX_3D[_skyTop._numVertex];

	// 一時インデックス配列を生成
	int* pIndexWk = new int[_sky._numIndex];
	int* pIndexTopWk = new int[_skyTop._numIndex];

	// 頂点配列の中身を埋める
	VERTEX_3D* pVtx = pVertexWk;
	const float ANGLE_H = (D3DX_PI * 2) / numBlockH;
	const float ANGLE_V = (D3DX_PI / 8) / (numBlockV + 1);
	const float WIDTH = 1.0f / numBlockH;
	const float HEIGHT = 1.0f / numBlockV;
	float lengthXZ;

	for (int vt = 0; vt < (numBlockV + 1); vt++) {
		lengthXZ = cosf(ANGLE_V * vt) * radius;

		for (int hr = 0; hr < (numBlockH + 1); hr++) {
			// 頂点座標の設定
			pVtx->Position.x = sinf(ANGLE_H * hr) * lengthXZ;
			if (_reverse) {
				pVtx->Position.y = -sinf(ANGLE_V * vt) * radius * SKY_HEIGHT_RATE;
			} else {
				pVtx->Position.y = sinf(ANGLE_V * vt) * radius * SKY_HEIGHT_RATE;
			}
			pVtx->Position.z = cosf(ANGLE_H * hr) * lengthXZ;

			// 法線の設定
			pVtx->Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// 反射光の設定
			if (_reverse) {
				pVtx->Diffuse = D3DXCOLOR(0.0625f, 0.0625f, 0.375f, 0.5f);
			} else {
				pVtx->Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}

			// テクスチャ座標の設定
			pVtx->TexCoord.x = hr * WIDTH * TEX_COUNT_LOOP;
			if (vt == numBlockV) {
				pVtx->TexCoord.y = 0.01f;
			} else {
				pVtx->TexCoord.y = 1.0f - vt * HEIGHT;
			}

			pVtx++;
		}
	}

	pVtx = pVertexTopWk;

	// 頂点座標の設定
	pVtx->Position.x = 0.0f;
	if (_reverse) {
		pVtx->Position.y = -sinf(ANGLE_V * (numBlockV + 1)) * radius * SKY_HEIGHT_RATE;
	} else {
		pVtx->Position.y = sinf(ANGLE_V * (numBlockV + 1)) * radius * SKY_HEIGHT_RATE;
	}
	pVtx->Position.z = 0.0f;

	// 法線の設定
	pVtx->Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// 頂点カラーの設定
	if (_reverse) {
		pVtx->Diffuse = D3DXCOLOR(0.0675f, 0.0675f, 0.375f, 0.5f);
	} else {
		pVtx->Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	// テクスチャ座標の設定
	pVtx->TexCoord.x = 0.01f;
	pVtx->TexCoord.y = 0.01f;

	pVtx++;

	lengthXZ = cosf(ANGLE_V * numBlockV) * radius;
	for (int hr = 0; hr < numBlockH; hr++ ) {
		// 頂点座標の設定
		pVtx->Position.x = -sinf(ANGLE_H * hr) * lengthXZ;
		if (_reverse) {
			pVtx->Position.y = -sinf(ANGLE_V * numBlockV) * radius * SKY_HEIGHT_RATE;
		} else {
			pVtx->Position.y = sinf(ANGLE_V * numBlockV) * radius * SKY_HEIGHT_RATE;
		}
		pVtx->Position.z = cosf(ANGLE_H * hr) * lengthXZ;

		// 法線の設定
		pVtx->Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// 頂点カラーの設定
		if (_reverse) {
			pVtx->Diffuse = D3DXCOLOR(0.0675f, 0.0675f, 0.375f, 0.5f);
		} else {
			pVtx->Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}

		// テクスチャ座標の設定
		pVtx->TexCoord.x = 0.01f;
		pVtx->TexCoord.y = 0.01f;

		pVtx++;
	}

	// インデックス配列の中身を埋める
	int* pIdx = pIndexWk;

	for (int vt = 0; vt < numBlockV; vt++) {
		if (vt != 0) {
			*pIdx = vt * (numBlockH + 1);
			pIdx++;
		}

		for (int hr = 0; hr < numBlockH + 1; hr++) {
			*pIdx = vt * (numBlockH + 1) + hr;
			pIdx++;

			*pIdx = (vt + 1) * (numBlockH + 1) + hr;
			pIdx++;
		}

		if (vt != (numBlockV - 1)) {
			*pIdx = (vt + 1) * (numBlockH + 1);
			pIdx++;
		}
	}

	pIdx = pIndexTopWk;
	for (int hr = 1; hr < numBlockH + 1; hr++) {
		*pIdx = 0;
		++pIdx;
		*pIdx = hr;
		++pIdx;
		if (hr < numBlockH) {
			*pIdx = hr + 1;
		} else {
			*pIdx = 1;
		}
		++pIdx;
	}

	//周回部分の頂点バッファ・インデックスバッファ作成
	{
		// 頂点バッファ生成
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(VERTEX_3D) * _sky._numVertex;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = pVertexWk;

		_api->GetDevice()->CreateBuffer(&bd, &sd, &_sky._vertexBuffer);

		// インデックスバッファ生成
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(int) * _sky._numIndex;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = pIndexWk;

		_api->GetDevice()->CreateBuffer(&bd, &sd, &_sky._indexBuffer);
	}

	//天頂部分の頂点バッファ・インデックスバッファ作成
	{
		// 頂点バッファ生成
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(VERTEX_3D) * _skyTop._numVertex;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = pVertexTopWk;

		_api->GetDevice()->CreateBuffer(&bd, &sd, &_skyTop._vertexBuffer);

		// インデックスバッファ生成
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(int) * _skyTop._numIndex;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = pIndexTopWk;

		_api->GetDevice()->CreateBuffer(&bd, &sd, &_skyTop._indexBuffer);
	}

	// 一時配列を解放
	delete[] pIndexTopWk;
	delete[] pIndexWk;
	delete[] pVertexTopWk;
	delete[] pVertexWk;
}

void SkyBox::Update(double deltaTime)
{
}

void SkyBox::Draw()
{
	if (_reverse) 
	{
		_api->SetCullingMode(CULL_MODE_FRONT);	// 前面カリング
	}
	else 
	{
		_api->SetCullingMode(CULL_MODE_BACK);		// 背面カリング
	}

	// テクスチャ設定
	_api->GetDeviceContext()->PSSetShaderResources(0, 1,TextureTool::Get()-> GetTexture(_texNo));

	//周回部分の描画
	{
		// 頂点バッファ設定
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		_api->GetDeviceContext()->IASetVertexBuffers(0, 1, &_sky._vertexBuffer, &stride, &offset);

		// インデックスバッファ設定
		_api->GetDeviceContext()->IASetIndexBuffer(_sky._indexBuffer, DXGI_FORMAT_R32_UINT, 0);

		// プリミティブトポロジ設定
		_api->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		// マテリアル設定
		_api->SetMaterial(_sky._material);


		D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&_sky._mtxWorld);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, _sky._rot.y, _sky._rot.x, _sky._rot.z);
		D3DXMatrixMultiply(&_sky._mtxWorld, &_sky._mtxWorld, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, _sky._pos.x, _sky._pos.y, _sky._pos.z);
		D3DXMatrixMultiply(&_sky._mtxWorld, &_sky._mtxWorld, &mtxTranslate);

		// ワールドマトリックスの設定
		_api->SetWorldMatrix(&_sky._mtxWorld);

		// ポリゴンの描画
		_api->GetDeviceContext()->DrawIndexed(_sky._numIndex, 0, 0);
	}

	//天頂部分の描画
	{
		// 頂点バッファ設定
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		_api->GetDeviceContext()->IASetVertexBuffers(0, 1, &_skyTop._vertexBuffer, &stride, &offset);

		// インデックスバッファ設定
		_api->GetDeviceContext()->IASetIndexBuffer(_skyTop._indexBuffer, DXGI_FORMAT_R32_UINT, 0);

		// プリミティブトポロジ設定
		_api->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// マテリアル設定
		_api->SetMaterial(_skyTop._material);


		D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&_skyTop._mtxWorld);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, _skyTop._rot.y, _skyTop._rot.x, _skyTop._rot.z);
		D3DXMatrixMultiply(&_skyTop._mtxWorld, &_skyTop._mtxWorld, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, _skyTop._pos.x, _skyTop._pos.y, _skyTop._pos.z);
		D3DXMatrixMultiply(&_skyTop._mtxWorld, &_skyTop._mtxWorld, &mtxTranslate);

		// ワールドマトリックスの設定
		_api->SetWorldMatrix(&_skyTop._mtxWorld);

		// ポリゴンの描画
		_api->GetDeviceContext()->DrawIndexed(_skyTop._numIndex, 0, 0);
	}

	_api->SetCullingMode(CULL_MODE_BACK);		// 背面カリング
}

bool SkyBox::Discard() const
{
	return false;
}
