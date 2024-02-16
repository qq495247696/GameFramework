//=============================================================================
//
// ƒ|ƒŠƒSƒ“•\Ž¦ˆ— [NormalTower.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "NormalTower.h"
#include "texture.h"
#include "Enemybullet.h"
#include "shadow.h"
#include "polyline.h"
#include "sound.h"
#include "BattlePhase.h"


HRESULT InitTower(void)
{

		//g_Tower[i].shadow = SetShadow(D3DXVECTOR3(g_Tower[i].pos.x, 0.0f, g_Tower[i].pos.z), 80.0f);
	return S_OK;
}



void NormalTower::Update(double deltaTime)
{
	D3DXVECTOR3 x = { 0.0,0.0,1.0 };
	time+=deltaTime;
	if (time > 1.5)
	{
		D3DXVECTOR4 pOut;
		D3DXMATRIX rot;
		D3DXMatrixIdentity(&rot);
		D3DXMatrixRotationY(&rot, _rotate.y);
		D3DXVec3Transform(&pOut, &x, &rot);
		//SetEnemyBullet(_position, { pOut.x,0,pOut.z });
		time = 0;
	}
}

void NormalTower::Draw()
{
	_renderComponent->Draw(this);
}

bool NormalTower::Discard() const
{
	return false;
}
