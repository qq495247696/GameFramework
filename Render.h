#pragma once
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
	DirectXAPI*				_dApi;//现在只有directX，要是有其他渲染接口的话也可以抽象出来，从构造函数传参
};
