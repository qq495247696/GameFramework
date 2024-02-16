//=============================================================================
//
// �����蔻�菈�� [collision.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "collision.h"
#include "bullet.h"
#include "enemy.h"
#include "shadow.h"
#include "Health.h"
#include "player.h"
#include "Home.h"
#include "sound.h"
#include "World.h"
#include "Wall.h"
#include "DirectXCollision.h"


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
bool CollisionBB(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR3 size1, D3DXVECTOR3 size2);
bool CollisionBS(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2);
float ClacCollisionDepth(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR3 size1, D3DXVECTOR3 size2);
D3DXVECTOR3& ClacCollisionNormal(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR3 size1, D3DXVECTOR3 size2);
void PlayerCollisionHandling(Player* player, const D3DXVECTOR3& pos2, const D3DXVECTOR3& size1, const D3DXVECTOR3& size2);



//=============================================================================
// �����蔻�菈��
//=============================================================================
void UpdateCollision(World* world)
{
	auto wall = world->GetObjectWithTag<Wall>("Wall");
	auto player= world->GetObjectWithTag<Player>("Player");



	for (int i = 0; i < 10; i++)
	{
		if (CollisionBB(player->GetPosition(), wall->GetBox()[i]._pos, player->_hitBox._size, wall->GetBox()[i]._size))
		{

			PlayerCollisionHandling(player, wall->GetBox()[i]._pos, player->_hitBox._size, wall->GetBox()[i]._size);
		}
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
// ���E��(BB)�ɂ�铖���蔻�菈��
// ��]�͍l�����Ȃ�
// �߂�l�F�������Ă���true
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
// ���E��(BS)�ɂ�铖���蔻�菈��
// �T�C�Y�͔��a
// �߂�l�F�������Ă���true
//=============================================================================
bool CollisionBS(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2)
{
	//pos1��pos2���Ȃ��x�N�g�������
	D3DXVECTOR3 dist = pos2 - pos1;

	//������x�N�g���̑傫�����v�Z����
//	float length = D3DXVec3Length(&dist);

	//Sq�����Ă���֐��͕������̌v�Z�����Ȃ��o�[�W����
	float length = D3DXVec3LengthSq(&dist);

	//1��2�̔��a�𑫂�
//	float size = size1 + size2;

	//�������̌v�Z�����Ȃ��̂Ŕ��肷�鑊��̕����悷��
	float size = (size1 + size2) * (size1 + size2);

	//���a�̕����傫���Ƃ��A��̉~�͏d�Ȃ��Ă���
	if (length < size)
		return true;

	return false;
}
