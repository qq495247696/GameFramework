/*********************************************************************
 * \file   AssetManager.h
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#pragma once
#include <map>
#include "model.h"
#include <string>
#include "Texture.h"
#include "sound.h"
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
		LoadModel((char*)"data/MODEL/Tower.obj", &_selectNormalTower, api);
		LoadModel((char*)"data/MODEL/Tower2.obj", &_selectFireTower, api);
		LoadModel((char*)"data/MODEL/Tower3.obj", &_selectThunderTower, api);
		LoadModel((char*)"data/MODEL/wall.obj", &_wall, api);
		LoadModel((char*)"data/MODEL/place.obj", &_place, api);

		_bulletTexNo = TextureTool::Get()->LoadTexture((char*)"data/TEXTURE/bullet000.png",api);
		_feildTexNo= TextureTool::Get()->LoadTexture((char*)"data/TEXTURE/field003.png", api);
		_skyBoxTexNo = TextureTool::Get()->LoadTexture((char*)"data/TEXTURE/sky001.jpg", api);
		_titleTexNo= TextureTool::Get()->LoadTexture((char*)"data/TEXTURE/title.jpg", api);
		_resultTexNo = TextureTool::Get()->LoadTexture((char*)"data/TEXTURE/result.png", api);
		_backGroundTexNo = TextureTool::Get()->LoadTexture((char*)"data/TEXTURE/Ui.png", api);
		_front = TextureTool::Get()->LoadTexture((char*)"data/TEXTURE/font.png", api);

		_titleSe = LoadSound((char*)"data/BGM/sample000.wav");

	}
	void UnInit()
	{
		UnloadModel(&_wall);
		UnloadModel(&_home);
		UnloadModel(&_normalTower);
		UnloadModel(&_fireTower);
		UnloadModel(&_thunderTower);
		UnloadModel(&_enemy);
		TextureTool::Get()->UninitTexture();
	}


	DX11_MODEL				_wall;
	DX11_MODEL				_home;
	DX11_MODEL				_normalTower;
	DX11_MODEL				_fireTower;
	DX11_MODEL				_thunderTower;
	DX11_MODEL				_enemy;
	DX11_MODEL				_selectNormalTower;
	DX11_MODEL				_selectFireTower;
	DX11_MODEL				_selectThunderTower;
	DX11_MODEL				_place;

	int						_bulletTexNo;
	int						_feildTexNo;
	int						_skyBoxTexNo;
	int						_titleTexNo;
	int						_resultTexNo;
	int						_backGroundTexNo;
	int						_front;

	int						_titleSe;
};
