//=============================================================================
//
// 地面処理 [Select.h]
// Author : 
//
//=============================================================================
#pragma once

#include <d3dx9.h>
#include "StateMachine.h"
#include "object.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
class Select:public Object
{
public:
	Select(DX11_MODEL* model, Render* render, World* world) :Object(model, render, "Select", world)
	{
		_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		_rotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		_scale = D3DXVECTOR3(5.0f, 5.0f, 5.0f);
		_use = false;
		//_model.SubsetArray->Material.Material.Diffuse = { 0.0,1.0,0.0,0.5 };
	}
	~Select(){;}

	D3DXVECTOR3     size;		// 当たり判定用サイズ
	// ﾍｨｹ� Object ｼﾌｳﾐ
	void Update(double deltaTime) override;
	void Draw() override;
	bool Discard() const override;

};