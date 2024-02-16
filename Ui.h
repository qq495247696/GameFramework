/*********************************************************************
 * \file   Ui.h
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 17
 *********************************************************************/
#pragma once
#include "object.h"

class Ui:public Object
{
public:
	Ui(const int texNo, Render* render, const std::string& tag, World* world,Ui* partner) :Object(texNo, render, tag, world), _uiPartner(partner) {}

	~Ui()
	{
	}

protected:
	Ui*					_uiPartner;

};
