/*********************************************************************
 * \file   player.h
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#pragma once
#include "StateMachine.h"
#include "State.h"
#include "BattlePhase.h"
#include "object.h"
#include "Render.h"
#include "model.h"
#include "collision.h"
//*****************************************************************************
// 儅僋儘掕媊
//*****************************************************************************

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



class Player :public Object
{
public:
	Player() = default;
	Player(DX11_MODEL* model, Render* render,DirectXAPI* api, World* world) :Object(model, render, "Player", world),_api(api)
	{
		fsm = new StateMachine<Player>(this, _api);
		_hitBox._pos=this->_position;
		_hitBox._size = { 80,100,40 };
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
		LoadModel((char*)"data/MODEL/playerBody.obj", &g_Model_Body, _api);
		LoadModel((char*)"data/MODEL/playerhandR.obj", &g_Model_RArm, _api);
		LoadModel((char*)"data/MODEL/playerhandL.obj", &g_Model_LArm, _api);
		LoadModel((char*)"data/MODEL/playerlegR.obj", &g_Model_RLeg, _api);
		LoadModel((char*)"data/MODEL/playerlegL.obj", &g_Model_LLeg, _api);


		// 埵抲丒夞揮丒僗働乕儖偺弶婜愝掕
		_position = D3DXVECTOR3(0.0f, 0.0f, 200.0f);
		_rotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		_scale = D3DXVECTOR3(2.0f, 2.0f, 2.0f);
		_vel = { 0,0,0 };
		_use = true;
		_speed = 1350;
		//摉偨傝敾掕梡僒僀僘偺弶婜愝掕
		size = D3DXVECTOR3(100.0f, 100.0f, 100.0f);
		frame = 0;
		lerpT = 0;
		//_se = LoadSound((char*)"data/SE/shot001.wav");
		fsm->SetCurrentState(BattlePhase::Instance());
		fsm->ChangeState(BattlePhase::Instance());
		_canBuild = false;
		// 塭偺僙僢僩乮塭偼崅偝傪0偵偟偰昞帵偝偣傞乯
		//_shadow = SetShadow(D3DXVECTOR3(_pos.x, 0.0f, _pos.z), 200.0f);

	}

	~Player()
	{
		delete fsm;
	}

	bool			_canBuild;
	int				shadow;		// 塭偺幆暿斣崋
	D3DXVECTOR3     size;		// 摉偨傝敾掕梡僒僀僘
	int				currency;
	int				se;
	float			lerpT;
	float 			frame;
	Vec3			topDownPosition;
	Vec3			topDownRotation;
	Vec3			thirdPersonPosition;
	Vec3			thirdPersonRotation;
	HitBox			_hitBox;
	DirectXAPI*		_api;


	DX11_MODEL	g_Model_Body;
	DX11_MODEL	g_Model_RArm;
	DX11_MODEL	g_Model_LArm;
	DX11_MODEL	g_Model_RLeg;
	DX11_MODEL	g_Model_LLeg;

	StateMachine<Player> *fsm;
	Render* GetComponent() const { return _renderComponent; }
	void DrawAnim(float* frame, D3DXVECTOR3& rot, D3DXVECTOR3& pos);
	void Update(double deltaTime) override;
	void Draw() override;
	bool Discard() const override;
};
