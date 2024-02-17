/*********************************************************************
 * \file   Ui.h
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 17
 *********************************************************************/
#pragma once
#include "object.h"
class UiInfoSubject;
class Ui:public Object
{
public:
	Ui(const int texNo, Render* render, const std::string& tag, World* world,Ui* partner) :Object(texNo, render, tag, world), _uiPartner(partner) {}

	~Ui()
	{
	}

	friend  UiInfoSubject;
protected:
	Ui*						_uiPartner;
	int						_hp;
	double					_time;
	int						_wave;
	int						_moneny;
};
