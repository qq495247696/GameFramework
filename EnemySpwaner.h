#pragma once
#include "object.h"
template<class T>
class EnemySpwaner:public Object
{
public:
	EnemySpwaner(Vec3 pos, double time, World* world) :Object("EnemySpawner", world), _existenceTime(time), _intervalTime(0)
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
	Vec3			_wayLine[4];
	Vec3			_wayLine2[4];
};
