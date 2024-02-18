/*********************************************************************
 * \file   Tbullet.cpp
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 18
 *********************************************************************/
#include "Tbullet.h"

void TBullet::Update(double deltaTime)
{
	_position += (_vel * _speed) * deltaTime;
}

void TBullet::Draw()
{
	if (_use)
	{
		_renderComponent->Draw(this);
	}
}

bool TBullet::Discard() const
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
