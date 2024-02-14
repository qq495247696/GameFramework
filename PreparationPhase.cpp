#include "PreparationPhase.h"
#include "camera.h"
#include "input.h"
#include "render.h"
#include "select.h"
#include "SelectPhase.h"


static D3DXVECTOR3 atPos;
static D3DXVECTOR3 oldPos;
void PreparationPhase::EnterState(Player* Entity, DirectXAPI* api)
{
	
}

void PreparationPhase::StayState(Player* Entity, float deltaTime, DirectXAPI* api)
{
	/*Camera* cam = GetCamera();
	if (cam->pos.y < 2000)
	{
		atPos = Entity->pos;
		
		cam->pos.y += 20;
	}

	if (cam->pos.y > 2000)
	{
		cam->pos.y = 2000;
	}


	if (cam->pos.y == 2000)
	{
		auto selectUi=GetSelect();
		selectUi->pos = { atPos.x,5,atPos.z };
		selectUi->use = true;
		if (GetMouseX() < 0)
		{
			cam->pos.x -= 20;
			atPos.x -= 20;
		}
		if (GetMouseX() > 0)
		{
			cam->pos.x += 20;
			atPos.x += 20;
		}

		if (GetMouseY() > 0)
		{
			cam->pos.z -= 20;
			atPos.z -= 20;
		}

		if (GetMouseY() < 0)
		{
			cam->pos.z += 20;
			atPos.z += 20;
		}

		if (IsMouseLeftTriggered())
		{
			Entity->fsm.ChangeState(SelectPhase::Instance());
		}
	}

	if (cam->pos.z > 2400)
	{
		cam->pos.z = 2400;
		atPos.z = 2800;
	}
	if (cam->pos.z < -2400)
	{
		cam->pos.z = -2400;
		atPos.z = -2000;
	}
	if (cam->pos.x > 2400)
	{
		cam->pos.x = 2400;
		atPos.x = 2400;
	}
	if (cam->pos.x < -2400)
	{
		cam->pos.x = -2400;
		atPos.x = -2400;
	}
	SetCameraAT(atPos, false);*/
}

void PreparationPhase::ExitState(Player* Entity, DirectXAPI* api)
{
}
