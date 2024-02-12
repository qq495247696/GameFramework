#include "Home.h"
#include "main.h"
#include "camera.h"
#include "model.h"
#include "shadow.h"
#include "polyline.h"
#include "sound.h"

static int			g_AxisLine[5]; //ポリライン用識別子

//HRESULT InitHome(void)
//{
//
//
//	// ポリラインのセット
//	g_AxisLine[0] = SetPolyLine(D3DXVECTOR3(-150.0f, 300.0f, -900.0f), D3DXVECTOR3(150.0f, 300.0f, -900.0f), 30.0f);
//	SetColorPolyLine(g_AxisLine[0], D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.8f));
//	return S_OK;
//}
//
//
//
//void UpdateHome(void)
//{
//	SetPositionPolyLine(0, { -150.0f, 500.0f, -900.0f }, { -150.0f + (300 / 5) * g_Home.hp, 500.0f, -900.0f });
//	if (g_Home.hp <= 0)
//	{
//		//SetScene(SCENE_RESULT);
//		StopSoundAll();
//	}
//}


void Home::Update(double deltaTime)
{
	if (hp <= 0)
	{
		//SetScene(SCENE_RESULT);
		//StopSoundAll();
	}
}

void Home::Draw()
{
	_renderComponent->Draw(this);
}

bool Home::Discard() const
{
	return false;
}
