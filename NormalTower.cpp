/*********************************************************************
 * \file   NormalTower.cpp
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#include "input.h"
#include "camera.h"
#include "NormalTower.h"
#include "Enemybullet.h"
#include "shadow.h"
#include "sound.h"
#include "BattlePhase.h"
#include "World.h"
#include "enemy.h"
#include "AssetManager.h"

static float rotValue = D3DX_PI / 90;
void NormalTower::Update(double deltaTime)
{
	FoundedEnemy(deltaTime);

	if (_finded == false)
	{
		NoFoundedEnemy();
	}

	
}

void NormalTower::Attack(double deltaTime)
{
	D3DXVECTOR3 x = { 0.0,0.0,1.0 };
	time += deltaTime;
	if (time > _attackSpeed)
	{
		D3DXVECTOR4 pOut;
		D3DXMATRIX rot;
		D3DXMatrixIdentity(&rot);
		D3DXMatrixRotationY(&rot, _rotate.y);
		D3DXVec3Transform(&pOut, &x, &rot);
		//SetEnemyBullet(_position, { pOut.x,0,pOut.z });
		PlaySound(AssetManager::Get()->_normalShootSe, 0);
		time = 0;
	}
}

void NormalTower::NoFoundedEnemy()
{
	if (_position.x < 0)
	{
		_rotate.y -= rotValue;
		if (_rotate.y < 0)
		{
			_rotate.y = 0;
			rotValue = -rotValue;

		}
		if (_rotate.y > D3DX_PI)
		{
			_rotate.y = D3DX_PI;
			rotValue = -rotValue;
		}
	}
	if (_position.x > 0)
	{
		_rotate.y += rotValue;
		if (_rotate.y > 2 * D3DX_PI)
		{
			_rotate.y = 2 * D3DX_PI;
			rotValue = -rotValue;
		}
		if (_rotate.y < D3DX_PI)
		{
			_rotate.y = D3DX_PI;
			rotValue = -rotValue;
		}
	}
}

void NormalTower::FoundedEnemy(float deltaTime)
{
	auto enemy = GetWorld()->GetObjectsWithTag<Enemy>("Enemy");

	for (auto x : enemy)
	{

		Vec3 velVec = x->GetPosition() - _position;
		if (D3DXVec3Length(&velVec) < 850)
		{
			Vec3 forword = { 0,0,1 };
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
			_finded = true;

			Attack(deltaTime);
			break;
		}
	}
}

void NormalTower::Draw()
{
	_renderComponent->Draw(this);
}

bool NormalTower::Discard() const
{
	return false;
}
