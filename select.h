//=============================================================================
//
// �n�ʏ��� [Select.h]
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
class Select
{
public:
	D3DXVECTOR3		pos;		// �ʒu
	D3DXVECTOR3		rot;		// ����(��])
	D3DXVECTOR3		scl;		// �傫��(�X�P�[��)
	bool			use;		// �\���t���O
	D3DXVECTOR3     size;		// �����蔻��p�T�C�Y

	D3DXMATRIX		mtxWorld;	// ���[���h�}�g���b�N�X
};
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSelect(void);
void UninitSelect(void);
void UpdateSelect(void);
void DrawSelect(void);
Select *GetSelect(void);
DX11_MODEL* GetSelectModel(void);
