/*********************************************************************
 * \file   enemy.cpp
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#include "input.h"
#include "camera.h"
#include "enemy.h"
#include "texture.h"
#include "player.h"
#include <random>
#include "BattlePhase.h"
#include "World.h"
#include "Home.h"
#include "AssetManager.h"
#include "EnemyBullet.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	VALUE_MOVE		(5.0f)						// 移動量
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)			// 回転量
void Enemy::Update(double deltaTime)
{
	//ﾒﾆ・､ﾎｲｿｷﾖ
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
		Vec3 velVec = Vec3(GetWorld()->GetObjectWithTag<Home>("Home")->GetPosition().x,0,GetWorld()->GetObjectWithTag<Home>("Home")->GetPosition().z+650) - _position;
		float len = D3DXVec3Length(&velVec);
		D3DXVec3Normalize(&velVec, &velVec);
		if(len>150)
		{
			_position += velVec * _speed * deltaTime;
		}
		else
		{
			_attackTime += deltaTime;
			if (_attackTime > 2.5f)
			{
				Vec3 velVec = Vec3(GetWorld()->GetObjectWithTag<Home>("Home")->GetPosition().x, 0, GetWorld()->GetObjectWithTag<Home>("Home")->GetPosition().z) - _position;
				D3DXVec3Normalize(&velVec, &velVec);
				PlaySound(AssetManager::Get()->_enemyShotSe, 0);
				SetVolume(AssetManager::Get()->_enemyShotSe,0.4);
				EnemyBullet* eBullet = new EnemyBullet({_position.x,90,_position.z }, velVec, _atk,_renderComponent, GetWorld());
				GetWorld()->AddObject(eBullet);
				_attackTime = 0;
			}
		}
	}

}

void Enemy::Draw()
{
	_renderComponent->Draw(this);

	

}

bool Enemy::Discard() const
{

	if (_hp <= 0)
	{
		auto p = GetWorld()->GetObjectWithTag<Player>("Player");
		p->_money += 45;
		return true;	
	}
	else
	{
		return false;
	}
}
