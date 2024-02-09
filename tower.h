//=============================================================================
//
// �n�ʏ��� [Tower.h]
// Author : 
//
//=============================================================================
#pragma once

#include <d3dx9.h>
#include "renderer.h"
#include "StateMachine.h"
#include "model.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

enum TowerType
{
	Normal,
	Fire,
	Light,
};

class Tower
{
public:
	D3DXVECTOR3		pos;		// �ʒu
	D3DXVECTOR3		rot;		// ����(��])
	D3DXVECTOR3		scl;		// �傫��(�X�P�[��)
	float			spd;		// �ړ��X�s�[�h
	bool			use;		// �\���t���O
	int				shadow;		// �e�̎��ʔԍ�
	int				time;
	D3DXVECTOR3     size;		// �����蔻��p�T�C�Y
	DX11_MODEL*     model;

	D3DXMATRIX		mtxWorld;	// ���[���h�}�g���b�N�X
};
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTower(void);
void UninitTower(void);
void UpdateTower(void);
void DrawTower(void);
Tower *GetTower(void);
void SetTower(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TowerType type);
