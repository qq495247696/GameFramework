#include "SelectPhase.h"
#include "input.h"
#include "select.h"
#include "tower.h"
#include "PreparationPhase.h"
static TowerType type = TowerType::Normal;
void SelectPhase::EnterState(Player* Entity)
{

}

void SelectPhase::StayState(Player* Entity)
{
	if (GetMouseZ() > 0)
	{
		GetSelect()->rot.y += D3DX_PI / 30;
	}

	if (GetMouseZ() < 0)
	{
		GetSelect()->rot.y -= D3DX_PI / 30;
	}


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


	if (IsMouseLeftTriggered())
	{
		SetTower(GetSelect()->pos, {0,GetSelect()->rot.y,0}, type);
		Entity->fsm.ChangeState(PreparationPhase::Instance());
	}
}

void SelectPhase::ExitState(Player* Entity)
{
	GetSelect()->use = false;
}
