/*********************************************************************
 * \file   RenderComponent.h
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#pragma once
#ifndef RenderComponentManager_H
#define	RenderComponentManager_H
#include "Render2D.h"
#include "Render3D.h"
class DirectXAPI;
class RenderComponentManager
{
public:
	RenderComponentManager(DirectXAPI* _api);
	~RenderComponentManager()
	{
		delete _render2D;
		delete _render3D;
	}


	Render2D* _render2D;
	Render3D* _render3D;
	DirectXAPI* GetGraphicApi() const{ return _api; }
private:
	DirectXAPI*				_api;

};

#endif // !RenderComponentManager_H
