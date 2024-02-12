#pragma once
#include <map>
#include "model.h"
#include <string>
#include "Texture.h"
class  AssetManager
{
public:
	static AssetManager* Get()
	{
		static AssetManager p;
		return& p;
	}

	void Init(DirectXAPI* api)
	{
		
		LoadModel((char*)"data/MODEL/home.obj", &_home,api);
		LoadModel((char*)"data/MODEL/Enemy01.obj", &_enemy, api);
		LoadModel((char*)"data/MODEL/Tower.obj", &_normalTower, api);
		LoadModel((char*)"data/MODEL/Tower2.obj", &_fireTower, api);
		LoadModel((char*)"data/MODEL/Tower3.obj", &_thunderTower, api);
		LoadModel((char*)"data/MODEL/wall.obj", &_wall, api);

	}
	void UnInit()
	{
		UnloadModel(&_wall);
		UnloadModel(&_home);
		UnloadModel(&_normalTower);
		UnloadModel(&_fireTower);
		UnloadModel(&_thunderTower);
		UnloadModel(&_enemy);
	}


	DX11_MODEL				_wall;
	DX11_MODEL				_home;
	DX11_MODEL				_normalTower;
	DX11_MODEL				_fireTower;
	DX11_MODEL				_thunderTower;
	DX11_MODEL				_enemy;

};