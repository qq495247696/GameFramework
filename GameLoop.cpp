/*********************************************************************
 * \file   GameLoop.cpp
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 18
 *********************************************************************/
#include "GameLoop.h"
#include "EnemySpwaner.h"
#include "Enemy.h"
#include "Render.h"

void GameLoop::Update(float deltaTime)
{
	UiEvent	e;
	_fsm.Update(deltaTime);
	e._time = _turnTime;
	e._wave = _wave;
	_obsever.Notify(e);

}
