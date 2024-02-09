/*==============================================================================

   ゲーム処理 [game.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/

#include "game.h"
#include "input.h"
#include "fade.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "meshfield.h"
#include "meshsky.h"
#include "meshmountain.h"
#include "EnemyBullet.h"
#include "collision.h"
#include "sound.h"
#include "score.h"
#include "camera.h"
#include "shadow.h"
#include "polyline.h"
#include "Home.h"
#include "Wall.h"
#include "sprite.h"
#include "Texture.h"
#include "select.h"
#include "tower.h"
#include "Ui.h"



/*------------------------------------------------------------------------------
   定数定義
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   構造体宣言
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   プロトタイプ宣言
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
   グローバル変数の定義
------------------------------------------------------------------------------*/
static int g_BGMNo = 0;


/*------------------------------------------------------------------------------
   初期化関数
------------------------------------------------------------------------------*/
static Ui *g_ui;
void InitGame(void)
{
	// カメラの初期化
	InitCamera();

	// 影の初期化
	InitShadow();

	// ポリラインの初期化
	InitPolyLine();
	g_ui = new Ui();
	// 地面の初期化
	InitMeshField(D3DXVECTOR3(0.0f, 0.0f, 3000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100, 100, 180.0f, 180.0f);

	// 空の初期化
	InitMeshSky(D3DXVECTOR3(0.0f, 0.0f, 3000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10000.0f, 16, 8);

	// 山の初期化
	InitMeshMountain(D3DXVECTOR3(0.0f, 0.0f, 3000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 16, 1, 8000.0f, 300.0f);

	// プレイヤーの初期化
	InitPlayer();
	InitEnemyBullet();

	InitWall();
	InitHome();
	// エネミーの初期化
	InitEnemy();
	InitTower();
	InitSelect();

	// 弾の初期化
	InitBullet();

	// スコアの初期化
	InitScore();

	SetLightEnable(true);

	SetAlphaTestEnable(true);

	g_BGMNo = LoadSound((char*)"data/BGM/sample001.wav");

	SetVolume(g_BGMNo, 1.0f);
	PlaySound(g_BGMNo, -1);
}


void UninitGame()
{
	//初期化とは逆順に終了処理を行う
	UninitScore();
	UninitPolyLine();
	UninitShadow();
	UninitBullet();
	UninitTower();
	UninitSelect();
	UninitEnemy();
	UninitEnemyBullet();
	UninitPlayer();
	delete g_ui;
	UninitHome();
	UninitMeshMountain();
	UninitMeshSky();
	UninitMeshField();
}

void UpdateGame(void)
{
	// カメラ更新
	UpdateCamera();

	// 地面の更新処理
	UpdateMeshField();
	UpdateMeshSky();
	UpdateMeshMountain();
	g_ui->Update();
	// プレイヤーの更新処理
	UpdatePlayer();
	UpdateEnemyBullet();
	UpdateHome();

	// エネミーの更新処理
	UpdateEnemy();
	UpdateTower();
	UpdateSelect();

	// 弾の更新処理
	UpdateBullet();

	// 影の更新処理
	UpdateShadow();

	// ポリラインの更新処理
	UpdatePolyLine();

	// スコアの更新処理
	UpdateScore();

	// 当たり判定の更新処理
	UpdateCollision();


	//スペースキーが押されていて、フェード処理中ではないとき
	if (GetKeyboardTrigger(DIK_RETURN) && GetFadeState() == FADE_NONE) 
	{
		SetVolume(g_BGMNo, 0.1f);

		//RESULTへ移行する
		SceneTransition(SCENE_RESULT);
	}
}


void DrawGame(void)
{
	// プレイヤー視点
	D3DXVECTOR3 pos = GetPlayer()->pos;
	auto cam = GetCamera();
	UpdateCameraPos(cam->pos);
	pos.y = 0.0f;			// カメラ酔いを防ぐためにクリアしている
	SetCamera();
	SetLightEnable(true);
	// 深度テスト有効
	SetDepthEnable(true);
	// ライティング有効
	
	// 地面の描画処理
	DrawMeshSky();
	DrawMeshField();
	DrawMeshMountain();

	// 影の描画処理
	DrawShadow();

	// エネミーの描画処理
	DrawEnemy();

	DrawTower();
	DrawSelect();
	DrawEnemyBullet();
	DrawWall();
	DrawPlayer();
	DrawHome();

	// 弾の描画処理
	DrawBullet();

	// ポリラインの描画処理
	DrawPolyLine();

	// マトリクス設定
	SetWorldViewProjection2D();//座標の2D変換

	// 2D描画なので深度無効
	SetDepthEnable(false);

	g_ui->Draw();
	// スコアの描画処理
	DrawScore();
}