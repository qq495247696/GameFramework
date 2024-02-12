#include "Wall.h"
#include "Utility.h"
#include "Texture.h"
#include "main.h"
#include "model.h"
#include "DirectXAPI.h"


void Wall::Update(double deltaTime)
{
}

void Wall::Draw()
{
	_renderComponent->Draw(this);
}

bool Wall::Discard() const
{
	return false;
}
