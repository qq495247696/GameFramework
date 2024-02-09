#include "Wall.h"
#include "Utility.h"
#include "Texture.h"
#include "main.h"
#include "model.h"



static DX11_MODEL	g_Model;
static UINT  _indexCount;
static MATERIAL g_material;
static unsigned int g_TexNo;

Wall g_wall;
void InitWall(void)
{
	LoadModel((char*)"data/MODEL/wall.obj", &g_Model);
	g_wall.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_wall.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_wall.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Model.SubsetArray->Material.Material.Diffuse = {1.0,1.0,1.0,1.0};
	g_Model.SubsetArray->Material.Material.Ambient = { 1.0,1.0,1.0,1.0 };
	g_Model.SubsetArray->Material.Material.Specular = { 1.0,1.0,1.0,1.0 };
}

void UninitWall(void)
{
	UnloadModel(&g_Model);
}

void UpdateWall(void)
{
}

void DrawWall(void)
{
	//SetCullingMode(CULL_MODE_NONE);
	SetCullingMode(CULL_MODE_BACK);
	SetLightEnable(true);
	// 嵓ｵ罕ﾐ･ﾃ･ﾕ･｡ﾔOｶｨ
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	// ワールドマトリックスの初期化（単位行列を作る関数）
	D3DXMatrixIdentity(&g_wall.mtxWorld);

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, g_wall.scl.x, g_wall.scl.y, g_wall.scl.z);
	D3DXMatrixMultiply(&g_wall.mtxWorld, &g_wall.mtxWorld, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_wall.rot.y, g_wall.rot.x, g_wall.rot.z);
	D3DXMatrixMultiply(&g_wall.mtxWorld, &g_wall.mtxWorld, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, g_wall.pos.x, g_wall.pos.y, g_wall.pos.z);
	D3DXMatrixMultiply(&g_wall.mtxWorld, &g_wall.mtxWorld, &mtxTranslate);

	// ワールドマトリックスの設定
	SetWorldMatrix(&g_wall.mtxWorld);
	//objモデルの描画
	DrawModel(&g_Model);
	SetLightEnable(true);
	SetCullingMode(CULL_MODE_NONE);
	
}
