#pragma once
#include"World.h"
#include "StateMachine.h"
#include "PreparationLoop.h"
#include "BattleLoop.h"
class GameLoop
{
public:
	GameLoop(World* world,Render *render):_world(world), _turn(1), _turnTime(30.0f),_battle(false),_render(render)
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
private:
	int							_turn;
	int							_enemyNum;
	float						_turnTime;
	World*						_world;
	Render*						_render;
	bool						_battle;
	StateMachine<GameLoop>		_fsm{ this,nullptr };
};

