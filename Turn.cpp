/*********************************************************************
 * \file   Turn.cpp
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 18
 *********************************************************************/
#include "Turn.h"
#include "Render2D.h"

void Turn::Update(double deltaTime)
{
}

void Turn::Draw()
{
	_hp = 10000;
	//T
	auto render = dynamic_cast<Render2D*>(_renderComponent);
	render->_anchor = Anchor::LeftTop();
	render->_pos = { 800.0f , -5.0f };
	render->_UW = 1.0f / 16.0f;
	render->_VH = 1.0f / 6.0f;
	render->_UV = { render->_UW * 7,render->_VH *3 };
	render->_width = 30;
	render->_height = 60;
	render->_color = { 0.5,0.5,0.5,1.0 };
	render->Draw(this);
	//U
	render->_anchor = Anchor::LeftTop();
	render->_pos = { 800.0f + 40, -5.0f };
	render->_UW = 1.0f / 16.0f;
	render->_VH = 1.0f / 6.0f;
	render->_UV = { render->_UW * 1,render->_VH * 2 };
	render->_width = 30;
	render->_height = 60;
	render->Draw(this);
	//R
	render->_anchor = Anchor::LeftTop();
	render->_pos = { 800.0f + 40 * 2, -5.0f };
	render->_UW = 1.0f / 16.0f;
	render->_VH = 1.0f / 6.0f;
	render->_UV = { render->_UW * 6,render->_VH * 3 };
	render->_width = 30;
	render->_height = 60;
	render->Draw(this);
	//N
	render->_anchor = Anchor::LeftTop();
	render->_pos = { 800.0f + 40 * 3, -5.0f };
	render->_UW = 1.0f / 16.0f;
	render->_VH = 1.0f / 6.0f;
	render->_UV = { render->_UW * 5,render->_VH * 2 };
	render->_width = 30;
	render->_height = 60;
	render->Draw(this);


	render->_anchor = Anchor::LeftTop();
	render->_pos = { 800.0f + 40 * 4.6, -30.0f };
	render->_UW = 1.0f / 16.0f;
	render->_VH = 1.0f / 6.0f;
	render->_UV = { render->_UW * _wave,render->_VH  };
	render->_width = 70;
	render->_height = 100;
	render->_color = { 1.0,1.0,1.0,1.0 };
	render->Draw(this);

	if (_uiPartner)
	{
		_uiPartner->Draw();
	}
}

bool Turn::Discard() const
{
	return false;
}
