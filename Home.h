/*********************************************************************
 * \file   Home.h
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#pragma once
#include "object.h"
#include "sound.h"
#include "UiInfoObsever.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
class Home:public Object
{
public:
	Home(DX11_MODEL* model, Render* render, World* world ):Object(model,render,"Home",world),_hp(10000)
	{
			// 位置・回転・スケールの初期設定
			_position = D3DXVECTOR3(0.0f, 0.0f, -1200.0f);
			_rotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			_scale = D3DXVECTOR3(20.0f, 20.0f, 20.0f);
			

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
	const int GetHp()const { return _hp; }
	void SetHp(const int hp) { _hp = hp; }
	UiInfoObsever	_obsever;
private:
	int				_hp;
	unsigned int    hitedSound;
	D3DXVECTOR3     size;		
};

