/*********************************************************************
 * \file   Place.cpp
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#include "Place.h"
#include "Utility.h"
#include "Texture.h"
#include "DirectXAPI.h"

void Place::Update(double deltaTime)
{
}

void Place::Draw()
{
	_renderComponent->Draw(this);
}

bool Place::Discard() const
{
	return false;
}
