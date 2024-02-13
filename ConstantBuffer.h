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
	float		Dummy;				// 16byte���E�p
};

// ���C�g�p�t���O�\����
struct LIGHTFLAGS
{
	int			Type;		//���C�g�^�C�v�ienum LIGHT_TYPE�j
	int         OnOff;		//���C�g�̃I��or�I�t�X�C�b�`
	int			Dummy[2];
};

// ���C�g�p�萔�o�b�t�@�\����
struct LIGHT_CBUFFER
{
	D3DXVECTOR4	Direction[LIGHT_MAX];	// ���C�g�̕���
	D3DXVECTOR4	Position[LIGHT_MAX];	// ���C�g�̈ʒu
	D3DXCOLOR	Diffuse[LIGHT_MAX];		// �g�U���̐F
	D3DXCOLOR	Ambient[LIGHT_MAX];		// �����̐F
	D3DXCOLOR	Specular[LIGHT_MAX];
	D3DXVECTOR4	Attenuation[LIGHT_MAX];	// ������
	LIGHTFLAGS	Flags[LIGHT_MAX];		// ���C�g���
	int			Enable;					// ���C�e�B���O�L���E�����t���O
	int			Dummy[3];				// 16byte���E�p
};

struct CameraBufferType
{
	D3DXVECTOR3 cameraPosition;
	float padding;  // ����ȷ���ṹ���СΪ16�ֽ�
};