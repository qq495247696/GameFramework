#include "EnemyBullet.h"
#include "model.h"


static DX11_MODEL		g_Model;	// モデル読み込み
static EnemyBullet		g_Ebullet[100];	// プレイヤー情報	
void InitEnemyBullet(void)
{
	LoadModel((char*)"data/MODEL/EnemyBullet.obj", &g_Model);
	for (int i = 0; i < 100; i++)
	{
		// 位置・回転・スケールの初期設定
		g_Ebullet[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Ebullet[i].dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Ebullet[i].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_Ebullet[i].use = false;
		g_Ebullet[i].speed = 3;
		g_Ebullet[i].frame = 0;
		//当たりi][判定用サイズの初期設定
		g_Ebullet[i].size = D3DXVECTOR3(10.0f, 10.0f, 10.0f);
	}
}

void UninitEnemyBullet(void)
{
	UnloadModel(&g_Model);
}

void UpdateEnemyBullet(void)
{
	for (int i = 0; i < 100; i++)
	{
		if (g_Ebullet[i].use)
		{
			//消滅処理
			if (g_Ebullet[i].frame > 500.0f)
			{
				g_Ebullet[i].use = false;
				g_Ebullet[i].frame = 0;
			}

			//座標の更新
			g_Ebullet[i].pos += g_Ebullet[i].dir * g_Ebullet[i].speed;
			//時間経過
			g_Ebullet[i].frame += 1.0f;
		}
	}

}

void DrawEnemyBullet(void)
{
	for(int i=0;i<100;i++)
	{
		if(g_Ebullet[i].use)
		{
			D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
			SetLightEnable(true);
			// ワールドマトリックスの初期化（単位行列を作る関数）
			D3DXMatrixIdentity(&g_Ebullet[i].mtxWorld);

			// スケールを反映
			D3DXMatrixScaling(&mtxScl, g_Ebullet[i].scl.x, g_Ebullet[i].scl.y, g_Ebullet[i].scl.z);
			D3DXMatrixMultiply(&g_Ebullet[i].mtxWorld, &g_Ebullet[i].mtxWorld, &mtxScl);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Ebullet[i].rot.y, g_Ebullet[i].rot.x, g_Ebullet[i].rot.z);
			D3DXMatrixMultiply(&g_Ebullet[i].mtxWorld, &g_Ebullet[i].mtxWorld, &mtxRot);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, g_Ebullet[i].pos.x, g_Ebullet[i].pos.y, g_Ebullet[i].pos.z);
			D3DXMatrixMultiply(&g_Ebullet[i].mtxWorld, &g_Ebullet[i].mtxWorld, &mtxTranslate);

			// ワールドマトリックスの設定
			SetWorldMatrix(&g_Ebullet[i].mtxWorld);

			//カリングなし(ミクさんモデルの髪の対応)
			SetCullingMode(CULL_MODE_NONE);

			//objモデルの描画
			DrawModel(&g_Model);

			//カリングを元に戻す
			SetCullingMode(CULL_MODE_BACK);
		}
	}

}

EnemyBullet* GetEnemyBullet(void)
{
	return g_Ebullet;
}

void SetEnemyBullet(D3DXVECTOR3 _pos, D3DXVECTOR3 _dir)
{
	for (int i = 0; i < 100; i++)
	{
		if (g_Ebullet[i].use == false)
		{
			g_Ebullet[i].pos = _pos;
			g_Ebullet[i].dir = _dir;
			g_Ebullet[i].use = true;
			break;
		}
	}
}
