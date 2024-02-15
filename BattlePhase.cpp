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
#include "SelectPhase.h"

static float g_Rot;
void BattlePhase::EnterState(Player* Entity, DirectXAPI* api)
{
	auto cam = Entity->GetWorld()->GetObjectWithTag<Camera>("Camera");
	cam->SetCameraAt(Entity->GetPosition(), true);
	cam->SetCamera(api);
}

void BattlePhase::StayState(Player* Entity, float deltaTime, DirectXAPI* api)
{
	Entity->lerpT -= deltaTime;
	if (Entity->lerpT <= 0)
	{
		Entity->lerpT = 0;
	}



	auto cam = Entity->GetWorld()->GetObjectWithTag<Camera>("Camera");
	//ˆÚ“®‘¬“x‚ÌŒ¸Šˆ—
	Entity->SetSpeed(Entity->GetSpeed()*0.9);
	if (GetMouseX()<0)
	{
		g_Rot += -D3DX_PI / 90;
	}
	if (GetMouseX()>0)
	{
		g_Rot += D3DX_PI / 90;
	}
	if (GetKeyboardPress(DIK_W))
	{
		Entity->SetVel({ 0,0,1 });
		Entity->SetSpeed(1350);
	}
	if (GetKeyboardPress(DIK_S))
	{
		Entity->SetVel({ 0,0,-1 });
		Entity->SetSpeed(1350);
	}

	{
		//Camera
		Entity->SetRotation({ 0,g_Rot,0 }); 
		
		
		Vec3 cameraOffset = Vec3(0.0f, 150.0f, -400.0f);
		Vec3 finalPosition;
		D3DXVECTOR4 rotateOffset, playerVel;
		D3DXMATRIX rotationMatrix;
		D3DXMatrixRotationYawPitchRoll(&rotationMatrix, Entity->GetRotation().y, 0, 0);
		D3DXVec3Transform(&playerVel, &Entity->GetVel(), &rotationMatrix);
		Entity->SetPosition(Entity->GetPosition()+Vec3{playerVel.x,playerVel.y ,playerVel.z } *Entity->GetSpeed()* deltaTime);
		D3DXVec3Transform(&rotateOffset, &cameraOffset, &rotationMatrix);
		Entity->topDownPosition = Entity->GetPosition() + Vec3(0.0f, 400.0f, 0.0f);
		Entity->topDownRotation = Vec3(-D3DX_PI / 2, 0.0f, 0.0f);
		Entity->thirdPersonRotation = { 0, Entity->GetRotation().y, 0 };
		Entity->thirdPersonPosition = { Entity->GetPosition() + Vec3{ rotateOffset.x,rotateOffset.y,rotateOffset.z } };
		Vec3 currentPosition, currentRotation;
		D3DXVec3Lerp(&currentPosition, &Entity->thirdPersonPosition, &Entity->topDownPosition, Entity->lerpT);
		D3DXVec3Lerp(&currentRotation, &Entity->thirdPersonRotation, &Entity->topDownRotation, Entity->lerpT);
		cam->SetPosition(currentPosition);
		cam->SetRotation(currentRotation);
		
	}
	cam->SetCameraAt({ Entity->GetPosition().x,0, Entity->GetPosition().z }, false);
	
	if (GetKeyboardTrigger(DIK_1))
	{
		Entity->fsm->ChangeState(SelectPhase::Instance());
	}
	

	/*if (GetKeyboardTrigger(DIK_SPACE))
	{
		D3DXVECTOR3 dir;
		dir.x = cosf(Entity->rot.y - (D3DX_PI / 2));
		dir.y = 0.0f;
		dir.z = sinf(Entity->rot.y + (D3DX_PI / 2));
		SetBullet(Entity->pos, dir);
		PlaySound(Entity->se, 0);

	}*/
	
}

void BattlePhase::ExitState(Player* Entity, DirectXAPI* api)
{
}
