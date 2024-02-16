/*********************************************************************
 * \file   TitleScnne.h
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#pragma once
#include "Scene.h"
#include "World.h"
class RenderComponentManager;
class TitleScene : public Scene
{
public:
	TitleScene() { _world = new World(); }
	~TitleScene() { delete _world; }


	void InitScene(Game* game, RenderComponentManager* rManager) override;
	void UpdateScene(double deltaTime,Game* game, RenderComponentManager* component) override;
	void UnInitScene(Game* game) override;

};
