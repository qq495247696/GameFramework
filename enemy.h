//=============================================================================
//
// �n�ʏ��� [enemy.h]
// Author : 
//
//=============================================================================
#pragma once

#include <d3dx9.h>
#include "renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ENEMY_NUM 20

class Enemy
{
public:

	Enemy() = default;
	~Enemy(){}
	void Update();
	void Draw();
	D3DXVECTOR3		pos;		// �ʒu
	D3DXVECTOR3		rot;		// ����(��])
	D3DXVECTOR3		scl;		// �傫��(�X�P�[��)
	D3DXVECTOR3		vel;		// �ړ�����
	float			spd;		// �ړ��X�s�[�h
	bool			use;		// �\���t���O
	int				shadow;		// �e�̎��ʔԍ�
	D3DXVECTOR3     size;		// �����蔻��p�T�C�Y



	D3DXMATRIX		mtxWorld;	// ���[���h�}�g���b�N�X


};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 dir, int time);

Enemy *GetEnemy(void);
