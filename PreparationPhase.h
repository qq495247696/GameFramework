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

	void EnterState(Player* Entity) override;
	void StayState(Player* Entity) override;
	void ExitState(Player* Entity) override;
private:
	PreparationPhase(){}
	~PreparationPhase(){}


};
