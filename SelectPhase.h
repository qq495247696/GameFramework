#pragma once
#include "player.h"
#include "State.h"


class SelectPhase:public State<Player>
{
public:
	static SelectPhase* Instance()
	{
		static SelectPhase p;
		return &p;
	}

	void EnterState(Player* Entity) override;
	void StayState(Player* Entity) override;
	void ExitState(Player* Entity) override;

private:
	SelectPhase() {}
	~SelectPhase() {}


};

