/*********************************************************************
 * \file   GameScene.cpp
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#include "GameScene.h"
#include "game.h"
#include "RenderComponent.h"
void GameScene::InitScene(Game* game, RenderComponentManager* rManager)
{
}

void GameScene::UpdateScene(double deltaTime,Game* game, RenderComponentManager* rManager)
{
	_world->Update(deltaTime);
	rManager->GetGraphicApi()->Clear(0.2, 0.2, 0.2, 1.0);
	_world->Draw();
	rManager->GetGraphicApi()->Present();
}

void GameScene::UnInitScene(Game* game)
{
	
}
