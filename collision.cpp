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
#include "score.h"
#include "player.h"
#include "Home.h"
#include "sound.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �\���̒�`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
bool CollisionBB(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR3 size1, D3DXVECTOR3 size2);
bool CollisionBS(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************


//=============================================================================
// �����蔻�菈��
//=============================================================================
void UpdateCollision(void)
{
//	Bullet*bullet = GetBullet();	// �e�̃|�C���^�[��������
//	Enemy  *enemy = GetEnemy();		// �G�l�~�[�̃|�C���^�[��������
//	Home* home = GetHome();
//	Player* player = GetPlayer();
//
//
//	// �e�ƓG�̓����蔻��(BB,BC)
//	for (int i = 0; i < BULLET_NUM; i++)
//	{
//		//�g�p����Ă��Ȃ��e�͉������Ȃ�
//		if (bullet[i].use == false)
//			continue;
//
//		for (int n = 0; n < ENEMY_NUM; n++)
//		{
//			//�g�p����Ă��Ȃ��G�͉������Ȃ�
//			if (enemy[n].use == false)
//				continue;
//
//			if (CollisionBB(bullet[i].pos, enemy[n].pos, bullet[i].size, enemy[n].size))
////			if (CollisionBS(bullet[i].pos, enemy[n].pos, bullet[i].size.x, enemy[n].size.x))
//			{
//				// �G�L�����N�^�[������
//				enemy[n].use = false;
//				ReleaseShadow(enemy[n].shadow);
//
//				// �e������
//				bullet[i].use = false;
//				ReleaseShadow(bullet[i].shadow);
//
//				// �_�������Z����
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
