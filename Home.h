#pragma once

#include <d3dx9.h>
#include "renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
struct Home
{
	D3DXVECTOR3		pos;		// �ʒu
	D3DXVECTOR3		rot;		// ����(��])
	D3DXVECTOR3		scl;		// �傫��(�X�P�[��)
	bool			use;		// �\���t���O
	int				hp;
	unsigned int    hitedSound;

	D3DXVECTOR3     size;		// �����蔻��p�T�C�Y

	D3DXMATRIX		mtxWorld;	// ���[���h�}�g���b�N�X
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitHome(void);
void UninitHome(void);
void UpdateHome(void);
void DrawHome(void);

Home* GetHome(void);
