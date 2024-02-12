//=============================================================================
//
// 弾処理 [bullet.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"
#include "render.h"
#include "object.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BULLET_NUM		(10)		// バレットのMax数
#define BULLET_SPEED	(10.0f)		// バレットの移動スピード


// バレット構造体
class Bullet:public Object
{
public:
	Bullet(DX11_MODEL* model, Render* render,World* world) :Object(model, render, "Bullet",world) 
	{
	
	};
	~Bullet()override {}
	float					frame;	// フレーム数
	int						shadow;	// 影の識別番号
	D3DXVECTOR3     size;		// 当たり判定用サイズ

	void Update(double deltaTime) override;
	void Draw() override;
	bool Discard() const override;

};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

Bullet *GetBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 dir);

