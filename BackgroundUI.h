/*********************************************************************
 * \file   BackgroundUI.h
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 18
 *********************************************************************/
#pragma once
#include"Ui.h"
#include"UiInfoSubject.h"
class BackgroundUi:public Ui
{
public:
	BackgroundUi(const int texNo, Render* render,World* world, Ui* partner):Ui(texNo, render,"BackGroundUi",world, partner)
	{
	}

	~BackgroundUi()
	{
		if (_uiPartner !=nullptr)
		{
			delete _uiPartner;
		}
	}

	void Update(double deltaTime) override;
	void Draw() override;
	bool Discard() const override;
};
