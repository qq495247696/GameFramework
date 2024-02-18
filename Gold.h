/*********************************************************************
 * \file   Gold.h
 * \brief
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 18
 *********************************************************************/
#pragma once
#include "Ui.h"
#include "UiInfoSubject.h"
class Gold :public Ui
{
public:
	Gold(const int texNo, Render* render, World* world, Ui* partner) :Ui(texNo, render, "Gold", world, partner) { ; }
	~Gold() {};
	void Update(double deltaTime) override;
	void Draw() override;
	bool Discard() const override;

	UiInfoSubject		_subject{ this };
};
