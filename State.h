/*********************************************************************
 * \file   State.h
 * \brief   
 * \author ¥Þ¡¡¥³¥¦¥ê¥å¥¦
 * \date   2024 \ 01 \ 17
 *********************************************************************/
#pragma once
#ifndef STATE_H_
#define STATE_H_
#define	VALUE_MOVE		(5.0f)						// ˆÚ“®—Ê
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)			// ‰ñ“]—Ê

template<class GameEntity>
class State
{
public:
	virtual ~State() { ; }								
	virtual void EnterState(GameEntity* Entity) = 0;
	virtual void StayState(GameEntity* Entity) = 0;
	virtual void ExitState(GameEntity* Entity) = 0;
};
#endif // !STATE_H