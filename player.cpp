//=============================================================================
//
//億儕僑儞昞帵張棟 [player.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "player.h"
#include "texture.h"
#include "model.h"
#include "bullet.h"
#include "shadow.h"
#include "polyline.h"
#include "sound.h"
#include "PreparationPhase.h"




//g_DirectionalLight.Type = LIGHT_TYPE_DIRECTIONAL;				// 暲峴岝尮
//g_DirectionalLight.Enable = true;								// 偙偺儔僀僩傪ON
//g_DirectionalLight.Position = D3DXVECTOR4(0.0f, 50.0f, 200.0f, 1.0f);
//g_DirectionalLight.Direction = D3DXVECTOR4(1.0f, -4.0f, -2.0f, 1.0f);// 岝偺岦偒
//g_DirectionalLight.Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);	// 岝偺怓
//g_DirectionalLight.Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
//g_DirectionalLight.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
//
//SetLight(0, &g_DirectionalLight);
void Player::DrawAnim(float* frame, D3DXVECTOR3& rot, D3DXVECTOR3& pos)
{
	MOTIONSET* pMotion = &g_WaitMotion;


	////経過フレームから現在補間中のインデックスを求める
	int MotionIndex = -1;
	////关键帧数计算；
	int loop = sizeof(pMotion->g_RArmMotion) / sizeof(KEYFRAME);
	for (int i = 0; i < loop; i++)
	{
		if (pMotion->g_RArmMotion[i].key >(*frame))
		{
			MotionIndex = i;
			break;
		}
	}

	//経過フレームが最大キーフレームを超えているのでリセット（ループ）する
	if (MotionIndex == -1)
	{
		(*frame) = 0;
		MotionIndex = 0;
	}
	//経過フレームから現在のアニメーション再生の角度を計算する
	float	t;
	if (MotionIndex == 0)
	{
		//关键帧头部的数据的情况使用0号
		D3DXVec3Lerp(&g_RArm.rot, &pMotion->g_RArmMotion[MotionIndex].rot, &pMotion->g_RArmMotion[MotionIndex].rot, 0.0f);
		D3DXVec3Lerp(&g_LArm.rot, &pMotion->g_LArmMotion[MotionIndex].rot, &pMotion->g_LArmMotion[MotionIndex].rot, 0.0f);
		D3DXVec3Lerp(&g_RLeg.rot, &pMotion->g_RLegMotion[MotionIndex].rot, &pMotion->g_RLegMotion[MotionIndex].rot, 0.0f);
		D3DXVec3Lerp(&g_LLeg.rot, &pMotion->g_LLegMotion[MotionIndex].rot, &pMotion->g_LLegMotion[MotionIndex].rot, 0.0f);
	}
	else
	{

		t = ((*frame) - pMotion->g_RArmMotion[MotionIndex - 1].key /
			(pMotion->g_RArmMotion[MotionIndex].key) - pMotion->g_RArmMotion[MotionIndex - 1].key);
		if (t > 1.0f)
		{
			t = 1.0f;
		}
		D3DXVec3Lerp(&g_RArm.rot, &pMotion->g_RArmMotion[MotionIndex].rot, &pMotion->g_RArmMotion[MotionIndex].rot, t);
		D3DXVec3Lerp(&g_LArm.rot, &pMotion->g_LArmMotion[MotionIndex].rot, &pMotion->g_LArmMotion[MotionIndex].rot, t);
		D3DXVec3Lerp(&g_RLeg.rot, &pMotion->g_RLegMotion[MotionIndex].rot, &pMotion->g_RLegMotion[MotionIndex].rot, t);
		D3DXVec3Lerp(&g_LLeg.rot, &pMotion->g_LLegMotion[MotionIndex].rot, &pMotion->g_LLegMotion[MotionIndex].rot, t);
	}

	//-----------------------------------------------------------------
	//上で決まった回転角度の値を使って描画を行う
	// ここからの処理は今までと同じ（各パーツの親子関係表示）
	//-----------------------------------------------------------------


	// ライティング無効

	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATRIX mtxWorldRoot;
	D3DXMATRIX mtxParent;

	// ワールドマトリックスの初期化（単位行列を作る関数）
	D3DXMatrixIdentity(&mtxWorldRoot);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	mtxWorldRoot *= mtxRot;

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, pos.x, pos.y, pos.z);
	mtxWorldRoot *= mtxTranslate;


	//--------------------------------------------------------------------------------------------
	//胴体
	//--------------------------------------------------------------------------------------------
	{
		D3DXMatrixIdentity(&g_Body.mtxWorld);

		// スケールを反映
		D3DXMatrixScaling(&mtxScl, _scale.x, _scale.y, _scale.z);
		g_Body.mtxWorld *= mtxScl;

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Body.rot.y, g_Body.rot.x, g_Body.rot.z);
		g_Body.mtxWorld *= mtxRot;

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, g_Body.pos.x, g_Body.pos.y, g_Body.pos.z);
		g_Body.mtxWorld *= mtxTranslate;

		// 親マトリクスを反映
		g_Body.mtxWorld *= mtxWorldRoot;

		// ワールドマトリックスの設定
		_renderComponent->GetApi()->SetWorldMatrix(&g_Body.mtxWorld);

		//objモデルの描画
		DrawModel(&g_Model_Body,_renderComponent->GetApi());


		//他のパーツのための親マトリクスをつくる
		mtxParent = mtxRot * mtxTranslate * mtxWorldRoot;
	}

	//--------------------------------------------------------------------------------------------
	//右腕
	//--------------------------------------------------------------------------------------------
	{
		D3DXMatrixIdentity(&g_RArm.mtxWorld);

		// スケールを反映
		D3DXMatrixScaling(&mtxScl, _scale.x, _scale.y, _scale.z);
		g_RArm.mtxWorld *= mtxScl;

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, g_RArm.offset.x, g_RArm.offset.y, g_RArm.offset.z);
		g_RArm.mtxWorld *= mtxTranslate;

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_RArm.rot.y, g_RArm.rot.x, g_RArm.rot.z);
		g_RArm.mtxWorld *= mtxRot;

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, g_RArm.pos.x, g_RArm.pos.y, g_RArm.pos.z);
		g_RArm.mtxWorld *= mtxTranslate;

		// 親のマトリクスを反映させる
		g_RArm.mtxWorld *= mtxParent;

		// ワールドマトリックスの設定
		_renderComponent->GetApi()->SetWorldMatrix(&g_RArm.mtxWorld);

		//右腕モデルの描画
		DrawModel(&g_Model_RArm,_renderComponent->GetApi());
	}

	//--------------------------------------------------------------------------------------------
	//左腕
	//--------------------------------------------------------------------------------------------
	{
		D3DXMatrixIdentity(&g_LArm.mtxWorld);

		// スケールを反映
		D3DXMatrixScaling(&mtxScl, _scale.x, _scale.y, _scale.z);
		g_LArm.mtxWorld *= mtxScl;

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, g_LArm.offset.x, g_LArm.offset.y, g_LArm.offset.z);
		g_LArm.mtxWorld *= mtxTranslate;

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_LArm.rot.y, g_LArm.rot.x, g_LArm.rot.z);
		g_LArm.mtxWorld *= mtxRot;

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, g_LArm.pos.x, g_LArm.pos.y, g_LArm.pos.z);
		g_LArm.mtxWorld *= mtxTranslate;

		// 親のマトリクスを反映させる
		g_LArm.mtxWorld *= mtxParent;

		// ワールドマトリックスの設定
		_renderComponent->GetApi()->SetWorldMatrix(&g_LArm.mtxWorld);

		//左腕モデルの描画
		DrawModel(&g_Model_LArm, _renderComponent->GetApi());
	}

	//--------------------------------------------------------------------------------------------
	//右脚
	//--------------------------------------------------------------------------------------------
	{
		D3DXMatrixIdentity(&g_RLeg.mtxWorld);

		// スケールを反映
		D3DXMatrixScaling(&mtxScl, _scale.x, _scale.y, _scale.z);
		g_RLeg.mtxWorld *= mtxScl;

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, g_RLeg.offset.x, g_RLeg.offset.y, g_RLeg.offset.z);
		g_RLeg.mtxWorld *= mtxTranslate;

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_RLeg.rot.y, g_RLeg.rot.x, g_RLeg.rot.z);
		g_RLeg.mtxWorld *= mtxRot;

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, g_RLeg.pos.x, g_RLeg.pos.y, g_RLeg.pos.z);
		g_RLeg.mtxWorld *= mtxTranslate;

		// 親のマトリクスを反映させる
		g_RLeg.mtxWorld *= mtxParent;

		// ワールドマトリックスの設定
		_renderComponent->GetApi()->SetWorldMatrix(&g_RLeg.mtxWorld);

		//右脚モデルの描画
		DrawModel(&g_Model_RLeg, _renderComponent->GetApi());
	}

	//--------------------------------------------------------------------------------------------
	//左脚
	//--------------------------------------------------------------------------------------------
	{
		// ワールドマトリックスの初期化（単位行列を作る関数）
		D3DXMatrixIdentity(&g_LLeg.mtxWorld);

		// スケールを反映
		D3DXMatrixScaling(&mtxScl, _scale.x, _scale.y, _scale.z);
		g_LLeg.mtxWorld *= mtxScl;

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, g_LLeg.offset.x, g_LLeg.offset.y, g_LLeg.offset.z);
		g_LLeg.mtxWorld *= mtxTranslate;

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_LLeg.rot.y, g_LLeg.rot.x, g_LLeg.rot.z);
		g_LLeg.mtxWorld *= mtxRot;

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, g_LLeg.pos.x, g_LLeg.pos.y, g_LLeg.pos.z);
		g_LLeg.mtxWorld *= mtxTranslate;

		// 親のマトリクスを反映させる
		g_LLeg.mtxWorld *= mtxParent;

		// ワールドマトリックスの設定
		_renderComponent->GetApi()->SetWorldMatrix(&g_LLeg.mtxWorld);

		//右脚モデルの描画
		DrawModel(&g_Model_LLeg, _renderComponent->GetApi());
	}
}

void Player::Update(double deltaTime)
{
	//SetPositionShadow(g_Player.shadow, D3DXVECTOR3(g_Player.pos.x, 0.0f, g_Player.pos.z));
	fsm.Update();
}

void Player::Draw()
{
	//-----------------------------------------------------------------
	//アニメーションフレームより現在の姿勢を決定する
	//-----------------------------------------------------------------

	DrawAnim(&frame, _rotate, _position);
	frame += 1.0f;

	// ライティング有効
}

bool Player::Discard() const
{
	return false;
}


