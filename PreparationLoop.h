#pragma once
#include "State.h"
class GameLoop;
class PreparationLoop :public State<GameLoop>
{
public:
	static PreparationLoop* Instance()
	{
		static PreparationLoop p;
		return &p;
	}

	void EnterState(GameLoop* Entity, DirectXAPI* api) override;
	void StayState(GameLoop* Entity, float deltaTime, DirectXAPI* api) override;
	void ExitState(GameLoop* Entity, DirectXAPI* api) override;

private:
	PreparationLoop() {}
	~PreparationLoop() {}

};