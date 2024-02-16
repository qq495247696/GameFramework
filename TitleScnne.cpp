#include "TitleScnne.h"
#include "RenderComponent.h"
#include "player.h"
#include "EnemyBullet.h"
#include "camera.h"
#include "Wall.h"
#include "bullet.h"
#include "meshfield.h"
#include "meshsky.h"
#include "Home.h"
#include "enemy.h"
#include "EnemySpwaner.h"
#include "Debug.h"
#include "AssetManager.h"
#include "collision.h"

void TitleScene::InitScene(Game* game, RenderComponentManager* rManager)
{
	Camera* cam = new Camera(_world);
	Debug::Get()->SetWorld(_world);
	_world->AddObject(cam);
	cam->SetCamera(rManager->GetGraphicApi());
	Wall* wall = new Wall(&AssetManager::Get()->_wall, rManager->_render3D, _world);
	_world->AddObject(wall);
	cam->SetCameraAt({ 0,50,100 }, true);
	Player* player = new Player(nullptr, rManager->_render3D, rManager->GetGraphicApi(), _world);
	_world->AddObject(player);
	FieldMesh* field = new FieldMesh(AssetManager::Get()->_feild, rManager->GetGraphicApi(), D3DXVECTOR3(0.0f, 0.0f, 3000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100, 100, { 180.0f, 180.0f }, _world);
	_world->AddObject(field);
	SkyBox* skyBox = new SkyBox(AssetManager::Get()->_skyBox,rManager->GetGraphicApi(), D3DXVECTOR3(0.0f, 0.0f, 3000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10000.0f, 16, 8,_world);
	_world->AddObject(skyBox);
	Home* home = new Home(&AssetManager::Get()->_home, rManager->_render3D, _world);
	_world->AddObject(home);
	EnemySpwaner<Enemy>* enemyS = new EnemySpwaner<Enemy>({0,0,10050},rManager->_render3D,80.0f, _world);
	_world->AddObject(enemyS);
}

void TitleScene::UpdateScene(double deltaTime,Game* game, RenderComponentManager* rManager)
{
	auto cam = _world->GetObjectWithTag<Camera>("Camera");
	Debug::Get()->NewFrame();
	_world->Update(deltaTime);
	Debug::Get()->Update();
	UpdateCollision(_world);
	

	rManager->GetGraphicApi()->Clear(0.2f,0.2f,0.2f,1.0f );
	rManager->GetGraphicApi()->SetDepthEnable(true);
	rManager->GetGraphicApi()->SetAlphaTestEnable(false);
	rManager->GetGraphicApi()->SetCullingMode(CULL_MODE_NONE);
	cam->SetCamera(rManager->GetGraphicApi());
	_world->Draw();
	Debug::Get()->Draw();
	rManager->GetGraphicApi()->Present();

	_world->CleanUp();
}

void TitleScene::UnInitScene(Game* game)
{
}
