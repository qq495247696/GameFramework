#pragma once
#include "renderer.h"

class EnemyBullet
{
public:
	D3DXMATRIX				mtxWorld;
	bool					use;	// true:使っている  false:未使用
	D3DXVECTOR3				pos;	// バレットの座標
	D3DXVECTOR3				dir;	
	D3DXVECTOR3				rot;
	D3DXVECTOR3				scl;
	float					speed;	// バレットの移動スピード
	float					frame;	// フレーム数

	D3DXVECTOR3     size;		// 当たり判定用サイズ
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitEnemyBullet(void);
void UninitEnemyBullet(void);
void UpdateEnemyBullet(void);
void DrawEnemyBullet(void);

EnemyBullet* GetEnemyBullet(void);
void SetEnemyBullet(D3DXVECTOR3 pos, D3DXVECTOR3 dir);