//=============================================================================
//
// 億儕僑儞昞帵張棟 [player.cpp]
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
#include "BattlePhase.h"
#include "PreparationPhase.h"

//*****************************************************************************
// 儅僋儘掕媊
//*****************************************************************************

//*****************************************************************************
// 僾儘僩僞僀僾愰尵
//*****************************************************************************


//*****************************************************************************
// 僌儘乕僶儖曄悢
//*****************************************************************************
static DX11_MODEL	g_Model;	// 儌僨儖撉傒崬傒
static Player		g_Player;	// 僾儗僀儎乕忣曬		
static float        g_Rot;		// 僉儍儔僋僞乕偺岦偒
static LIGHT		g_DirectionalLight;	// 僨傿儗僋僔儑僫儖儔僀僩
static LIGHT		g_PointLight;		// 億僀儞僩儔僀僩
static int			g_AxisLine[3]; //億儕儔僀儞梡幆暿巕


static DX11_MODEL	g_Model_Body;
static DX11_MODEL	g_Model_RArm;
static DX11_MODEL	g_Model_LArm;
static DX11_MODEL	g_Model_RLeg;
static DX11_MODEL	g_Model_LLeg;

struct BODYPARTS
{
	D3DXVECTOR3		pos;		// 位置
	D3DXVECTOR3		rot;		// 向き(回転)
	D3DXVECTOR3		offset;		// オフセット位置
	D3DXMATRIX		mtxWorld;	// ワールドマトリックス

	ID3D11Buffer* g_VB;	// 頂点情報
	ID3D11Buffer* g_IB;	// インデックス情報
};

static BODYPARTS	g_Body;
static BODYPARTS	g_RArm;
static BODYPARTS	g_LArm;
static BODYPARTS	g_RLeg;
static BODYPARTS	g_LLeg;

struct KEYFRAME				//关键帧
{
	float		key;
	D3DXVECTOR3 rot;		//旋转
};

struct MOTIONSET			//动画数据数组
{
	KEYFRAME g_RArmMotion[5];
	KEYFRAME g_LArmMotion[5];
	KEYFRAME g_RLegMotion[5];
	KEYFRAME g_LLegMotion[5];
};

static MOTIONSET g_RunMotion =
	{
		{//RArmMotion
			{	  0.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f)},
			{	 10.0f, D3DXVECTOR3(D3DX_PI / 15, 0.0f, 0.0f)},
			{	 20.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f)},
			{	 30.0f, D3DXVECTOR3(-D3DX_PI / 15, 0.0f, 0.0f)},
			{	40.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f)},
		},
		{//LArmMotion
			{  0.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f)},
			{ 10.0f, D3DXVECTOR3(-D3DX_PI / 15, 0.0f, 0.0f)},
			{ 20.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f)},
			{ 30.0f, D3DXVECTOR3(D3DX_PI / 15, 0.0f, 0.0f)},
			{40.0f,  D3DXVECTOR3(0.0f, 0.0f, 0.0f)},
		},
		{//RLegMotion
			{  0.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f)},
			{ 10.0f, D3DXVECTOR3(-D3DX_PI / 15, 0.0f, 0.0f)},
			{ 20.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f)},
			{ 30.0f, D3DXVECTOR3(D3DX_PI / 15, 0.0f, 0.0f)},
			{40.0f,  D3DXVECTOR3(0.0f, 0.0f, 0.0f)},
		},
		{//LLegMotion
			{  0.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f)},
			{ 10.0f, D3DXVECTOR3(D3DX_PI / 15, 0.0f, 0.0f)},
			{ 20.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f)},
			{ 30.0f, D3DXVECTOR3(-D3DX_PI / 15, 0.0f, 0.0f)},
			{40.0f,  D3DXVECTOR3(0.0f, 0.0f, 0.0f)},
		},
	};

static MOTIONSET g_WaitMotion =
{
		{//RArmMotion
			{	  0.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f)},
			{	 30.0f, D3DXVECTOR3(D3DX_PI / 15, 0.0f, 0.0f)},
			{	 60.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f)},
			{	 90.0f, D3DXVECTOR3(-D3DX_PI / 15, 0.0f, 0.0f)},
			{	120.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f)},
		},
		{//LArmMotion
			{  0.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f)},
			{ 30.0f, D3DXVECTOR3(-D3DX_PI / 15, 0.0f, 0.0f)},
			{ 60.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f)},
			{ 90.0f, D3DXVECTOR3(D3DX_PI / 15, 0.0f, 0.0f)},
			{120.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f)},
		},
		{//RLegMotion
			{  0.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f)},
			{ 30.0f, D3DXVECTOR3(-D3DX_PI / 15, 0.0f, 0.0f)},
			{ 60.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f)},
			{ 90.0f, D3DXVECTOR3(D3DX_PI / 15, 0.0f, 0.0f)},
			{120.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f)},
		},
		{//LLegMotion
			{  0.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f)},
			{ 30.0f, D3DXVECTOR3(D3DX_PI / 15, 0.0f, 0.0f)},
			{ 60.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f)},
			{ 90.0f, D3DXVECTOR3(-D3DX_PI / 15, 0.0f, 0.0f)},
			{120.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f)},
		},
};

