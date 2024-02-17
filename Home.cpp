#include "Home.h"
#include "camera.h"
#include "model.h"
#include "shadow.h"
#include "sound.h"
#include "World.h"


void Home::Update(double deltaTime)
{
	UiEvent e;
	e._hp = _hp;
	_obsever.Notify(e);
	if (_hp <= 0)
	{
		
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
