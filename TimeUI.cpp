/*********************************************************************
 * \file   TimeUI.cpp
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 18
 *********************************************************************/
#include "TimeUI.h"
#include "Render2D.h"
void TimeUI::Update(double deltaTime)
{
}

void TimeUI::Draw()
{

	int first = (int)_time / 10;
	int secend = (int)_time % 10;
	auto render = dynamic_cast<Render2D*>(_renderComponent);
	render->_anchor = Anchor::LeftTop();
	render->_pos = { 15.0f, 850.0f };
	render->_UW = 1.0f / 16.0f;
	render->_VH = 1.0f / 6.0f;
	render->_UV = { render->_UW * first,render->_VH };
	render->_width = 80;
	render->_height = 250;
	render->Draw(this);
	//P
	render->_anchor = Anchor::LeftTop();
	render->_pos = { 15.0f + 80, 850.0f };
	render->_UW = 1.0f / 16.0f;
	render->_VH = 1.0f / 6.0f;
	render->_UV = { render->_UW * secend,render->_VH  };
	render->_width = 80;
	render->_height = 250;
	render->Draw(this);

	if (_uiPartner)
	{
		_uiPartner->Draw();
	}
}

bool TimeUI::Discard() const
{
	return false;
}
