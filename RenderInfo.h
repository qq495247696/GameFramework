#pragma once
#include"main.h"
enum LIGHT_TYPE
{
	LIGHT_TYPE_NONE,		//ライト無し
	LIGHT_TYPE_DIRECTIONAL,	//ディレクショナルライト
	LIGHT_TYPE_POINT,		//ポイントライト

	LIGHT_TYPE_NUM
};

enum BLEND_MODE
{
	BLEND_MODE_NONE,		//ブレンド無し
	BLEND_MODE_ALPHABLEND,	//αブレンド
	BLEND_MODE_ADD,			//加算ブレンド
	BLEND_MODE_SUBTRACT,	//減算ブレンド
	BLEDD_MODE_NUM
};

enum CULL_MODE
{
	CULL_MODE_NONE,			//カリング無し
	CULL_MODE_FRONT,		//表のポリゴンを描画しない(CW)
	CULL_MODE_BACK,			//裏のポリゴンを描画しない(CCW)

	CULL_MODE_NUM
};

enum ADDRESS_MODE
{
	ADDRESS_MODE_WRAP,
	ADDRESS_MODE_MIRROR,
	ADDRESS_MODE_CLAMP,
	ADDRESS_MODE_BORDER,

	ADDRESS_MODE_NUM
};

enum FILTER_MODE
{
	FILTER_MODE_POINT,
	FILTER_MODE_LINEAR,
	FILTER_MODE_ANISOTROPIC,

	FILTER_MODE_NUM
};

struct MATERIAL
{
	D3DXCOLOR	Ambient;
	D3DXCOLOR	Diffuse;
	D3DXCOLOR	Specular;
	D3DXCOLOR	Emission;
	float		Shininess;
	int			noTexSampling;
	int         Polyline;
	float		Dummy;	//16byte境界用
};

// ライト構造体
struct LIGHT {
	D3DXVECTOR4 Direction;	// ライトの方向
	D3DXVECTOR4 Position;	// ライトの位置
	D3DXCOLOR	Diffuse;	// 拡散光の色
	D3DXCOLOR   Ambient;	// 環境光の色
	D3DXCOLOR	Specular;
	float		Attenuation;// 減衰率
	int			Type;		// ライト種別
	int			Enable;		// 有効フラグ
	float		Dummy;		//16byte境界用
};

struct VERTEX_3D
{
	D3DXVECTOR3 Position;//座標
	D3DXVECTOR3 Normal;//法線
	D3DXCOLOR  Diffuse;//頂点カラー
	D3DXVECTOR2 TexCoord;//UV値
};
