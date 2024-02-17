#include "BattleLoop.h"
#include "enemy.h"
#include "EnemySpwaner.h"
#include "GameLoop.h"
#include "AssetManager.h"
#include "sound.h"
void BattleLoop::EnterState(GameLoop* Entity, DirectXAPI* api)
{
	SetVolume(AssetManager::Get()->_battleBgm, 0.7f);
	Entity->_turnTime = 70.0;
	EnemySpwaner<Enemy>* enemyS = new EnemySpwaner<Enemy>({ 0,0,10050 }, Entity->_render, 60.0f, Entity ->_world);
	Entity->_world->AddObject(enemyS);
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
