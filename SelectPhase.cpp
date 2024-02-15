#include "SelectPhase.h"
#include "input.h"
#include "select.h"
#include "tower.h"
#include "BattlePhase.h"
#include "World.h"
#include "camera.h"
static TowerType type = TowerType::Normal;



void SelectPhase::EnterState(Player* Entity, DirectXAPI* api)
{
	Entity->topDownPosition = Entity->GetPosition() + Vec3(0.0f, 1500.0f, -1.0f);
	Entity->topDownRotation = Vec3(-D3DX_PI/2,0.0f, 0.0f);
}

void SelectPhase::StayState(Player* Entity, float deltaTime, DirectXAPI* api)
{

	auto cam = Entity->GetWorld()->GetObjectWithTag<Camera>("Camera");
	Entity->lerpT += deltaTime;
	if (Entity->lerpT >= 1.0f)
	{
		Entity->lerpT = 1.0f;
	}

	if (Entity->lerpT < 1)
	{
		Vec3 currentPosition, currentRotation;
		D3DXVec3Lerp(&currentPosition, &Entity->thirdPersonPosition, &Entity->topDownPosition, Entity->lerpT);
		D3DXVec3Lerp(&currentRotation, &Entity->thirdPersonRotation, &Entity->topDownRotation, Entity->lerpT);
		cam->SetPosition(currentPosition);
		cam->SetRotation(currentRotation);
	}
	else
	{
		
		if (GetKeyboardPress(DIK_W))
		{
			cam->SetPositionZ(cam->GetPosition().z + 30);
		}
		if (GetKeyboardPress(DIK_S))
		{
			cam->SetPositionZ(cam->GetPosition().z -30);
		}
		if (GetKeyboardPress(DIK_A))
		{
			cam->SetPositionX(cam->GetPosition().x - 30);
		}
		if (GetKeyboardPress(DIK_D))
		{
			cam->SetPositionX(cam->GetPosition().x + 30);
		}

		cam->SetCameraAt({ cam->GetPosition().x,0, cam->GetPosition().z + 1 }, false);



		if (GetKeyboardPress(DIK_F1))
		{
			type = TowerType::Normal;
		}
		else if (GetKeyboardPress(DIK_F2))
		{
			type = TowerType::Fire;
		}
		else if (GetKeyboardPress(DIK_F3))
		{
			type = TowerType::Light;
		}


		if (GetKeyboardTrigger(DIK_TAB))
		{
			Entity->fsm->ChangeState(BattlePhase::Instance());
		}

		cam->SetCamera(api);
	}
}

void SelectPhase::ExitState(Player* Entity, DirectXAPI* api)
{
	//GetSelect()->use = false;
}
