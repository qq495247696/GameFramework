//=============================================================================
//
// �e���� [bullet.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"
#include "render.h"
#include "object.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BULLET_NUM		(10)		// �o���b�g��Max��
#define BULLET_SPEED	(10.0f)		// �o���b�g�̈ړ��X�s�[�h


// �o���b�g�\����
class Bullet:public Object
{
public:
	Bullet(DX11_MODEL* model, Render* render,World* world) :Object(model, render, "Bullet",world) 
	{
	
	};
	~Bullet()override {}
	float					frame;	// �t���[����
	int						shadow;	// �e�̎��ʔԍ�
	D3DXVECTOR3     size;		// �����蔻��p�T�C�Y

	void Update(double deltaTime) override;
	void Draw() override;
	bool Discard() const override;

};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

Bullet *GetBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 dir);

