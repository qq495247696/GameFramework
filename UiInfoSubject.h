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
