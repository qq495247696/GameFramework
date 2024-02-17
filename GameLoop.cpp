#include "GameLoop.h"
#include "EnemySpwaner.h"
#include "Enemy.h"
#include "Render.h"

void GameLoop::Update(float deltaTime)
{
	_fsm.Update(deltaTime);
}
