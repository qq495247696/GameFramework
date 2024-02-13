//=============================================================================
//
// �e���� [shadow.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"
#include "render.h"


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);

int SetShadow(D3DXVECTOR3 pos, float size);
void ReleaseShadow(int index);
void SetPositionShadow(int index, D3DXVECTOR3 pos);
void SetColorShadow(int index, D3DXCOLOR col);
