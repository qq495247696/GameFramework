#include "EnemySpwaner.h"
#include "Time.h"
#include "World.h"
template<class T>
void EnemySpwaner<T>::Update(double deltaTime)
{
    _existenceTime -= deltaTime;
    if (Time::Get()->NowTime()>=_intervalTime)
    {
        T* enemy = new T();
        GetWorld()->AddObject(enemy);
        _intervalTime = Time::Get()->NowTime()+20.0f;
    }
}
template<class T>
void EnemySpwaner<T>::Draw()
{

}

template<class T>
bool EnemySpwaner<T>::Discard() const
{
    return _existenceTime<=0;
}
