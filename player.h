//=============================================================================
//
// �n�ʏ��� [player.h]
// Author : 
//
//=============================================================================
#pragma once

#include <d3dx9.h>
#include "renderer.h"
#include "StateMachine.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************




class Player
{
public:
	D3DXVECTOR3		pos;		// �ʒu
	D3DXVECTOR3		rot;		// ����(��])
	D3DXVECTOR3		scl;		// �傫��(�X�P�[��)
	float			spd;		// �ړ��X�s�[�h
	bool			use;		// �\���t���O
	int				shadow;		// �e�̎��ʔԍ�

	D3DXVECTOR3     size;		// �����蔻��p�T�C�Y

	D3DXMATRIX		mtxWorld;	// ���[���h�}�g���b�N�X
	int				currency;
	int				se;
	float 		frame;

	void DrawAnim(float* frame, D3DXVECTOR3& rot, D3DXVECTOR3& pos);
	StateMachine<Player> fsm{this};
};
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player *GetPlayer(void);
