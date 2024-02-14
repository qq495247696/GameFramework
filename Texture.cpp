/*==============================================================================

   �e�N�X�`���̓ǂݍ��� [texture.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/

#include "texture.h"
int TextureTool::LoadTexture(char* fileName, DirectXAPI* api)
{
	//�ǂݍ��܂�Ă���e�N�X�`�����𒲂ׂāA�����̂��̂�
//���łɓǂݍ��܂�Ă����炻�̔ԍ���Ԃ�
	for (unsigned int i = 0; i < _textureIndex; i++)
	{
		//�e�N�X�`�������r
		if (strcmp(_textureName[i], fileName) == 0)
		{
			return i;
		}
	}

	//�ǂݍ��ݍő吔�𒴂��Ă����畉�̒l��Ԃ�
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
		//�ǂݍ��݂Ɏ��s�����ꍇ�A���̒l��Ԃ�
		return -1;
	}

	//�ǂݍ��񂾃e�N�X�`������ۑ�����
	strcpy_s(_textureName[_textureIndex], 256, fileName);

	int retIndex = _textureIndex;

	//�C���f�b�N�X����i�߂�
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
	//index�̕s���l�`�F�b�N(���̒l)
	if (index < 0)
		return NULL;

	//index�̕s���l�`�F�b�N(�ő吔�I�[�o�[)
	if (index >= (int)_textureIndex)
		return NULL;

	return &_pTexture[index];
}
