//=============================================================================
//
// �X�R�A���� [score.h]
// Author : 
//
//=============================================================================
#pragma once
#include "Ui.h"

#define SCORE_MAX			(99999)		// �X�R�A�̍ő�l
#define SCORE_DIGIT			(5)			// ����

class Health:public Ui
{
public:
	Health(const int texNo, Render* render, World* world,Ui* partner):Ui(texNo, render,"Score", world, partner) { ; }
	~Health() {};
	void Update(double deltaTime) override;
	void Draw() override;
	bool Discard() const override;

};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);

void AddScore(int add);


