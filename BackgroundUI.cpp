/*********************************************************************
 * \file   BackgroundUI.cpp
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 18
 *********************************************************************/
#include "BackgroundUI.h"
#include "Render.h"
#include "Render2D.h"
void BackgroundUi::Update(double deltaTime)
{
}

void BackgroundUi::Draw()
{
    auto render = dynamic_cast<Render2D*>(_renderComponent);
    render->_anchor = Anchor::LeftTop();
    render->_pos = { 0,0 };
    render->_UV = { 0,0 };
    render->_UW = render->_VH = 1.0f;
    render->_width = 1920;
    render->_height = 1080;
    render->Draw(this);
    if (_uiPartner)
    {
        _uiPartner->Draw();
    }
}

bool BackgroundUi::Discard() const
{
    return false;
}
