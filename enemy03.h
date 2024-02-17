/*********************************************************************
 * \file   enemy.h
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#pragma once
#include "object.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ENEMY_NUM 20

class Enemy03:public Object
{
public:

	Enemy03(DX11_MODEL* model,const Vec3& Pos ,Render* render, D3DXVECTOR3* wayLine,World* world) :Object(model, render, "Enemy03",world),_wayLine(wayLine)
	{
		_position = Pos;
		_rotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		_scale = D3DXVECTOR3(3.0f, 3.0f, 3.0f);
		_vel = D3DXVECTOR3(0, 0.0f, 0);
		_speed = 350.0f;
		_use = false;
		_target = 0;
		_size = D3DXVECTOR3(35.0f, 50.0f, 35.0f);
		//������P�ʃx�N�g��������
		D3DXVec3Normalize(&_vel, &_vel);
	}
	~Enemy03()override
	{
		
	}
	bool			_use;		// �\���t���O
	int				_shadow;		// �e�̎��ʔԍ�
	D3DXVECTOR3     _size;		// �����蔻��p�T�C�Y
	D3DXVECTOR3*	_wayLine;
	int				_target;
	int				_hp;

	// ͨ�� Object �̳�
	void Update(double deltaTime) override;
	void motor(double deltaTime);
	void Draw()override;
	bool Discard() const override;

};

