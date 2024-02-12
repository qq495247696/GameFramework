/*********************************************************************
 * \file   Timer.h
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 10
 *********************************************************************/
#pragma once
#include <chrono>
using namespace std::chrono;
class Timer
{
	Timer(int seconds):duration(seconds),_running(false) {}
	~Timer() {}



private:
	bool _running;
	seconds duration;
};
