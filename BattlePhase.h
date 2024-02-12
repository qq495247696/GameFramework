#pragma once
#include "State.h"
class Player;
class BattlePhase:public State<Player>
{
public:
	static BattlePhase* Instance()
	{
		static BattlePhase p;
		return &p;
	}

	void EnterState(Player* Entity) override;
	void StayState(Player* Entity) override;
	void ExitState(Player* Entity) override;
private:
	BattlePhase() {}
	~BattlePhase() {}
};

