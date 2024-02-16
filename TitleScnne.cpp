/*********************************************************************
 * \file   TitleScnne.cpp
 * \brief
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#include "TitleScnne.h"
#include "GameScene.h"
#include "RenderComponent.h"
#include "game.h"
#include "input.h"
#include "title.h"

void TitleScene::InitScene(Game* game, RenderComponentManager* rManager)
{
	PlaySound(AssetManager::Get()->_titleSe, -1);
	Title *title = new Title(AssetManager::Get()->_titleTexNo, rManager->_render2D, _world);
	_world->AddObject(title);
}

void TitleScene::UpdateScene(double deltaTime,Game* game, RenderComponentManager* rManager)
{
	_world->Update(deltaTime);
	rManager->GetGraphicApi()->Clear(0.2, 0.2, 0.2, 1.0);
	_world->Draw();
	rManager->GetGraphicApi()->Present();
	_world->CleanUp();
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		game->ChangeScene(new GameScene());
	}
}

void TitleScene::UnInitScene(Game* game)
{
	StopSoundAll();
}