//=============================================================================
// 弶婜壔張棟
//=============================================================================
HRESULT InitPlayer(void)
{
	// 位置・回転・スケールの初期設定
	g_Body.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Body.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 位置・回転・スケールの初期設定
	g_RArm.pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	g_RArm.rot = D3DXVECTOR3(0.0f, 0.0f, 0);
	g_RArm.offset = D3DXVECTOR3(0.0f, -5.0f, 0.0f);

	// 位置・回転・スケールの初期設定
	g_LArm.pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	g_LArm.rot = D3DXVECTOR3(0.0f, 0.0f, 0);
	g_LArm.offset = D3DXVECTOR3(0.0f, -5.0f, 0.0f);

	// 位置・回転・スケールの初期設定
	g_RLeg.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_RLeg.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_RLeg.offset = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

	// 位置・回転・スケールの初期設定
	g_LLeg.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_LLeg.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_LLeg.offset = D3DXVECTOR3(0.0f, -1.0f, 0.0f);


	//objモデルの読み込み
	LoadModel((char*)"data/MODEL/playerBody.obj", &g_Model);
	LoadModel((char*)"data/MODEL/playerhandR.obj", &g_Model_RArm);
	LoadModel((char*)"data/MODEL/playerhandL.obj", &g_Model_LArm);
	LoadModel((char*)"data/MODEL/playerlegR.obj", &g_Model_RLeg);
	LoadModel((char*)"data/MODEL/playerlegL.obj", &g_Model_LLeg);


	
	



	// 埵抲丒夞揮丒僗働乕儖偺弶婜愝掕
	g_Player.pos = D3DXVECTOR3(0.0f, 0.0f, -200.0f);
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.scl = D3DXVECTOR3(2.0f, 2.0f, 2.0f);
	g_Player.use = true;

	////摉偨傝敾掕梡僒僀僘偺弶婜愝掕
	g_Player.size = D3DXVECTOR3(100.0f, 100.0f, 100.0f);
	g_Player.frame = 0;

	////obj儌僨儖偺撉傒崬傒
	//LoadModel((char*)"data/MODEL/player.obj", &g_Model);
	g_Player.se = LoadSound((char*)"data/SE/shot001.wav");
	g_Player.fsm.SetCurrentState(BattlePhase::Instance());
	g_Player.fsm.ChangeState(BattlePhase::Instance());
	// 暲峴岝尮偺愝掕乮悽奅傪徠傜偡岝乯
	g_DirectionalLight.Type = LIGHT_TYPE_DIRECTIONAL;				// 暲峴岝尮
	g_DirectionalLight.Enable = true;								// 偙偺儔僀僩傪ON
	g_DirectionalLight.Position = D3DXVECTOR4(0.0f, 50.0f, 200.0f, 1.0f);
	g_DirectionalLight.Direction = D3DXVECTOR4(1.0f, -4.0f, -2.0f, 1.0f);// 岝偺岦偒
	g_DirectionalLight.Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);	// 岝偺怓
	g_DirectionalLight.Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
	g_DirectionalLight.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);

	SetLight(0, &g_DirectionalLight);
	// 塭偺僙僢僩乮塭偼崅偝傪0偵偟偰昞帵偝偣傞乯
	g_Player.shadow = SetShadow(D3DXVECTOR3(g_Player.pos.x, 0.0f, g_Player.pos.z), 200.0f);

	return S_OK;
}

//=============================================================================
// 廔椆張棟
//=============================================================================
void UninitPlayer(void)
{
	//obj儌僨儖偺夝曻
		//objモデルの解放
	UnloadModel(&g_Model);
	UnloadModel(&g_Model_RArm);
	UnloadModel(&g_Model_LArm);
	UnloadModel(&g_Model_RLeg);
	UnloadModel(&g_Model_LLeg);
}

//=============================================================================
// 峏怴張棟
//=============================================================================
void UpdatePlayer(void)
{
	SetPositionShadow(g_Player.shadow, D3DXVECTOR3(g_Player.pos.x, 0.0f, g_Player.pos.z));
	g_Player.fsm.Update();
}

