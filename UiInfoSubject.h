/*********************************************************************
 * \file   UiInfoSubject.h
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 18
 *********************************************************************/
#pragma once
class Ui;
class UiEvent;
class UiInfoSubject
{
public:
	UiInfoSubject(Ui* ui): _ui(ui){}
	~UiInfoSubject() {};
	
	void Update(UiEvent& uiEvent);
	Ui* _ui;
};
