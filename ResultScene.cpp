/*********************************************************************
 * \file   ResultScene.cpp
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#include "ResultScene.h"
#include "game.h"
#include "RenderComponent.h"
void ResultScene::InitScene(Game* game, RenderComponentManager* rManager)
{
}

void ResultScene::UpdateScene(double deltaTime,Game* game, RenderComponentManager* rManager)
{
	_world->Update(deltaTime);
	rManager->GetGraphicApi()->Clear(0.2, 0.2, 0.2, 1.0);
	_world->Draw();
	rManager->GetGraphicApi()->Present();
}

void ResultScene::UnInitScene(Game* game)
{
}
