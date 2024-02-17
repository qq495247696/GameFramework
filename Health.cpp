/*********************************************************************
 * \file   Health.cpp
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 18
 *********************************************************************/
#include "Health.h"
#include "texture.h"
#include "Home.h"
#include "scene.h"
#include "Render.h"
#include "Render2D.h"

void Health::Update(double deltaTime)
{


}

void Health::Draw()
{
	//H
	auto render = dynamic_cast<Render2D*>(_renderComponent);
	render->_anchor = Anchor::LeftTop();
	render->_pos = { 500.0f-40*2, 990.0f };
	render->_UW = 1.0f / 16.0f;
	render->_VH = 1.0f / 6.0f;
	render->_UV = { render->_UW*8,render->_VH*2 };
	render->_width = 40;
	render->_height = 100;
	render->Draw(this);
	//P
	render->_anchor = Anchor::LeftTop();
	render->_pos = { 500.0f-40, 990.0f };
	render->_UW = 1.0f / 16.0f;
	render->_VH = 1.0f / 6.0f;
	render->_UV = { render->_UW * 0,render->_VH * 3 };
	render->_width = 40;
	render->_height = 100;
	render->Draw(this);

	for (int i = 5; i > 0; i--)
	{
		// ¡‰ñ•\Ž¦‚·‚éŒ…‚Ì”Žš
		float x = (float)(_hp % 10);
		
		render->_anchor = Anchor::LeftTop();
		render->_pos = { (480.0f+(i*40)), 990.0f };
		render->_UW = 1.0f / 16.0f;
		render->_VH = 1.0f / 6.0f;
		render->_UV = { render->_UW * x,render->_VH };
		render->_width = 40;
		render->_height = 100;
		render->Draw(this);
		// ŽŸ‚ÌŒ…‚Ö
		_hp /= 10;
	}
	if (_uiPartner)
	{
		_uiPartner->Draw();
	}
}

bool Health::Discard() const
{
	return false;
}
