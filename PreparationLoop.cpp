#include "PreparationLoop.h"
#include "GameLoop.h"
#include "sound.h"
#include "AssetManager.h"
void PreparationLoop::EnterState(GameLoop* Entity, DirectXAPI* api)
{
	Entity->_turnTime= 30.0f;
	SetVolume(AssetManager::Get()->_battleBgm, 0.3f);
}

void PreparationLoop::StayState(GameLoop* Entity, float deltaTime, DirectXAPI* api)
{
	Entity->_turnTime -= deltaTime;

	if (Entity->_turnTime <= 0)
	{
		Entity->_turnTime = 0;
		Entity->_fsm.ChangeState(BattleLoop::Instance());
	}
}

void PreparationLoop::ExitState(GameLoop* Entity, DirectXAPI* api)
{
}
