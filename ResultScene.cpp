/*********************************************************************
 * \file   ResultScene.cpp
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#include "ResultScene.h"
#include "game.h"
#include "RenderComponent.h"
#include "result.h"
#include "TitleScene.h"
void ResultScene::InitScene(Game* game, RenderComponentManager* rManager)
{
	Result* result = new Result(AssetManager::Get()->_resultTexNo, rManager->_render2D, _world);
	_world->AddObject(result);
}

void ResultScene::UpdateScene(double deltaTime,Game* game, RenderComponentManager* rManager)
{
	_world->Update(deltaTime);
	rManager->GetGraphicApi()->Clear(0.2, 0.2, 0.2, 1.0);
	_world->Draw();
	rManager->GetGraphicApi()->Present();
	_world->CleanUp();
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		game->ChangeScene(new TitleScene());
	}
}

void ResultScene::UnInitScene(Game* game)
{
}
