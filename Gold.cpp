/*********************************************************************
 * \file   Gold.cpp
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 18
 *********************************************************************/
#include "Gold.h"
#include "Render2D.h"
void Gold::Update(double deltaTime)
{
}

void Gold::Draw()
{
	//M
	auto render = dynamic_cast<Render2D*>(_renderComponent);
	render->_anchor = Anchor::LeftTop();
	render->_pos = { 1000.0f + 40, 990.0f };
	render->_UW = 1.0f / 16.0f;
	render->_VH = 1.0f / 6.0f;
	render->_UV = { render->_UW * 13,render->_VH * 2 };
	render->_width = 40;
	render->_height = 100;
	render->Draw(this);
	//O
	render->_anchor = Anchor::LeftTop();
	render->_pos = { 1000.0f + 40*2, 990.0f };
	render->_UW = 1.0f / 16.0f;
	render->_VH = 1.0f / 6.0f;
	render->_UV = { render->_UW * 15,render->_VH * 2 };
	render->_width = 40;
	render->_height = 100;
	render->Draw(this);
	//N
	render->_anchor = Anchor::LeftTop();
	render->_pos = { 1000.0f + 40 * 3, 990.0f };
	render->_UW = 1.0f / 16.0f;
	render->_VH = 1.0f / 6.0f;
	render->_UV = { render->_UW * 14,render->_VH * 2 };
	render->_width = 40;
	render->_height = 100;
	render->Draw(this);
	//E
	render->_anchor = Anchor::LeftTop();
	render->_pos = { 1000.0f + 40*4, 990.0f };
	render->_UW = 1.0f / 16.0f;
	render->_VH = 1.0f / 6.0f;
	render->_UV = { render->_UW * 5,render->_VH * 2 };
	render->_width = 40;
	render->_height = 100;
	render->Draw(this);
	//Y
	render->_anchor = Anchor::LeftTop();
	render->_pos = { 1000.0f + 40*5, 990.0f };
	render->_UW = 1.0f / 16.0f;
	render->_VH = 1.0f / 6.0f;
	render->_UV = { render->_UW * 9,render->_VH * 3 };
	render->_width = 40;
	render->_height = 100;
	render->Draw(this);

	for (int i = 5; i > 0; i--)
	{
		// ¡‰ñ•\Ž¦‚·‚éŒ…‚Ì”Žš
		float x = (float)(_moneny % 10);

		render->_anchor = Anchor::LeftTop();
		render->_pos = { (1240.0f + (i * 40)), 990.0f };
		render->_UW = 1.0f / 16.0f;
		render->_VH = 1.0f / 6.0f;
		render->_UV = { render->_UW * x,render->_VH };
		render->_width = 40;
		render->_height = 100;
		render->Draw(this);
		// ŽŸ‚ÌŒ…‚Ö
		_moneny /= 10;
	}
	if (_uiPartner)
	{
		_uiPartner->Draw();
	}
}

bool Gold::Discard() const
{
	return false;
}
