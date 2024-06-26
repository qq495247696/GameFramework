/*********************************************************************
 * \file   Health.h
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 18
 *********************************************************************/
#pragma once
#include "Ui.h"
#include "UiInfoSubject.h"
class Health:public Ui
{
public:
	Health(const int texNo, Render* render, World* world,Ui* partner):Ui(texNo, render,"Score", world, partner) { ; }
	~Health() {};
	void Update(double deltaTime) override;
	void Draw() override;
	bool Discard() const override;

	UiInfoSubject		_subject{ this };
};

