#pragma once
#include "main.h"
class DirectXAPI;
class Object;
class Render
{
public:
	Render(DirectXAPI* api):_dApi(api) { ; }
	virtual ~Render() { ; }
	virtual	void Draw(Object* object) = 0;
	DirectXAPI* GetApi() { return _dApi; }
protected:
	DirectXAPI*				_dApi;//����ֻ��directX��Ҫ����������Ⱦ�ӿڵĻ�Ҳ���Գ���������ӹ��캯������
};