#pragma once
/*********************************************************************
 * \file   Turn.h
 * \brief
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 18
 *********************************************************************/
#pragma once
#include "Ui.h"
#include "UiInfoSubject.h"

class Turn :public Ui
{
public:
	Turn(const int texNo, Render* render, World* world, Ui* partner) :Ui(texNo, render, "Score", world, partner) { ; }
	~Turn() {};
	void Update(double deltaTime) override;
	void Draw() override;
	bool Discard() const override;

	UiInfoSubject		_subject{this};
};

