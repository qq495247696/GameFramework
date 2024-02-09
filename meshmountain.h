//=============================================================================
//
// ���b�V���R���� [meshmountain.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitMeshMountain(D3DXVECTOR3 pos, D3DXVECTOR3 rot, 
	int numBlockH, int numBlockV, float sizeBlockH, float sizeBlockV,
	float texSizeX = 0.25f, float texSizeZ = 1.0f);
void UninitMeshMountain(void);
void UpdateMeshMountain(void);
void DrawMeshMountain(void);
