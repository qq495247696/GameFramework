/*********************************************************************
 * \file   State.h
 * \brief   
 * \author �ޡ�������奦
 * \date   2024 \ 01 \ 17
 *********************************************************************/
#pragma once
#ifndef STATE_H_
#define STATE_H_
#define	VALUE_MOVE		(5.0f)						// �ړ���
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)			// ��]��

template<typename Object>
class State
{
public:
	State() = default;
	virtual ~State() { ; }								
	virtual void EnterState(Object* Entity) = 0;
	virtual void StayState(Object* Entity) = 0;
	virtual void ExitState(Object* Entity) = 0;
};
#endif // !STATE_H