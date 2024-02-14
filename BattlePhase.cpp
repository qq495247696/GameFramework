#include "BattlePhase.h"
#include "input.h"
#include "shadow.h"
#include "camera.h"
#include "bullet.h"
#include "sound.h"
#include "select.h"
#include "player.h"
#include "World.h"
#include "DirectXAPI.h"

static float g_Rot;
void BattlePhase::EnterState(Player* Entity, DirectXAPI* api)
{
	//GetSelect()->use = false;
	auto cam = Entity->GetWorld()->GetObjectWithTag<Camera>("Camera");
	cam->SetCameraAt(Entity->GetPosition(), true);
	cam->SetCamera(api);
}

void BattlePhase::StayState(Player* Entity, float deltaTime, DirectXAPI* api)
{

	auto cam = Entity->GetWorld()->GetObjectWithTag<Camera>("Camera");
	//Camera* cam = GetCamera();
	//if (cam->pos.y < 100)
	//{
	//	cam->pos.y = 100;
	//}
	//if (cam->pos.y == 100 )
	//{
		//ˆÚ“®‘¬“x‚ÌŒ¸Šˆ—
		Entity->SetSpeed(Entity->GetSpeed()*0.9);

		if (GetKeyboardPress(DIK_LEFT))
		{
			//Entity->spd = VALUE_MOVE;
			g_Rot += -D3DX_PI / 90;
		}
		if (GetKeyboardPress(DIK_RIGHT))
		{
			//Entity->spd = VALUE_MOVE;
			g_Rot += D3DX_PI / 90;
		}
		if (GetKeyboardPress(DIK_UP))
		{
			Entity->SetSpeed(VALUE_MOVE);
			//g_Rot = 0.0f;
		}
		if (GetKeyboardPress(DIK_DOWN))
		{
			Entity->SetSpeed(-VALUE_MOVE);
			//g_Rot = D3DX_PI;
		}

		{
			Entity->SetRotation({ 0,g_Rot,0 }); //+ cam->rot.y;
			cam->SetRotation({ 0,Entity->GetRotation().y,0 });
			Entity->SetPositionX(Entity->GetPosition().x + sinf(Entity->GetRotation().y) * Entity->GetSpeed() * deltaTime);
			Entity->SetPositionZ(Entity->GetPosition().z + cosf(Entity->GetRotation().y) * Entity->GetSpeed() * deltaTime);
		}

		cam->SetCameraAt({ Entity->GetPosition().x,0, Entity->GetPosition().z }, true);
	//	// ’e‚ðŒ‚‚Â
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

void BattlePhase::ExitState(Player* Entity, DirectXAPI* api)
{
}
