/*********************************************************************
 * \file   Render.h
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#pragma once
class DirectXAPI;
class Object;
class Render
{
public:
	Render(DirectXAPI* api):_dApi(api) { ; }
	virtual ~Render() { ; }
	virtual	void Draw(Object* object) = 0;
protected:
	DirectXAPI*				_dApi;//现在只有directX，要是有其他渲染接口的话也可以抽象出来，从构詠E?
};
