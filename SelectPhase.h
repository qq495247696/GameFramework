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

	void EnterState(Player* Entity, DirectXAPI* api) override;
	void StayState(Player* Entity, float deltaTime, DirectXAPI* api) override;
	void ExitState(Player* Entity, DirectXAPI* api) override;

private:
	SelectPhase() {}
	~SelectPhase() {}


};

