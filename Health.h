//=============================================================================
//
// スコア処理 [score.h]
// Author : 
//
//=============================================================================
#pragma once
#include "Ui.h"

#define SCORE_MAX			(99999)		// スコアの最大値
#define SCORE_DIGIT			(5)			// 桁数

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
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);

void AddScore(int add);


