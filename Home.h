#pragma once

#include <d3dx9.h>
#include "object.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
class Home:public Object
{
public:
	Home(DX11_MODEL* model, Render* render, World* world ):Object(model,render,"Home",world)
	{
			// 位置・回転・スケールの初期設定
			_position = D3DXVECTOR3(0.0f, 0.0f, -1200.0f);
			_rotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			_scale = D3DXVECTOR3(20.0f, 20.0f, 20.0f);
			hitedSound = LoadSound((char*)"data/SE/defend001.wav");
			hp = 5;

			//当たり判定用サイズの初期設定
			size = D3DXVECTOR3(120.0f, 210.0f, 120.0f);
		;
	}
	~Home()
	{

	}
	// ﾍｨｹ� Object ｼﾌｳﾐ
	void Update(double deltaTime) override;
	void Draw() override;
	bool Discard() const override;
private:
	int				hp;
	unsigned int    hitedSound;
	D3DXVECTOR3     size;		
};

