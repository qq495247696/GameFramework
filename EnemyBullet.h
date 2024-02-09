#pragma once
#include "renderer.h"

class EnemyBullet
{
public:
	D3DXMATRIX				mtxWorld;
	bool					use;	// true:�g���Ă���  false:���g�p
	D3DXVECTOR3				pos;	// �o���b�g�̍��W
	D3DXVECTOR3				dir;	
	D3DXVECTOR3				rot;
	D3DXVECTOR3				scl;
	float					speed;	// �o���b�g�̈ړ��X�s�[�h
	float					frame;	// �t���[����

	D3DXVECTOR3     size;		// �����蔻��p�T�C�Y
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitEnemyBullet(void);
void UninitEnemyBullet(void);
void UpdateEnemyBullet(void);
void DrawEnemyBullet(void);

EnemyBullet* GetEnemyBullet(void);
void SetEnemyBullet(D3DXVECTOR3 pos, D3DXVECTOR3 dir);