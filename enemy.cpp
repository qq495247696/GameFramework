//=============================================================================
//
// ポリゴン表示処理 [enemy.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "enemy.h"
#include "texture.h"
#include "player.h"
#include "shadow.h"
#include <random>
#include "BattlePhase.h"
#include "World.h"
#include "Home.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	VALUE_MOVE		(5.0f)						// 移動量
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)			// 回転量
void Enemy::Update(double deltaTime)
{
	//ﾒﾆ�ﾓ､ﾎｲｿｷﾖ
	motor(deltaTime);
	

}

void Enemy::motor(double deltaTime)
{
	if (_target<4)
	{
		Vec3 velVec = _wayLine[_target] - _position;
		Vec3 forword = { 0,0,-1 };
		Vec3 length = velVec;
		D3DXVec3Normalize(&velVec, &velVec);
		Vec3 cross;
		D3DXVec3Cross(&cross, &velVec, &forword);
		float theta = D3DXVec3Dot(&velVec, &forword);
		float radian = acosf(theta);
		if (cross.y > 0)
		{
			_rotate.y = -radian;
		}
		else
		{

			_rotate.y = radian;
		}
		if (D3DXVec3Length(&length) < 50)
		{

			_target++;
		}
		_position += velVec * _speed * deltaTime;
	}
	else
	{
		Vec3 velVec = GetWorld()->GetObjectWithTag<Home>("Home")->GetPosition() - _position;
		D3DXVec3Normalize(&velVec, &velVec);
		_position += velVec * _speed * deltaTime;
	}
}

void Enemy::Draw()
{
	_renderComponent->Draw(this);

	

}

bool Enemy::Discard() const
{
	return false;
}
