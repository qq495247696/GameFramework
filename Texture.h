#pragma once


#include "render.h"
#include "DirectXAPI.h"

class TextureTool
{
public:
	static TextureTool* Get()
	{
		static TextureTool p;
		return &p;
	}

	int LoadTexture(char* fileName, DirectXAPI* api);
	void UninitTexture(void);
	ID3D11ShaderResourceView** GetTexture(int index);
private:
	TextureTool() {}
	~TextureTool() {}
	ID3D11ShaderResourceView* _pTexture[100] = {};
	unsigned int _textureIndex = 0;					// テクスチャ
	char _textureName[100][256] = {};	// テクスチャ
};
