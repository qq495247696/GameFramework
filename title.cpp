/*********************************************************************
 * \file   title.cpp
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#include "title.h"
#include "texture.h"
#include "fade.h"


void Title::Update(double deltaTime)
{

}

void Title::Draw()
{
	_renderComponent->Draw(this);
}

bool Title::Discard() const
{
	return false;
}
