#include "BattlePhase.h"
#include "input.h"
#include "shadow.h"
#include "camera.h"
#include "bullet.h"
#include "sound.h"
#include "select.h"


static float g_Rot;
void BattlePhase::EnterState(Player* Entity)
{
	/*GetSelect()->use = false;
	SetCameraAT(Entity->pos,true);
	SetCamera();*/
}

void BattlePhase::StayState(Player* Entity)
{

	
	//Camera* cam = GetCamera();

	if (5> 100)
	{
		
	}
	//if (cam->pos.y < 100)
	//{
	//	cam->pos.y = 100;
	//}
	//if (cam->pos.y == 100 )
	//{
	//	//移動速度の減衰処理
	//	Entity->spd *= 0.9f;

	//	if (GetKeyboardPress(DIK_LEFT))
	//	{
	//		//Entity->spd = VALUE_MOVE;
	//		g_Rot += -D3DX_PI / 90;
	//	}
	//	if (GetKeyboardPress(DIK_RIGHT))
	//	{
	//		//Entity->spd = VALUE_MOVE;
	//		g_Rot += D3DX_PI / 90;
	//	}
	//	if (GetKeyboardPress(DIK_UP))
	//	{
	//		Entity->spd = VALUE_MOVE;
	//		//g_Rot = 0.0f;
	//	}
	//	if (GetKeyboardPress(DIK_DOWN))
	//	{
	//		Entity->spd = -VALUE_MOVE;
	//		//g_Rot = D3DX_PI;
	//	}

	//	{	// 押した方向にプレイヤーを移動させる
	//		// 押した方向にプレイヤーを向かせている所
	//		Entity->rot.y = g_Rot; //+ cam->rot.y;
	//		cam->rot.y = Entity->rot.y;
	//		Entity->pos.x += sinf(Entity->rot.y) * Entity->spd;
	//		Entity->pos.z += cosf(Entity->rot.y) * Entity->spd;
	//	}

	//	SetCameraAT({ Entity->pos.x,0,Entity->pos.z }, true);
	//	// 弾を撃つ
	//	if (GetKeyboardTrigger(DIK_SPACE))
	//	{
	//		D3DXVECTOR3 dir;
	//		dir.x = cosf(Entity->rot.y - (D3DX_PI / 2));
	//		dir.y = 0.0f;
	//		dir.z = sinf(Entity->rot.y + (D3DX_PI / 2));
	//		SetBullet(Entity->pos, dir);
	//		PlaySound(Entity->se, 0);

	//	}
	//}
}

void BattlePhase::ExitState(Player* Entity)
{
}
