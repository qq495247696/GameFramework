/*********************************************************************
 * \file   BattleLoop.h
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 18
 *********************************************************************/
#pragma once
#include "State.h"
class GameLoop;
class BattleLoop :public State<GameLoop>
{
public:
	static BattleLoop* Instance()
	{
		static BattleLoop p;
		return &p;
	}

	void EnterState(GameLoop* Entity, DirectXAPI* api) override;
	void StayState(GameLoop* Entity, float deltaTime, DirectXAPI* api) override;
	void ExitState(GameLoop* Entity, DirectXAPI* api) override;

private:
	BattleLoop() {}
	~BattleLoop() {}


};