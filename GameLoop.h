#pragma once
#include"World.h"
#include "StateMachine.h"
#include "PreparationLoop.h"
#include "BattleLoop.h"
#include "UiInfoObsever.h"
class GameLoop
{
public:
	GameLoop(World* world,Render *render):_world(world), _wave(1), _turnTime(40.0f),_battle(false),_render(render)
	{
		_fsm.SetCurrentState(PreparationLoop::Instance());
		_fsm.ChangeState(PreparationLoop::Instance());
	}

	~GameLoop()
	{
	}
	void Update(float deltaTime);

	friend PreparationLoop;
	friend BattleLoop;
	UiInfoObsever				_obsever;
	const int GetWave()const { return _wave; }
private:
	int							_wave;
	int							_enemyNum;
	double						_turnTime;
	World*						_world;
	Render*						_render;
	bool						_battle;
	StateMachine<GameLoop>		_fsm{ this,nullptr };
};

