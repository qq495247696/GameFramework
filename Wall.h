#pragma once
#include <d3dx9.h>
#include "renderer.h"
struct Wall
{
	D3DXVECTOR3		pos;		
	D3DXCOLOR		color;		
	D3DXVECTOR3		size;
	D3DXVECTOR3		rot;
	D3DXVECTOR3		scl;
	D3DXMATRIX		 mtxWorld;
};


void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
