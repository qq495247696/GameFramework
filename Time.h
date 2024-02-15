/*********************************************************************
 * \file   Time.h
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 10
 *********************************************************************/
#pragma once
#include <chrono>
using namespace std::chrono;
class Time
{
public:
	//����ʵ����
	static Time* Get()
	{
		static Time time;
		return &time;
	}

	//��E¼���deltaTime
	void Update() {
		auto currentTime = std::chrono::high_resolution_clock::now();
		_deltaTime = std::chrono::duration<double, std::chrono::seconds::period>(currentTime - _lastTime).count();
		_lastTime = currentTime;
	}
	//ÿ֡ʱ��E
	const double DeltaTime() const 
	{
		return _deltaTime; 
	}

	const double FixDeltaTime()const
	{
		return _fixdeltaTime * _timeScale;
	}
	//������������ڵ���ʱ��E
	const double TotalTime() const
	{
		duration<double> elapsed_seconds = high_resolution_clock::now() - _startTime;
		return elapsed_seconds.count();
	}

	const double NowTime()const
	{
		auto nowTime = high_resolution_clock::now();
		auto durationInSeconds = std::chrono::duration_cast<std::chrono::seconds>(nowTime.time_since_epoch()).count();
		return durationInSeconds;
	}

	void SetTimeScale(double scale)
	{
		if (scale >= 1.0f)
		{
			scale = 1.0f;
		}
		if (scale <= 0.0f)
		{
			scale = 0.0f;
		}
		_timeScale = scale;
	}
	//����ʱ
private:
	Time():_deltaTime(0),_timeScale(1.0f) 
	{
		_startTime = high_resolution_clock::now();
		_lastTime = _startTime;
		_fixdeltaTime = 1.0 / 60.0f;
	}
	~Time() {}

	double _timeScale;
	double _deltaTime;
	double _fixdeltaTime;
	high_resolution_clock::time_point _startTime;
	high_resolution_clock::time_point _lastTime;
	high_resolution_clock::time_point _currentTime;

	//���ÿ��ຯ��
	Time(const Time&) = delete;
	Time& operator=(const Time&) = delete;
};