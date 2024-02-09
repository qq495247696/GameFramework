//=============================================================================
//
// �|�����C������ [polyline.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPolyLine(void);
void UninitPolyLine(void);
void UpdatePolyLine(void);
void DrawPolyLine(void);

int SetPolyLine(D3DXVECTOR3 begin, D3DXVECTOR3 end, float width);
void ReleasePolyLine(int index);
void SetPositionPolyLine(int index, D3DXVECTOR3 begin, D3DXVECTOR3 end);
void SetColorPolyLine(int index, D3DXCOLOR col);
