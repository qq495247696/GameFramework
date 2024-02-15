#pragma once
#include "object.h"
#include "Time.h"
#include "AssetManager.h"
template<class T>
class EnemySpwaner:public Object
{
public:
	EnemySpwaner(Vec3 pos,Render* render ,double time, World* world) :Object(render,"EnemySpawner", world), _existenceTime(time), _intervalTime(0)
	{
		_position = pos;
	}

	~EnemySpwaner()
	{
	}

	// Object ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
	void Update(double deltaTime) override;
	void Draw() override;
	bool Discard() const override;
private:
	int				_spawnedNum;
	double			_existenceTime;
	double			_intervalTime;
	Vec3			_wayLine[4] = { {2450,0,10050},{2450,0,8450},{0,0,8450},{0,0,500} };
	Vec3			_wayLine2[4] = { {-2450,0,10050},{-2450,0,8450},{0,0,8450},{0,0,500} };
};


template<class T>
void EnemySpwaner<T>::Update(double deltaTime)
{
	_existenceTime -= deltaTime;
	if (Time::Get()->NowTime() >= _intervalTime)
	{
		T* enemy = new T(&AssetManager::Get()->_enemy, _position, _renderComponent, &_wayLine[0], GetWorld());
		GetWorld()->AddObject(enemy);
		_intervalTime = (Time::Get()->NowTime() + 3.0f);
	}
}
template<class T>
void EnemySpwaner<T>::Draw()
{

}

template<class T>
bool EnemySpwaner<T>::Discard() const
{
	return _existenceTime <= 0;
}