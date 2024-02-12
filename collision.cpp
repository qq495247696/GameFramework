//=============================================================================
//
// 当たり判定処理 [collision.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "collision.h"
#include "bullet.h"
#include "enemy.h"
#include "shadow.h"
#include "score.h"
#include "player.h"
#include "Home.h"
#include "sound.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// 構造体定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
bool CollisionBB(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR3 size1, D3DXVECTOR3 size2);
bool CollisionBS(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2);


//*****************************************************************************
// グローバル変数
//*****************************************************************************


//=============================================================================
// 当たり判定処理
//=============================================================================
void UpdateCollision(void)
{
//	Bullet*bullet = GetBullet();	// 弾のポインターを初期化
//	Enemy  *enemy = GetEnemy();		// エネミーのポインターを初期化
//	Home* home = GetHome();
//	Player* player = GetPlayer();
//
//
//	// 弾と敵の当たり判定(BB,BC)
//	for (int i = 0; i < BULLET_NUM; i++)
//	{
//		//使用されていない弾は何もしない
//		if (bullet[i].use == false)
//			continue;
//
//		for (int n = 0; n < ENEMY_NUM; n++)
//		{
//			//使用されていない敵は何もしない
//			if (enemy[n].use == false)
//				continue;
//
//			if (CollisionBB(bullet[i].pos, enemy[n].pos, bullet[i].size, enemy[n].size))
////			if (CollisionBS(bullet[i].pos, enemy[n].pos, bullet[i].size.x, enemy[n].size.x))
//			{
//				// 敵キャラクターを消す
//				enemy[n].use = false;
//				ReleaseShadow(enemy[n].shadow);
//
//				// 弾を消す
//				bullet[i].use = false;
//				ReleaseShadow(bullet[i].shadow);
//
//				// 点数を加算する
//				AddScore(39);
//			}
//		}
//	}
//
//
//	for (int i = 0; i < ENEMY_NUM; i++)
//	{
//		if (enemy[i].use == false)
//			continue;
//
//		if (CollisionBB(enemy[i].pos, home->pos, enemy[i].size, home->size))
//		{
//			home->hp--;
//			enemy[i].use = false;
//			PlaySound(home->hitedSound,0);
//		}
//	}
//
//
//	if(CollisionBB(player->pos, home->pos, player->size, home->size))
//	{
//		
//		if (player->pos.x<(home->pos.x + home->size.x) && player->pos.x >(home->pos.x - home->size.x))
//		{
//			if (player->pos.z < 0)
//			{
//				player->pos.z = (home->pos.z - home->size.z) - player->size.z * 0.5f;
//			}
//
//			if (player->pos.z > 0)
//			{
//				player->pos.z = (home->pos.z + home->size.z) + player->size.z * 0.5f;
//			}
//		}else if 
//		(player->pos.z<(home->pos.z + home->size.z) && player->pos.z >(home->pos.z - home->size.z))
//		{
//			if (player->pos.x < 0)
//			{
//				player->pos.x = (home->pos.x - home->size.x) - player->size.x * 0.5f;
//			}
//
//			if (player->pos.x > 0)
//			{
//				player->pos.x = (home->pos.x + home->size.x) + player->size.x * 0.5f;
//			}
//		}
//	}
}

//=============================================================================
// 境界箱(BB)による当たり判定処理
// 回転は考慮しない
// 戻り値：当たってたらtrue
//=============================================================================
bool CollisionBB(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR3 size1, D3DXVECTOR3 size2)
{
	float Axmax = pos1.x + (size1.x / 2);
	float Axmin = pos1.x - (size1.x / 2);
	float Aymax = pos1.y + (size1.y / 2);
	float Aymin = pos1.y - (size1.y / 2);
	float Azmax = pos1.z + (size1.z / 2);
	float Azmin = pos1.z - (size1.z / 2);

	float Bxmax = pos2.x + (size2.x / 2);
	float Bxmin = pos2.x - (size2.x / 2);
	float Bymax = pos2.y + (size2.y / 2);
	float Bymin = pos2.y - (size2.y / 2);
	float Bzmax = pos2.z + (size2.z / 2);
	float Bzmin = pos2.z - (size2.z / 2);

	if ((Axmax > Bxmin) && (Axmin < Bxmax))
	{
		if ((Aymin < Bymax) && (Aymax > Bymin))
		{
			if ((Azmax > Bzmin) && (Azmin < Bzmax))
			{
				return true;
			}
		}
	}

	return false;
}

//=============================================================================
// 境界球(BS)による当たり判定処理
// サイズは半径
// 戻り値：当たってたらtrue
//=============================================================================
bool CollisionBS(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2)
{
	//pos1とpos2をつなぐベクトルを作る
	D3DXVECTOR3 dist = pos2 - pos1;

	//作ったベクトルの大きさを計算する
//	float length = D3DXVec3Length(&dist);

	//Sqがついている関数は平方根の計算をしないバージョン
	float length = D3DXVec3LengthSq(&dist);

	//1と2の半径を足す
//	float size = size1 + size2;

	//平方根の計算をしないので判定する相手の方を二乗する
	float size = (size1 + size2) * (size1 + size2);

	//半径の方が大きいとき、二つの円は重なっている
	if (length < size)
		return true;

	return false;
}
