/*********************************************************************
 * \file   ThunderTower.cpp
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#include "ThunderTower.h"
#include "Render.h"
#include "model.h"
#include "World.h"
#include "enemy.h"
#include "Tbullet.h"

void ThunderTower::Update(double deltaTime)
{
    auto enemy = GetWorld()->GetObjectsWithTag<Enemy>("Enemy");

    for (auto x : enemy)
    {

        Vec3 velVec = x->GetPosition() - _position;
        if (D3DXVec3Length(&velVec) < _attackDistance)
        {
            D3DXVec3Normalize(&velVec, &velVec);
            _finded=true;
            _model->SubsetArray[24].Material.Material.Diffuse = { 1.0,1.0,0.0,1.0 };

            _attackTime += deltaTime;
            if (_attackTime > _attackSpeed)
            {
                TBullet* nBullet = new TBullet(&AssetManager::Get()->_thunderTBullet, { _position.x,55.0f,_position.z }, velVec, 3500, _attack, _renderComponent, GetWorld());
                GetWorld()->AddObject(nBullet);
                PlaySound(AssetManager::Get()->_normalShootSe, 0);
                _attackTime = 0;
            }
        }
    }

    if (_finded == false)
    {
        _time += _timeValue * deltaTime;

        if (_time < 0)
        {
            _time = 0;
            _timeValue = -_timeValue;
        }
        if (_time > 1)
        {
            _time = 1;
            _timeValue = -_timeValue;
        }

        D3DXCOLOR ab;
        D3DXCOLOR start = { 0.4f,0.4f,0.0f,1.0f };
        D3DXCOLOR end = { 0.8f,0.8f,0.0f,1.0f };
        D3DXColorLerp(&ab, &start, &end, _time);
        _model->SubsetArray[24].Material.Material.Diffuse = ab;
    }
  
}

void ThunderTower::Draw()
{
    _renderComponent->Draw(this);
}

bool ThunderTower::Discard() const
{
    return false;
}
