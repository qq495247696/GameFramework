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
#include "World.h"
#include "Wall.h"
#include "DirectXCollision.h"


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
bool CollisionBB(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR3 size1, D3DXVECTOR3 size2);
bool CollisionBS(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2);
float ClacCollisionDepth(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR3 size1, D3DXVECTOR3 size2);
D3DXVECTOR3& ClacCollisionNormal(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR3 size1, D3DXVECTOR3 size2);
void PlayerCollisionHandling(Player* player, const D3DXVECTOR3& pos2, const D3DXVECTOR3& size1, const D3DXVECTOR3& size2);



//=============================================================================
// 当たり判定処理
//=============================================================================
void UpdateCollision(World* world)
{
	auto wall = world->GetObjectWithTag<Wall>("Wall");
	auto player= world->GetObjectWithTag<Player>("Player");

	if(CollisionBB(player->GetPosition(), wall->GetBox1()._pos, player->_hitBox._size, wall->GetBox1()._size))
	{
		
		PlayerCollisionHandling(player, wall->GetBox1()._pos, player->_hitBox._size, wall->GetBox1()._size);
	}

	if (CollisionBB(player->GetPosition(), wall->GetBox2()._pos, player->_hitBox._size, wall->GetBox2()._size))
	{

		PlayerCollisionHandling(player, wall->GetBox2()._pos, player->_hitBox._size, wall->GetBox2()._size);
	}

	if (CollisionBB(player->GetPosition(), wall->GetBox3()._pos, player->_hitBox._size, wall->GetBox3()._size))
	{

		PlayerCollisionHandling(player, wall->GetBox3()._pos, player->_hitBox._size, wall->GetBox3()._size);
	}

	if (CollisionBB(player->GetPosition(), wall->GetBox4()._pos, player->_hitBox._size, wall->GetBox4()._size))
	{

		PlayerCollisionHandling(player, wall->GetBox4()._pos, player->_hitBox._size, wall->GetBox4()._size);
	}

}




void PlayerCollisionHandling(Player* player, const D3DXVECTOR3& pos2, const D3DXVECTOR3& size1, const D3DXVECTOR3& size2)
{
	float penetrationDepth = ClacCollisionDepth(player->GetPosition(), pos2,size1, size2);
	D3DXVECTOR3 normal = ClacCollisionNormal(player->GetPosition(), pos2,size1, size2);
	player->SetPosition(player->GetPosition() + (normal * penetrationDepth));
}


float ClacCollisionDepth(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR3 size1, D3DXVECTOR3 size2)
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

	float overlapX = min(Axmax - Bxmin, Bxmax - Axmin);
	float overlapY = min(Aymax - Bymin, Bymax - Aymin);
	float overlapZ = min(Azmax - Bzmin, Bzmax - Azmin);
	float penetrationDepth = min(overlapX, min(overlapY, overlapZ));
	return penetrationDepth;
}

D3DXVECTOR3& ClacCollisionNormal(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR3 size1, D3DXVECTOR3 size2)
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

	float overlapX = min(Axmax - Bxmin, Bxmax - Axmin);
	float overlapY = min(Aymax - Bymin, Bymax - Aymin);
	float overlapZ = min(Azmax - Bzmin, Bzmax - Azmin);
	float penetrationDepth = min(overlapX, min(overlapY, overlapZ));
	D3DXVECTOR3 normal;
	if (penetrationDepth == overlapX) {
		normal = (Axmax < Bxmax) ? Vec3(-1, 0, 0) : Vec3(1, 0, 0);
	}
	else if (penetrationDepth == overlapY) {
		normal = (Aymax < Bymax) ? Vec3(0, -1, 0) : Vec3(0, 1, 0);
	}
	else {
		normal = (Azmax < Bzmax) ? Vec3(0, 0, -1) : Vec3(0, 0, 1);
	}

	return normal;
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
