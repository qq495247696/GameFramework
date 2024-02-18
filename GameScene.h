/*********************************************************************
 * \file   GameScene.h
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 18
 *********************************************************************/
#pragma once
#include "Scene.h"
#include "World.h"
#include "gameloop.h"
class RenderComponentManager;
class GameScene : public Scene
{
	
public:
	GameScene() { _world = new World(); };
	~GameScene() 
	{ 
		delete _world;
		_world = nullptr;
	}


	void InitScene(Game* game, RenderComponentManager* rManager) override;
	void UpdateScene(double deltaTime,Game* game, RenderComponentManager* rManager) override;
	void UnInitScene(Game* game) override;
private:
	GameLoop*		_wave;
};

