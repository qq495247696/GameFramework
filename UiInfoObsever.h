#pragma once
#include <list>
#include "UiInfoSubject.h"

struct UiEvent
{
	int			_hp;
	double		_time;
	int			_wave;
	int			_moneny;
};


class UiInfoObsever
{
public:
	UiInfoObsever() { ; }
	~UiInfoObsever() { ; }
	void Notify(UiEvent& uiEvent)
	{
		for (auto x : _subject)
		{
			x->Update(uiEvent);
		}
	
	}

	void AddSubject(UiInfoSubject* subject)
	{
		_subject.push_back(subject);
	};
private:
	std::list<UiInfoSubject*>			_subject;
};
