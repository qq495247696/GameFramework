#pragma once
#include "main.h"
#define LIGHT_MAX		(10)
struct MATERIAL_CBUFFER
{
	D3DXCOLOR	Ambient;
	D3DXCOLOR	Diffuse;
	D3DXCOLOR	Specular;
	D3DXCOLOR	Emission;
	float		Shininess;
	int			noTexSampling;
	int			PolyLine;
	float		Dummy;				// 16byte境界用
};

// ライト用フラグ構造体
struct LIGHTFLAGS
{
	int			Type;		//ライトタイプ（enum LIGHT_TYPE）
	int         OnOff;		//ライトのオンorオフスイッチ
	int			Dummy[2];
};

// ライト用定数バッファ構造体
struct LIGHT_CBUFFER
{
	D3DXVECTOR4	Direction[LIGHT_MAX];	// ライトの方向
	D3DXVECTOR4	Position[LIGHT_MAX];	// ライトの位置
	D3DXCOLOR	Diffuse[LIGHT_MAX];		// 拡散光の色
	D3DXCOLOR	Ambient[LIGHT_MAX];		// 環境光の色
	D3DXCOLOR	Specular[LIGHT_MAX];
	D3DXVECTOR4	Attenuation[LIGHT_MAX];	// 減衰率
	LIGHTFLAGS	Flags[LIGHT_MAX];		// ライト種別
	int			Enable;					// ライティング有効・無効フラグ
	int			Dummy[3];				// 16byte境界用
};

struct CameraBufferType
{
	D3DXVECTOR3 cameraPosition;
	float padding;  // ﾓﾃﾓﾚﾈｷｱ｣ｽ盪ｹﾌ蟠｡ﾎｪ16ﾗﾖｽﾚ
};