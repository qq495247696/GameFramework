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
	auto render = dynamic_cast<Render2D*>(_renderComponent);
	render->_anchor = Anchor::LeftTop();
	render->_pos = { 0 , 0 };
	render->_UW = 1.0f ;
	render->_VH = 1.0f ;
	render->_UV = { 0,0 };
	render->_width = 1920;
	render->_height = 1080;
	render->Draw(this);
}

bool Result::Discard() const
{
	return false;
}
