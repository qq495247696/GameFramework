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
	_position += (_vel * _speed)*deltaTime;
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
	if (_use)
	{
		return false;
	}
	else
	{
		return true;
	}
}
