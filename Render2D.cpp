#include "Render2D.h"

void Render2D::DrawCenter(Object* object)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	_dApi->GetDeviceContext()->Map(_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	float hw, hh;
	hw = _width * 0.5f;
	hh = _height * 0.5f;

	float BaseAngle = atan2f(hh, hw);		// 中心点から頂点に対する角度
	D3DXVECTOR2 temp = D3DXVECTOR2(hw, hh);
	float Radius = D3DXVec2Length(&temp);	// 中心点から頂点に対する距離

	float x = _pos.x - cosf(BaseAngle + _rotate) * Radius;
	float y = _pos.y - sinf(BaseAngle + _rotate) * Radius;
	vertex[0].Position = D3DXVECTOR3(x, y, 0.0f);

	x = _pos.x + cosf(BaseAngle - _rotate) * Radius;
	y = _pos.y - sinf(BaseAngle - _rotate) * Radius;
	vertex[1].Position = D3DXVECTOR3(x, y, 0.0f);

	x = _pos.x - cosf(BaseAngle - _rotate) * Radius;
	y = _pos.y + sinf(BaseAngle - _rotate) * Radius;
	vertex[2].Position = D3DXVECTOR3(x, y, 0.0f);

	x = _pos.x + cosf(BaseAngle + _rotate) * Radius;
	y = _pos.y + sinf(BaseAngle + _rotate) * Radius;
	vertex[3].Position = D3DXVECTOR3(x, y, 0.0f);

	vertex[0].Diffuse = _color;
	vertex[1].Diffuse = _color;
	vertex[2].Diffuse = _color;
	vertex[3].Diffuse = _color;

	vertex[0].TexCoord = _UV;
	vertex[1].TexCoord = D3DXVECTOR2(_UV.x + _UW, _UV.y);
	vertex[2].TexCoord = D3DXVECTOR2(_UV.x, _UV.y + _VH);
	vertex[3].TexCoord = D3DXVECTOR2(_UV.x + _UW, _UV.y + _VH);

	_dApi->GetDeviceContext()->Unmap(_vertexBuffer, 0);

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	_dApi->GetDeviceContext()->IASetVertexBuffers(0, 1, &_vertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	_dApi->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// テクスチャ設定
	_dApi->GetDeviceContext()->PSSetShaderResources(0, 1, TextureTool::Get()->GetTexture(object->GetTexNo()));

	// マテリアル設定
	_dApi->SetMaterial(_material);

	// マトリクス設定
	_dApi->SetWorldViewProjection2D();

	// 2D描画なので深度無効
	_dApi->SetDepthEnable(false);

	// ライティング無効
	_dApi->SetLightEnable(false);

	// ポリゴン描画
	_dApi->GetDeviceContext()->Draw(4, 0);
}

void Render2D::DrawLeftTop(Object* object)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	_dApi->GetDeviceContext()->Map(_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	
	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;
	
	// 左上を原点として設定するプログラム
	vertex[0].Position = D3DXVECTOR3(_pos.x,_pos.y , 0.0f);
	vertex[0].Diffuse = _color;
	vertex[0].TexCoord = _UV;
	
	vertex[1].Position = D3DXVECTOR3(_pos.x + _width, _pos.y, 0.0f);
	vertex[1].Diffuse = _color;
	vertex[1].TexCoord = D3DXVECTOR2(_UV.x + _UW, _UV.y);
	
	vertex[2].Position = D3DXVECTOR3(_pos.x, _pos.y + _height, 0.0f);
	vertex[2].Diffuse = _color;
	vertex[2].TexCoord = D3DXVECTOR2(_UV.x, _UV.y + _VH);
	
	vertex[3].Position = D3DXVECTOR3(_pos.x + _width, _pos.y + _height, 0.0f);
	vertex[3].Diffuse = _color;
	vertex[3].TexCoord = D3DXVECTOR2(_UV.x + _UW, _UV.y + _VH);
	
	_dApi->GetDeviceContext()->Unmap(_vertexBuffer, 0);
	
	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	_dApi->GetDeviceContext()->IASetVertexBuffers(0, 1, &_vertexBuffer, &stride, &offset);
	
	// プリミティブトポロジ設定
	_dApi->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	
	// テクスチャ設定
	_dApi->GetDeviceContext()->PSSetShaderResources(0, 1, TextureTool::Get()->GetTexture(object->GetTexNo()));
	
	// マテリアル設定
	_dApi->SetMaterial(_material);
	
	// マトリクス設定
	_dApi->SetWorldViewProjection2D();
	
	// 2D描画なので深度無効
	_dApi->SetDepthEnable(false);
	
	// ライティング無効
	_dApi->SetLightEnable(false);
	
	// ポリゴン描画
	_dApi->GetDeviceContext()->Draw(4, 0);
}

void Render2D::Draw(Object* object)
{
	switch (_anchor)
	{
	case Anchor::LeftTop:
		DrawLeftTop(object);
		break;
	case Anchor::Center:
		DrawCenter(object);
		break;
	}
}
