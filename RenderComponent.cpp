#include "Render2D.h"
#include "RenderComponent.h"
#include "Render3D.h"
#include "DirectXAPI.h"
RenderComponentManager::RenderComponentManager(DirectXAPI* _api) : _api(_api)
{
	_render2D = new Render2D(_api, Anchor::LeftTop);
	_render3D = new Render3D(_api);
}
