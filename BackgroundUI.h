#pragma once
#include"Ui.h"
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
