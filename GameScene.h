
#pragma once
#include "Scene.h"
#include "World.h"
class RenderComponentManager;
class GameScene : public Scene
{
	
public:
	GameScene() { _world = new World(); };
	~GameScene() { delete _world; }


	void InitScene(Game* game, RenderComponentManager* rManager) override;
	void UpdateScene(double deltaTime,Game* game, RenderComponentManager* rManager) override;
	void UnInitScene(Game* game) override;

};

