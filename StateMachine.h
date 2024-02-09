/*********************************************************************
 * \file   StateMachine.h
 * \brief   
 * \author マ　コウリュウ
 * \date   2024 \ 01 \ 17
 *********************************************************************/
#pragma once
#include "State.h"
template<typename GameEntity>
class StateMachine
{
public:
	StateMachine(GameEntity* pEntity):_entity(pEntity){}
	~StateMachine(){}

	void Update()
	{
		if (_GlobalState != nullptr)
		{
			_GlobalState->StayState(_entity);
		}

		if (_CurrentState != nullptr)
		{
			_CurrentState->StayState(_entity);
		}
	}

	bool ChangeState(State<GameEntity>* newState)
	{
		if (newState !=nullptr)
		{
			_PreviousState = _CurrentState;
			_CurrentState->ExitState(_entity);
			_CurrentState = newState;
			_CurrentState->EnterState(_entity);
			return true;
		}
		return false;
	}

	bool ReturnToPreviousState()
	{
		return ChangeState(_PreviousState);
	}

	State<GameEntity>* GetCurrentState()const { return _CurrentState; }
	State<GameEntity>* GetGlobalState()const { return _GlobalState; }
	State<GameEntity>* GetPreviousState()const { return _PreviousState; }
	void SetCurrentState(State<GameEntity>* s) { _CurrentState = s; }
	void SetGlobalState(State<GameEntity>* s) { _GlobalState = s; }
	void SetPreviousState(State<GameEntity>* s) { _PreviousState = s; }

private:
	State<GameEntity>* _CurrentState;
	State<GameEntity>* _GlobalState;
	State<GameEntity>* _PreviousState;
	GameEntity* _entity;
};
