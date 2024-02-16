#pragma once
#include "RenderInfo.h"
class DirectXAPI;
class Object;
class Render
{
public:
	Render(DirectXAPI* api):_dApi(api) { ; }
	virtual ~Render() { ; }
	virtual	void Draw(Object* object) = 0;
protected:
	DirectXAPI*				_dApi;//ÏÖÔÚÖ»ÓĞdirectX£¬ÒªÊÇÓĞÆäËûäÖÈ¾½Ó¿ÚµÄ»°Ò²¿ÉÒÔ³éÏó³öÀ´£¬´Ó¹¹ÔE¯Êı´«²Î
};
