//=============================================================================
//
// �X�R�A���� [score.cpp]
// Author : 
//
//=============================================================================
#include "score.h"
#include "texture.h"
#include "sprite.h"
#include "Home.h"
#include "scene.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_WIDTH				(64)	// �L�����T�C�Y
#define TEXTURE_HEIGHT				(128)	// 


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************			
static float					g_UW, g_UH;					// ���ƍ���
static D3DXVECTOR2				g_TimePos;						// �|���S���̍��W
static D3DXVECTOR2				g_TimeSize;
static D3DXVECTOR2				g_HpPos;
static D3DXVECTOR2				g_HpSize;
static int						g_TexNo;					// �e�N�X�`���ԍ�
static int						g_Score;					// �X�R�A
double							tt;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitScore(void)
{
	//�e�N�X�`������
	g_TexNo = LoadTexture((char*)"data/TEXTURE/font.png"); 
	//������
	g_UW     = 1.0f/16.0f;
	g_UH     = 1.0f/6.0f;
	g_TimePos = D3DXVECTOR2(15.0f, 850.0f);
	g_TimeSize = { 80,250 };
	g_HpPos = D3DXVECTOR2(600.0f, 990.0f);
	g_HpSize = { 40,100 };
	g_Score = 0;	// �X�R�A�̏�����
	tt = 60.0f;
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitScore(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateScore(void)
{
	if (g_Score > 2500)
	{
		//SetScene(SCENE_RESULT);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawScore(void)
{
	tt -= (double)((1000.0f / 60.0f)/1000.0f);
	//�L�����t���O��ON�Ȃ�`�悷��
	if (true)
	{
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_TexNo));

		// ��������������
		int number = g_Score;

		int hp = GetHome()->hp;
		int first = (int)tt / 10;
		int secend = (int)tt % 10;
		DrawSpriteLeftTop(g_TexNo, g_TimePos.x, g_TimePos.y , g_TimeSize.x, g_TimeSize.y, g_UW*first , g_UH, g_UW, g_UH);
		DrawSpriteLeftTop(g_TexNo, g_TimePos.x + g_TimeSize.x , g_TimePos.y, g_TimeSize.x, g_TimeSize.y, g_UW * secend, g_UH, g_UW, g_UH);


		DrawSpriteLeftTopColor(g_TexNo, g_HpPos.x - g_HpSize.x*3, g_HpPos.y, g_HpSize.x, g_HpSize.y, g_UW*8 , g_UH*2, g_UW, g_UH, { 0.6,0.6,0.6,1.0 });
		DrawSpriteLeftTopColor(g_TexNo, g_HpPos.x - g_HpSize.x*2, g_HpPos.y, g_HpSize.x, g_HpSize.y, g_UW*0 , g_UH*3, g_UW, g_UH, { 0.6,0.6,0.6,1.0 });
		DrawSpriteLeftTopColor(g_TexNo, g_HpPos.x, g_HpPos.y, g_HpSize.x, g_HpSize.y, g_UW * hp, g_UH, g_UW, g_UH, {0.8,0.8,0.8,1.0});
		DrawSpriteLeftTopColor(g_TexNo, g_HpPos.x + g_HpSize.x, g_HpPos.y, g_HpSize.x, g_HpSize.y, g_UW * hp, g_UH, g_UW, g_UH, { 0.8,0.8,0.8,1.0 });


		//for (int i = 0; i < SCORE_DIGIT; i++)
		//{
		//	// ����\�����錅�̐���
		//	float x = (float)(number % 10);

		//	// �X�R�A�̈ʒu��e�N�X�`���[���W�𔽉f
		//	float px = g_Pos.x - g_w * i;	// �\���ʒuX
		//	float py = g_Pos.y;				// �\���ʒuY
		//	float pw = g_w;					// �\����
		//	float ph = g_h;					// �\������

		//	float tw = 1.0f / 10;		// �e�N�X�`���̕�
		//	float th = 1.0f / 1;		// �e�N�X�`���̍���
		//	float tx = x * tw;			// �e�N�X�`���̍���X���W
		//	float ty = 0.0f;			// �e�N�X�`���̍���Y���W


		//	float px2 = 500 - g_w * i;	// �\���ʒuX
		//	float py2 = g_Pos.y;				// �\���ʒuY

		//	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		//	DrawSprite(g_TexNo, px, py, pw, ph, tx, ty, tw, th);
		//	// ���̌���
		//	number /= 10;
		//}


		//DrawSprite(g_TexNo2, 300, 60, TEXTURE_WIDTH,TEXTURE_HEIGHT, 0.0,0.4, 0.2f, 0.2f);
		//for (int i = 0; i < 1; i++)
		//{
		//	int hp = GetHome()->hp;
		//	// ����\�����錅�̐���
		//	float x = (float)(hp % 10);

		//	// �X�R�A�̈ʒu��e�N�X�`���[���W�𔽉f

		//	float px2 = 400 - g_w * i;
		//	float py2 = g_Pos.y;		
		//	float pw = g_w;				
		//	float ph = g_h;				

		//	float tw = 1.0f / 10;		
		//	float th = 1.0f / 1;		
		//	float tx = x * tw;			
		//	float ty = 0.0f;			


		//	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		//	DrawSprite(g_TexNo, px2, py2, pw, ph, tx, ty, tw, th);
		//	// ���̌���
		//	hp /= 10;
		//}

	}
}

//=============================================================================
// �X�R�A�����Z����
// ����:add :�ǉ�����_���B�}�C�i�X���\
//=============================================================================
void AddScore(int add)
{
	g_Score += add;

	if (g_Score > SCORE_MAX)
	{
		g_Score = SCORE_MAX;
	}
}

