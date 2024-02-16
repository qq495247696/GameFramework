/*********************************************************************
 * \file   SelectPhase.h
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#pragma once
#include "State.h"

class Player;
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

