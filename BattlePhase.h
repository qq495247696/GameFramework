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

	void EnterState(Player* Entity, DirectXAPI* api) override;
	void StayState(Player* Entity, float deltaTime, DirectXAPI* api) override;
	void ExitState(Player* Entity, DirectXAPI* api) override;
private:
	BattlePhase() {}
	~BattlePhase() {}
};

