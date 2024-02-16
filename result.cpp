/*********************************************************************
 * \file   result.cpp
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#include "result.h"
#include "texture.h"
#include "fade.h"



void Result::Update(double deltaTime)
{
}

void Result::Draw()
{
	_renderComponent->Draw(this);
}

bool Result::Discard() const
{
	return false;
}