//=============================================================================
// 昤夋張棟
//=============================================================================
void DrawPlayer()
{
	//D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	//SetLightEnable(true);
	//// 儚乕儖僪儅僩儕僢僋僗偺弶婜壔乮扨埵峴楍傪嶌傞娭悢乯
	//D3DXMatrixIdentity(&g_Player.mtxWorld);

	//// 僗働乕儖傪斀塮
	//D3DXMatrixScaling(&mtxScl, g_Player.scl.x, g_Player.scl.y, g_Player.scl.z);
	//D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxScl);

	//// 夞揮傪斀塮
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	//D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

	//// 堏摦傪斀塮
	//D3DXMatrixTranslation(&mtxTranslate, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	//D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTranslate);

	//// 儚乕儖僪儅僩儕僢僋僗偺愝掕
	//SetWorldMatrix(&g_Player.mtxWorld);
	////僇儕儞僌側偟(儈僋偝傫儌僨儖偺敮偺懳墳)
	//SetCullingMode(CULL_MODE_NONE);

	////obj儌僨儖偺昤夋
	//DrawModel(&g_Model);

	////僇儕儞僌傪尦偵栠偡
	//SetCullingMode(CULL_MODE_BACK);


	//-----------------------------------------------------------------
	//アニメーションフレームより現在の姿勢を決定する
	//-----------------------------------------------------------------
	
	g_Player.DrawAnim(&g_Player.frame, g_Player.rot, g_Player.pos);
	g_Player.frame += 1.0f;

	// ライティング有効
	
}

void Player::DrawAnim(float* frame, D3DXVECTOR3& rot, D3DXVECTOR3& pos)
{
	SetLightEnable(true);
	MOTIONSET* pMotion = &g_WaitMotion;


	//経過フレームから現在補間中のインデックスを求める
	int MotionIndex = -1;
	//关键帧数计算；
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
		D3DXMatrixScaling(&mtxScl, g_Player.scl.x, g_Player.scl.y, g_Player.scl.z);
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
		SetWorldMatrix(&g_Body.mtxWorld);

		//objモデルの描画
		DrawModel(&g_Model);

		//他のパーツのための親マトリクスをつくる
		mtxParent = mtxRot * mtxTranslate * mtxWorldRoot;
	}

	//--------------------------------------------------------------------------------------------
	//右腕
	//--------------------------------------------------------------------------------------------
	{
		D3DXMatrixIdentity(&g_RArm.mtxWorld);

		// スケールを反映
		D3DXMatrixScaling(&mtxScl, g_Player.scl.x, g_Player.scl.y, g_Player.scl.z);
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
		SetWorldMatrix(&g_RArm.mtxWorld);

		//右腕モデルの描画
		DrawModel(&g_Model_RArm);
	}

	//--------------------------------------------------------------------------------------------
	//左腕
	//--------------------------------------------------------------------------------------------
	{
		D3DXMatrixIdentity(&g_LArm.mtxWorld);

		// スケールを反映
		D3DXMatrixScaling(&mtxScl, g_Player.scl.x, g_Player.scl.y, g_Player.scl.z);
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
		SetWorldMatrix(&g_LArm.mtxWorld);

		//左腕モデルの描画
		DrawModel(&g_Model_LArm);
	}

	//--------------------------------------------------------------------------------------------
	//右脚
	//--------------------------------------------------------------------------------------------
	{
		D3DXMatrixIdentity(&g_RLeg.mtxWorld);

		// スケールを反映
		D3DXMatrixScaling(&mtxScl, g_Player.scl.x, g_Player.scl.y, g_Player.scl.z);
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
		SetWorldMatrix(&g_RLeg.mtxWorld);

		//右脚モデルの描画
		DrawModel(&g_Model_RLeg);
	}

	//--------------------------------------------------------------------------------------------
	//左脚
	//--------------------------------------------------------------------------------------------
	{
		// ワールドマトリックスの初期化（単位行列を作る関数）
		D3DXMatrixIdentity(&g_LLeg.mtxWorld);

		// スケールを反映
		D3DXMatrixScaling(&mtxScl, g_Player.scl.x, g_Player.scl.y, g_Player.scl.z);
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
		SetWorldMatrix(&g_LLeg.mtxWorld);

		//右脚モデルの描画
		DrawModel(&g_Model_LLeg);
	}
}


//=============================================================================
// 僾儗僀儎乕忣曬傪庢摼
//=============================================================================
Player *GetPlayer(void)
{
	return &g_Player;
}

