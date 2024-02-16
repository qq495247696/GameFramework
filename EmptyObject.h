/*********************************************************************
 * \file   EmptyObject.h
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#pragma once
#include "object.h"
class DirectXAPI;
class DX11_MODEL;
class EmptyObject:public Object
{
public:
	EmptyObject(DirectXAPI* api,World*world):Object("EmptyObject",world) ,_api(api)
	{
		_position = { 0,0,0 };
		_scale = { 5,5,5 };
		_rotate = { 0,0,0 };
		_use = true;
	
	};
	~EmptyObject() {};

	void SetModel(DX11_MODEL* model) { _model = model; }
	// Object ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
	void Update(double deltaTime) override;
	void Draw() override;
	bool Discard() const override;
private:
	DirectXAPI*  _api;
};
