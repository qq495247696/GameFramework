/*********************************************************************
 * \file   EnemyBullet.cpp
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#include "EnemyBullet.h"
#include "model.h"
#include "Render.h"

void EnemyBullet::Update(double deltaTime)
{
	if (_use)
	{
		//消滅処理
		if (frame > 500.0f)
		{
			_use = false;
			frame = 0;
		}

		//座標の更新
		_position += (_vel * _speed)*deltaTime;
		//時間経過
		frame += 1.0f;
	}
}

void EnemyBullet::Draw()
{	
	if (_use)
	{
		_renderComponent->Draw(this);
	}
}

bool EnemyBullet::Discard() const
{
	return false;
}
