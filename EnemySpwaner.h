/*********************************************************************
 * \file   EnemySpwaner.h
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#pragma once
#include "object.h"
#include "Time.h"
#include "AssetManager.h"
struct WayLineArray
{
	Vec3			_wayLine1[4] = { {2450,0,10050},{2450,0,8450},{0,0,8450},{0,0,500} };
	Vec3			_wayLine2[4] = { {-2450,0,10050},{-2450,0,8450},{0,0,8450},{0,0,500} };
};

static WayLineArray way;
template<class T>
class EnemySpwaner:public Object
{
public:
	EnemySpwaner(Vec3 pos,Render* render ,double time, float createTime,World* world, Vec3* wayLine) :Object(render,"EnemySpawner", world), _existenceTime(time), _intervalTime(0), _createSpeed(createTime), _wayLine(wayLine)
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
	float			_createSpeed;
	Vec3*			_wayLine;
};


template<class T>
void EnemySpwaner<T>::Update(double deltaTime)
{
	_existenceTime -= deltaTime;
	if (Time::Get()->NowTime() >= _intervalTime)
	{
		T* enemy = new T( _position, _renderComponent, _wayLine, GetWorld());
		GetWorld()->AddObject(enemy);
		_intervalTime = (Time::Get()->NowTime() + _createSpeed);
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