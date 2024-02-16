/*********************************************************************
 * \file   Home.h
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#pragma once
#include "object.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
class Home:public Object
{
public:
	Home(DX11_MODEL* model, Render* render, World* world ):Object(model,render,"Home",world)
	{
			// �ʒu�E��]�E�X�P�[���̏����ݒ�
			_position = D3DXVECTOR3(0.0f, 0.0f, -1200.0f);
			_rotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			_scale = D3DXVECTOR3(20.0f, 20.0f, 20.0f);
			hitedSound = LoadSound((char*)"data/SE/defend001.wav");
			hp = 5;

			//�����蔻��p�T�C�Y�̏����ݒ�
			size = D3DXVECTOR3(120.0f, 210.0f, 120.0f);
		;
	}
	~Home()
	{

	}
	// ͨ�� Object �̳�
	void Update(double deltaTime) override;
	void Draw() override;
	bool Discard() const override;
private:
	int				hp;
	unsigned int    hitedSound;
	D3DXVECTOR3     size;		
};

