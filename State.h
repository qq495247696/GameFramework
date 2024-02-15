/*********************************************************************
 * \file   State.h
 * \brief   
 * \author ¥Þ¡¡¥³¥¦¥ê¥å¥¦
 * \date   2024 \ 01 \ 17
 *********************************************************************/
#pragma once
#ifndef STATE_H_
#define STATE_H_
#define	VALUE_MOVE		(1350.0f)						// ˆÚ“®—Ê
#define	VALUE_ROTATE	(D3DX_PI * 0.03f)			// ‰ñ“]—Ê

class DirectXAPI;
template<typename Object>
class State
{
public:
	State() = default;
	virtual ~State() { ; }								
	virtual void EnterState(Object* Entity, DirectXAPI* api) = 0;
	virtual void StayState(Object* Entity,float deltaTime, DirectXAPI* api) = 0;
	virtual void ExitState(Object* Entity, DirectXAPI* api) = 0;
};
#endif // !STATE_H