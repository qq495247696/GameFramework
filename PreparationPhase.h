#pragma once
#include "State.h"
#include "player.h"
class PreparationPhase:public State<Player>
{
public:
	static PreparationPhase* Instance()
	{
		static PreparationPhase p;
		return &p;
	}

	void EnterState(Player* Entity, DirectXAPI* api) override;
	void StayState(Player* Entity, float deltaTime, DirectXAPI* api) override;
	void ExitState(Player* Entity, DirectXAPI* api) override;
private:
	PreparationPhase(){}
	~PreparationPhase(){}


};
