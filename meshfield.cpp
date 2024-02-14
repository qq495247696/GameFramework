//=============================================================================
//
// メッシュ地面の処理 [meshfield.cpp]
// Author : 
//
//=============================================================================
#include "input.h"
#include "texture.h"
#include "meshfield.h"
#include "DirectXAPI.h"

FieldMesh::FieldMesh(int texNo,DirectXAPI* api , D3DXVECTOR3 pos, D3DXVECTOR3 rot, int numBlockX, int numBlockZ, D3DXVECTOR2 size, World* world) :Object(texNo, "FieldMesh", world),_size(size),_api(api)
{
	// 位置・回転・スケールの初期設定
	_position = pos;
	_rotate = rot;
	_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	
	int yoko = numBlockX;
	int tate = numBlockZ;
	
	//必要な頂点数とインデックス数を計算する
	_numVertex = (yoko + 1) * (tate + 1);
	_numIndex = (yoko + 1) * 2 * tate + (tate - 1) * 2;
	
	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * _numVertex;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	
	_api->GetDevice()->CreateBuffer(&bd, NULL, &_vertexBuffer);
	
	
	// インデックスバッファ生成
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(unsigned short) * _numIndex;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	
	_api->GetDevice()->CreateBuffer(&bd, NULL, &_indexBuffer);
	
	{
	
		// 頂点バッファへのポインタを取得
		D3D11_MAPPED_SUBRESOURCE msr;
		_api->GetDeviceContext()->Map(_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	
		VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;
	
		for (int y = 0; y < (tate + 1); y++)
		{
			for (int x = 0; x < (yoko + 1); x++)
			{
				//配列のインデックスを計算する
				int i = y * (yoko + 1) + x;
	
				// 頂点座標の設定
				pVtx[i].Position = D3DXVECTOR3(-(yoko / 2.0f) * _size.x + x * _size.x, 0.0f, (tate / 2.0f) * _size.y - y * _size.y);
				// UV値の設定
				pVtx[i].TexCoord = D3DXVECTOR2(x * 1.0f, y * 1.0f);
	
				// 法線の設定
				pVtx[i].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				// 頂点カラーの設定
				pVtx[i].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
		}
		_api->GetDeviceContext()->Unmap(_vertexBuffer, 0);
	}
	
	{
	
		// インデックスバッファのポインタを取得
		D3D11_MAPPED_SUBRESOURCE msr;
		_api->GetDeviceContext()->Map(_indexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	
		unsigned short *pIdx = (unsigned short*)msr.pData;
	
		int idx = 0;
	
		for (int y = 0; y < tate; y++)
		{
			//y行目のポリゴンのインデックス
			for (int x = 0; x < (yoko + 1); x++)
			{
				pIdx[idx] = (yoko + 1) + x + (yoko + 1) * y;
				idx++;
				pIdx[idx] = 0 + x + (yoko + 1) * y;
				idx++;
			}
	
			//縮退ポリゴン分のインデックス
			if (y < (tate - 1))
			{
				pIdx[idx] = yoko + (yoko + 1) * y;
				idx++;
				pIdx[idx] = (yoko + 1) * 2 + (yoko + 1) * y;
				idx++;
			}
		}
	
		_api->GetDeviceContext()->Unmap(_indexBuffer, 0);
	   }
	
	   //マテリアルの初期化
	   ZeroMemory(&_material1, sizeof(MATERIAL));
	   _material1.Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	   _material1.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	   _material1.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

void FieldMesh::Update(double deltaTime)
{
}

void FieldMesh::Draw()
{
	_api->SetCullingMode(CULL_MODE_BACK);
	
	_api->SetLightEnable(false);
	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	_api->GetDeviceContext()->IASetVertexBuffers(0, 1, &_vertexBuffer, &stride, &offset);

	// インデックスバッファ設定
	_api->GetDeviceContext()->IASetIndexBuffer(_indexBuffer, DXGI_FORMAT_R16_UINT, 0);

	// プリミティブトポロジ設定
	_api->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// マテリアル設定
	_api->SetMaterial(_material1);

	// テクスチャ設定
	_api->GetDeviceContext()->PSSetShaderResources(0, 1, TextureTool::Get()->GetTexture(_texNo));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ワールドマトリックスの初期化
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

	// ポリゴンの描画
	_api->GetDeviceContext()->DrawIndexed(_numIndex, 0, 0);
}

bool FieldMesh::Discard() const
{
	return false;
}
