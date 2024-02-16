#pragma once
#ifndef RenderComponentManager_H
#define	RenderComponentManager_H
class Render3D;
class DirectXAPI;
class Render2D;
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
