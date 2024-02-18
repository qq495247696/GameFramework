/*********************************************************************
 * \file   UiInfoSubject.cpp
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 18
 *********************************************************************/
#include "UiInfoSubject.h"
#include "UiInfoObsever.h"
#include "Ui.h"
void UiInfoSubject::Update(UiEvent& uiEvent)
{
	_ui->_hp = uiEvent._hp;
	_ui->_time = uiEvent._time;
	_ui->_wave = uiEvent._wave;
	_ui->_moneny = uiEvent._moneny;
}
