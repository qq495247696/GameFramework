/*********************************************************************
 * \file   ResultScene.h
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#pragma once
#include "Scene.h"
#include "World.h"
class RenderComponentManager;
class ResultScene : public Scene
{
public:
	ResultScene() { _world = new World(); }
	~ResultScene() { delete _world; }

	void InitScene(Game* game, RenderComponentManager* rManager) override;
	void UpdateScene(double deltaTime,Game* game,RenderComponentManager* rManager) override;
	void UnInitScene(Game* game) override;

};
