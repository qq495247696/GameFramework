/*********************************************************************
 * \file   Wall.cpp
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#include "Wall.h"
#include "Utility.h"
#include "Texture.h"
#include "DirectXAPI.h"

void Wall::Update(double deltaTime)
{
}

void Wall::Draw()
{
	_renderComponent->Draw(this);
}

bool Wall::Discard() const
{
	return false;
}
