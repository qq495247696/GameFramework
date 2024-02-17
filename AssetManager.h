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
		LoadModel((char*)"data/MODEL/Enemy01.obj", &_enemy01, api);
		LoadModel((char*)"data/MODEL/enemy02.obj", &_enemy02, api);
		LoadModel((char*)"data/MODEL/enemy03.obj", &_enemy03, api);
		LoadModel((char*)"data/MODEL/Tower.obj", &_normalTower, api);
		LoadModel((char*)"data/MODEL/Tower2.obj", &_fireTower, api);
		LoadModel((char*)"data/MODEL/Tower3.obj", &_thunderTower, api);
		LoadModel((char*)"data/MODEL/Tower.obj", &_selectNormalTower, api);
		LoadModel((char*)"data/MODEL/Tower2.obj", &_selectFireTower, api);
		LoadModel((char*)"data/MODEL/Tower3.obj", &_selectThunderTower, api);
		LoadModel((char*)"data/MODEL/wall.obj", &_wall, api);
		LoadModel((char*)"data/MODEL/place.obj", &_place, api);
		LoadModel((char*)"data/MODEL/EnemyBullet.obj", &_enemyBullet, api);

		_bulletTexNo = TextureTool::Get()->LoadTexture((char*)"data/TEXTURE/bullet000.png",api);
		_feildTexNo= TextureTool::Get()->LoadTexture((char*)"data/TEXTURE/field003.png", api);
		_skyBoxTexNo = TextureTool::Get()->LoadTexture((char*)"data/TEXTURE/sky001.jpg", api);
		_titleTexNo= TextureTool::Get()->LoadTexture((char*)"data/TEXTURE/title.jpg", api);
		_resultTexNo = TextureTool::Get()->LoadTexture((char*)"data/TEXTURE/result.jpg", api);
		_backGroundTexNo = TextureTool::Get()->LoadTexture((char*)"data/TEXTURE/Ui.png", api);
		_front = TextureTool::Get()->LoadTexture((char*)"data/TEXTURE/font.png", api);

		_titleSe = LoadSound((char*)"data/BGM/sample000.wav");
		_fireShotSe = LoadSound((char*)"data/SE/shot001.wav");
		_normalShootSe= LoadSound((char*)"data/SE/normalShoot.wav");
		_battleBgm = LoadSound((char*)"data/BGM/Battle.wav");
		_hitedSe = LoadSound((char*)"data/SE/defend001.wav");
	}
	void UnInit()
	{
		UnloadModel(&_wall);
		UnloadModel(&_home);
		UnloadModel(&_normalTower);
		UnloadModel(&_fireTower);
		UnloadModel(&_thunderTower);
		UnloadModel(&_enemy01);
		UnloadModel(&_enemy02);
		UnloadModel(&_enemy03);
		UnloadModel(&_selectNormalTower);
		UnloadModel(&_selectFireTower);
		UnloadModel(&_selectThunderTower);
		UnloadModel(&_place);
		TextureTool::Get()->UninitTexture();
	}

	//model
	DX11_MODEL				_wall;
	DX11_MODEL				_home;
	DX11_MODEL				_normalTower;
	DX11_MODEL				_fireTower;
	DX11_MODEL				_thunderTower;
	DX11_MODEL				_enemy01;
	DX11_MODEL				_enemy02;
	DX11_MODEL				_enemy03;
	DX11_MODEL				_selectNormalTower;
	DX11_MODEL				_selectFireTower;
	DX11_MODEL				_selectThunderTower;
	DX11_MODEL				_place;
	DX11_MODEL				_enemyBullet;
	//texture
	int						_bulletTexNo;
	int						_feildTexNo;
	int						_skyBoxTexNo;
	int						_titleTexNo;
	int						_resultTexNo;
	int						_backGroundTexNo;
	int						_front;
	//sound
	int						_titleSe;
	int						_fireShotSe;
	int						_normalShootSe;
	int						_battleBgm;
	int						_hitedSe;
};
