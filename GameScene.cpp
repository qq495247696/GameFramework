/*********************************************************************
 * \file   GameScene.cpp
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#include "GameScene.h"
#include "game.h"
#include "RenderComponent.h"
#include "EnemyBullet.h"
#include "camera.h"
#include "Wall.h"
#include "bullet.h"
#include "meshfield.h"
#include "Home.h"
#include "enemy.h"
#include "EnemySpwaner.h"
#include "Debug.h"
#include "AssetManager.h"
#include "collision.h"
#include "Render2D.h"
#include "Render3D.h"
#include "meshsky.h"
#include "BackgroundUI.h"
#include "Health.h"
void GameScene::InitScene(Game* game, RenderComponentManager* rManager)
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
	FieldMesh* field = new FieldMesh(AssetManager::Get()->_feildTexNo, rManager->GetGraphicApi(), D3DXVECTOR3(0.0f, 0.0f, 3000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100, 100, { 180.0f, 180.0f }, _world);
	_world->AddObject(field);
	SkyBox* skyBox = new SkyBox(AssetManager::Get()->_skyBoxTexNo, rManager->GetGraphicApi(), D3DXVECTOR3(0.0f, 0.0f, 3000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10000.0f, 16, 8, _world);
	_world->AddObject(skyBox);
	Home* home = new Home(&AssetManager::Get()->_home, rManager->_render3D, _world);
	_world->AddObject(home);
	EnemySpwaner<Enemy>* enemyS = new EnemySpwaner<Enemy>({ 0,0,10050 }, rManager->_render3D, 80.0f, _world);
	_world->AddObject(enemyS);

	Health* hp = new Health(AssetManager::Get()->_front, rManager->_render2D, _world, nullptr);
	BackgroundUi* bg = new BackgroundUi(AssetManager::Get()->_backGroundTexNo, rManager->_render2D,_world, hp);
	_world->AddObject(bg);
}

void GameScene::UpdateScene(double deltaTime,Game* game, RenderComponentManager* rManager)
{
	auto cam = _world->GetObjectWithTag<Camera>("Camera");
	Debug::Get()->NewFrame();
	_world->Update(deltaTime);
	Debug::Get()->Update();
	UpdateCollision(_world);


	rManager->GetGraphicApi()->Clear(0.2f, 0.2f, 0.2f, 1.0f);
	rManager->GetGraphicApi()->SetDepthEnable(true);
	rManager->GetGraphicApi()->SetAlphaTestEnable(false);
	rManager->GetGraphicApi()->SetCullingMode(CULL_MODE_NONE);
	cam->SetCamera(rManager->GetGraphicApi());
	_world->Draw();
	Debug::Get()->Draw();
	rManager->GetGraphicApi()->Present();

	_world->CleanUp();
}

void GameScene::UnInitScene(Game* game)
{
	
}
