/*==============================================================================

   テクスチャの読み込み [texture.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/

#include "texture.h"
int TextureTool::LoadTexture(char* fileName, DirectXAPI* api)
{
	//読み込まれているテクスチャ名を調べて、同名のものが
//すでに読み込まれていたらその番号を返す
	for (unsigned int i = 0; i < _textureIndex; i++)
	{
		//テクスチャ名を比較
		if (strcmp(_textureName[i], fileName) == 0)
		{
			return i;
		}
	}

	//読み込み最大数を超えていたら負の値を返す
	if (_textureIndex == 100)
	{
		return -1;
	}


	HRESULT hr = D3DX11CreateShaderResourceViewFromFile(
		api->GetDevice().Get(),
		fileName,
		NULL,
		NULL,
		&_pTexture[_textureIndex],
		NULL);

	if (S_OK != hr)
	{
		//読み込みに失敗した場合、負の値を返す
		return -1;
	}

	//読み込んだテクスチャ名を保存する
	strcpy_s(_textureName[_textureIndex], 256, fileName);

	int retIndex = _textureIndex;

	//インデックスを一つ進める
	_textureIndex++;

	/*return retIndex;*/
	return retIndex;
}

void TextureTool::UninitTexture(void)
{
	for (unsigned int i = 0; i < _textureIndex; i++)
	{
		if (_pTexture[i] != NULL)
		{
			_pTexture[i]->Release();
			_pTexture[i] = NULL;
		}
	}
}

ID3D11ShaderResourceView** TextureTool::GetTexture(int index)
{
	//indexの不正値チェック(負の値)
	if (index < 0)
		return NULL;

	//indexの不正値チェック(最大数オーバー)
	if (index >= (int)_textureIndex)
		return NULL;

	return &_pTexture[index];
}
