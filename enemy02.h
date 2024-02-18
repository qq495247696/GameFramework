/*********************************************************************
 * \file   enemy.h
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#pragma once
#include "object.h"
#include "AssetManager.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

class Enemy02:public Object
{
public:

	Enemy02(const Vec3& Pos ,Render* render, D3DXVECTOR3* wayLine,World* world) :Object(&AssetManager::Get()->_enemy02, render, "Enemy",world),_wayLine(wayLine), _attackTime(0.0), _atk(60)
	{
		_position = Pos;
		_rotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		_scale = D3DXVECTOR3(3.0f, 3.0f, 3.0f);
		_vel = D3DXVECTOR3(0, 0.0f, 0);
		_speed = 250.0f;
		_use = false;
		_target = 0;
		_hp = 2800;
		_size = D3DXVECTOR3(35.0f, 50.0f, 35.0f);
		//������P�ʃx�N�g��������
		D3DXVec3Normalize(&_vel, &_vel);
	}
	~Enemy02()override
	{
		
	}
	bool			_use;		// �\���t���O
	int				_shadow;		// �e�̎��ʔԍ�
	D3DXVECTOR3     _size;		// �����蔻��p�T�C�Y
	D3DXVECTOR3*	_wayLine;
	int				_target;
	double			_attackTime;
	int				_atk;


	// ͨ�� Object �̳�
	void Update(double deltaTime) override;
	void motor(double deltaTime);
	void Draw()override;
	bool Discard() const override;

};

