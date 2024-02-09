//=============================================================================
//
// スコア処理 [score.cpp]
// Author : 
//
//=============================================================================
#include "score.h"
#include "texture.h"
#include "sprite.h"
#include "Home.h"
#include "scene.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_WIDTH				(64)	// キャラサイズ
#define TEXTURE_HEIGHT				(128)	// 


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************			
static float					g_UW, g_UH;					// 幅と高さ
static D3DXVECTOR2				g_TimePos;						// ポリゴンの座標
static D3DXVECTOR2				g_TimeSize;
static D3DXVECTOR2				g_HpPos;
static D3DXVECTOR2				g_HpSize;
static int						g_TexNo;					// テクスチャ番号
static int						g_Score;					// スコア
double							tt;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitScore(void)
{
	//テクスチャ生成
	g_TexNo = LoadTexture((char*)"data/TEXTURE/font.png"); 
	//初期化
	g_UW     = 1.0f/16.0f;
	g_UH     = 1.0f/6.0f;
	g_TimePos = D3DXVECTOR2(15.0f, 850.0f);
	g_TimeSize = { 80,250 };
	g_HpPos = D3DXVECTOR2(600.0f, 990.0f);
	g_HpSize = { 40,100 };
	g_Score = 0;	// スコアの初期化
	tt = 60.0f;
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitScore(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateScore(void)
{
	if (g_Score > 2500)
	{
		//SetScene(SCENE_RESULT);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawScore(void)
{
	tt -= (double)((1000.0f / 60.0f)/1000.0f);
	//有効化フラグがONなら描画する
	if (true)
	{
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_TexNo));

		// 桁数分処理する
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
		//	// 今回表示する桁の数字
		//	float x = (float)(number % 10);

		//	// スコアの位置やテクスチャー座標を反映
		//	float px = g_Pos.x - g_w * i;	// 表示位置X
		//	float py = g_Pos.y;				// 表示位置Y
		//	float pw = g_w;					// 表示幅
		//	float ph = g_h;					// 表示高さ

		//	float tw = 1.0f / 10;		// テクスチャの幅
		//	float th = 1.0f / 1;		// テクスチャの高さ
		//	float tx = x * tw;			// テクスチャの左上X座標
		//	float ty = 0.0f;			// テクスチャの左上Y座標


		//	float px2 = 500 - g_w * i;	// 表示位置X
		//	float py2 = g_Pos.y;				// 表示位置Y

		//	// １枚のポリゴンの頂点とテクスチャ座標を設定
		//	DrawSprite(g_TexNo, px, py, pw, ph, tx, ty, tw, th);
		//	// 次の桁へ
		//	number /= 10;
		//}


		//DrawSprite(g_TexNo2, 300, 60, TEXTURE_WIDTH,TEXTURE_HEIGHT, 0.0,0.4, 0.2f, 0.2f);
		//for (int i = 0; i < 1; i++)
		//{
		//	int hp = GetHome()->hp;
		//	// 今回表示する桁の数字
		//	float x = (float)(hp % 10);

		//	// スコアの位置やテクスチャー座標を反映

		//	float px2 = 400 - g_w * i;
		//	float py2 = g_Pos.y;		
		//	float pw = g_w;				
		//	float ph = g_h;				

		//	float tw = 1.0f / 10;		
		//	float th = 1.0f / 1;		
		//	float tx = x * tw;			
		//	float ty = 0.0f;			


		//	// １枚のポリゴンの頂点とテクスチャ座標を設定
		//	DrawSprite(g_TexNo, px2, py2, pw, ph, tx, ty, tw, th);
		//	// 次の桁へ
		//	hp /= 10;
		//}

	}
}

//=============================================================================
// スコアを加算する
// 引数:add :追加する点数。マイナスも可能
//=============================================================================
void AddScore(int add)
{
	g_Score += add;

	if (g_Score > SCORE_MAX)
	{
		g_Score = SCORE_MAX;
	}
}

