//=============================================================================
//
// ƒ|ƒŠƒSƒ“•\Ž¦ˆ— [Select.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "Select.h"
#include "texture.h"
#include "polyline.h"

void Select::Update(double deltaTime)
{

}

void Select::Draw()
{
	_renderComponent->Draw(this);
}

bool Select::Discard() const
{
	return false;
}
