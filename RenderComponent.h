#pragma once
#include "Render2D.h"
#include "Render3D.h"
#include "DirectXAPI.h"
class RenderComponentManager
{
public:
	RenderComponentManager(DirectXAPI* _api): _api(_api)
	{
		_render2D = new Render2D(_api,Anchor::LeftTop);
		_render3D = new Render3D(_api);
	}
	~RenderComponentManager()
	{
		delete _render2D;
		delete _render3D;
	}
	Render2D		*_render2D;
	Render3D		*_render3D;
	DirectXAPI* GetGraphicApi() const{ return _api; }
private:
	DirectXAPI*				_api;

};
