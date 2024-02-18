/*********************************************************************
 * \file   BattleLoop.cpp
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 18
 *********************************************************************/
#include "BattleLoop.h"
#include "enemy.h"
#include "enemy02.h"
#include "enemy03.h"
#include "EnemySpwaner.h"
#include "GameLoop.h"
#include "AssetManager.h"
#include "ResultScene.h"
#include "sound.h"
void BattleLoop::EnterState(GameLoop* Entity, DirectXAPI* api)
{
	SetVolume(AssetManager::Get()->_battleBgm, 0.7f);
	Entity->_turnTime = 70.0;


	switch (Entity->_wave)
	{
	case 1: {
		EnemySpwaner<Enemy>* enemyS = new EnemySpwaner<Enemy>({ 0,0,10050 }, Entity->_render, 60.0f, 5.5, Entity->_world,way._wayLine1);
		Entity->_world->AddObject(enemyS);
		break; }
	case 2: {
		EnemySpwaner<Enemy02>* enemyS02 = new EnemySpwaner<Enemy02>({ 0,0,10050 }, Entity->_render, 60.0f, 3.5, Entity->_world, way._wayLine2);
		Entity->_world->AddObject(enemyS02);
		break; }
	case 3: {
		EnemySpwaner<Enemy03>* enemyS03 = new EnemySpwaner<Enemy03>({ 0,0,10050 }, Entity->_render, 60.0f, 4.5, Entity->_world, way._wayLine1);
		Entity->_world->AddObject(enemyS03);
		break; }
	}
	
}

void BattleLoop::StayState(GameLoop* Entity, float deltaTime, DirectXAPI* api)
{
	Entity->_turnTime-=deltaTime;
	if (Entity->_turnTime <= 0)
	{
		Entity->_turnTime = 0;
		Entity->_fsm.ChangeState(PreparationLoop::Instance());
	}
}

void BattleLoop::ExitState(GameLoop* Entity, DirectXAPI* api)
{
	Entity->_wave += 1;
}
