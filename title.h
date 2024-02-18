/*********************************************************************
 * \file   title.h
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#pragma once

#include "object.h"
class Title :public Object
{
public:
	Title(int texNo, Render* render, World* world):Object(texNo, render,"Title",world) {};
	~Title() {};
	void Update(double deltaTime) override;
	void Draw() override;
	bool Discard() const override;
};

