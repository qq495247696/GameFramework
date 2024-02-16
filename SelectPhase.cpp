#include "SelectPhase.h"
#include "input.h"
#include "NormalTower.h"
#include "BattlePhase.h"
#include "World.h"
#include "camera.h"
#include "EmptyObject.h"
#include "Player.h"
#include "AssetManager.h"

static EmptyObject* selectmode;
static TowerType type = TowerType::Normal;
void SelectPhase::EnterState(Player* Entity, DirectXAPI* api)
{
	auto cam = Entity->GetWorld()->GetObjectWithTag<Camera>("Camera");
	Entity->topDownPosition = Entity->GetPosition() + Vec3(0.0f, 1500.0f, -1.0f);
	Entity->topDownRotation = Vec3(-D3DX_PI/2,0.0f, 0.0f);
	selectmode = new EmptyObject(api, Entity->GetWorld());
	selectmode->SetPosition({ Entity->GetPosition().x, 0, Entity->GetPosition().z + 1 });
	selectmode->SetModel(&AssetManager::Get()->_selectNormalTower);
	for (int i = 0; i < selectmode->GetModel()->SubsetNum; i++)
	{
		selectmode->GetModel()->SubsetArray[i].Material.Material.Diffuse = { 1,0,0,0.5f };
	}
	Entity->GetWorld()->AddObject(selectmode);
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

		selectmode->SetPosition({ cam->GetPosition().x,0, cam->GetPosition().z + 1 });
		cam->SetCameraAt({ cam->GetPosition().x,0, cam->GetPosition().z + 1 }, false);
		


		//防御タワー型スイッチ
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
		switch (type)
		{
		case Normal:
			selectmode->SetModel(&AssetManager::Get()->_selectNormalTower);
			for (int i = 0; i < selectmode->GetModel()->SubsetNum; i++)
			{
				selectmode->GetModel()->SubsetArray[i].Material.Material.Diffuse = { 1,0,0,0.5f };
			}
			break;
		case Fire:
			selectmode->SetModel(&AssetManager::Get()->_selectFireTower);
			for (int i = 0; i < selectmode->GetModel()->SubsetNum; i++)
			{
				selectmode->GetModel()->SubsetArray[i].Material.Material.Diffuse = { 1,0,0,0.5f };
			}
			break;
		case Light:
			selectmode->SetModel(&AssetManager::Get()->_selectThunderTower);
			for (int i = 0; i < selectmode->GetModel()->SubsetNum; i++)
			{
				selectmode->GetModel()->SubsetArray[i].Material.Material.Diffuse = { 1,0,0,0.5f };
			}
			break;
		}

		//状態を変更する
		if (IsMouseLeftTriggered())
		{
			switch (type)
			{
			case Normal:
				NormalTower* nTower=new NormalTower(&AssetManager::Get()->_normalTower, Entity->GetComponent(), Entity->GetWorld());
				nTower->SetPosition({ cam->GetPosition().x,0, cam->GetPosition().z + 1 });
				Entity->GetWorld()->AddObject(nTower);
				break;
		/*	case Fire:
				break;
			case Light:
				break;*/
		/*	default:
				break;*/
			}
			
			Entity->fsm->ChangeState(BattlePhase::Instance());
		}

		cam->SetCamera(api);
	}
}

void SelectPhase::ExitState(Player* Entity, DirectXAPI* api)
{
	selectmode->SetUse(false);
}
