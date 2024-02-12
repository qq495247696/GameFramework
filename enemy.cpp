//=============================================================================
//
// �|���S���\������ [enemy.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "enemy.h"
#include "texture.h"
#include "player.h"
#include "shadow.h"
#include <random>
#include "BattlePhase.h"
#include "PreparationPhase.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	VALUE_MOVE		(5.0f)						// �ړ���
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)			// ��]��
void Enemy::Update(double deltaTime)
{
	_position += _vel * _speed * deltaTime;

}

void Enemy::Draw()
{
	_renderComponent->Draw(this);
}

bool Enemy::Discard() const
{
	return false;
}
