#include "TitleScnne.h"
#include "game.h"
#include "RenderComponent.h"
#include "player.h"
#include "EnemyBullet.h"
#include "camera.h"
#include "Wall.h"
void TitleScene::InitScene(Game* game, RenderComponentManager* rManager)
{
	Camera* cam = new Camera(_world);
	_world->AddObject(cam);
	cam->SetCamera(rManager->GetGraphicApi());
	Wall* wall = new Wall(&AssetManager::Get()->_wall, rManager->_render3D, _world);
	_world->AddObject(wall);
	cam->SetCameraAt({ 0,50,100 }, true);
	Player *player = new Player(nullptr, rManager->_render3D, _world);
	_world->AddObject(player);
	EnemyBullet* e = new EnemyBullet(&AssetManager::Get()->_fireTower,rManager->_render3D, _world);
	_world->AddObject(e);
	rManager->GetGraphicApi()->SetDepthEnable(true);
	rManager->GetGraphicApi()->SetAlphaTestEnable(true);
}

void TitleScene::UpdateScene(double deltaTime,Game* game, RenderComponentManager* rManager)
{
	_world->Update(deltaTime);

	auto cam = _world->GetObjectWithTag<Camera>("Camera");

	cam->SetCamera(rManager->GetGraphicApi());
	cam->SetCameraAt({ 0,0,200 }, false);
	rManager->GetGraphicApi()->Clear(0.2f,0.2f,0.2f,1.0f );
	rManager->GetGraphicApi()->SetCullingMode(CULL_MODE_BACK);
	_world->Draw();
	rManager->GetGraphicApi()->Present();
}

void TitleScene::UnInitScene(Game* game)
{
}
