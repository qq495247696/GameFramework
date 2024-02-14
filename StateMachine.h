/*********************************************************************
 * \file   StateMachine.h
 * \brief   
 * \author マ　コウリュウ
 * \date   2024 \ 01 \ 17
 *********************************************************************/
#pragma once
#include "State.h"

template<class Object>
class StateMachine
{
public:
	StateMachine(Object* pEntity,DirectXAPI* api):_entity(pEntity),_api(api){}
	~StateMachine(){}

	void Update(float deltaTime)
	{
		if (_GlobalState != nullptr)
		{
			_GlobalState->StayState(_entity, deltaTime, _api);
		}

		if (_CurrentState != nullptr)
		{
			_CurrentState->StayState(_entity,deltaTime, _api);
		}
	}

	bool ChangeState(State<Object>* newState)
	{
		if (newState !=nullptr)
		{
			_PreviousState = _CurrentState;
			_CurrentState->ExitState(_entity, _api);
			_CurrentState = newState;
			_CurrentState->EnterState(_entity,_api);
			return true;
		}
		return false;
	}

	bool ReturnToPreviousState()
	{
		return ChangeState(_PreviousState);
	}

	State<Object>* GetCurrentState()const { return _CurrentState; }
	State<Object>* GetGlobalState()const { return _GlobalState; }
	State<Object>* GetPreviousState()const { return _PreviousState; }
	void SetCurrentState(State<Object>* s) { _CurrentState = s; }
	void SetGlobalState(State<Object>* s) { _GlobalState = s; }
	void SetPreviousState(State<Object>* s) { _PreviousState = s; }
private:
	State<Object>*		_CurrentState;
	State<Object>*		_GlobalState = nullptr;
	State<Object>*		_PreviousState;
	Object*				_entity;
	DirectXAPI*			 _api;
};
