#include "Ui.h"
#include "camera.h"
#include "Texture.h"
#include "sprite.h"

void Ui::Update()
{
	_position = GetCamera()->pos;

}

void Ui::Draw()
{
	SetLightEnable(false);
	DrawSpriteLeftTop(_texNo, 0, 0, 1920, 1080, 1, 1, 1, 1);
}
