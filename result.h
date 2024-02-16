/*********************************************************************
 * \file   result.h
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#pragma once

#include "object.h"
class Result :public Object
{
public:
	Result(int texNo, Render* render, World* world) :Object(texNo, render, "Result", world) {};
	~Result() {};
	void Update(double deltaTime) override;
	void Draw() override;
	bool Discard() const override;
};

