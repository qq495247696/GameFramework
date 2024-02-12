#include "EnemyBullet.h"
#include "model.h"


void EnemyBullet::Update(double deltaTime)
{
	if (_use)
	{
		//���ŏ���
		if (frame > 500.0f)
		{
			_use = false;
			frame = 0;
		}

		//���W�̍X�V
		_position += (_vel * _speed)*deltaTime;
		//���Ԍo��
		frame += 1.0f;
	}
}

void EnemyBullet::Draw()
{	
	if (_use)
	{
		_renderComponent->Draw(this);
	}
}

bool EnemyBullet::Discard() const
{
	return false;
}