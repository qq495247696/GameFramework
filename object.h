#pragma once
#include "model.h"
#include <string>
#include"Render.h"
#define	Vec3			D3DXVECTOR3
class World;
class Object
{
public:
	Object(Render* render,const std::string& tag, World* world) :_renderComponent(render),_tag(tag), _world(world) { ; }
	Object(const std::string& tag, World* world) :_tag(tag), _world(world) { ; }
	Object(const int texNo, const std::string& tag, World* world):_texNo(texNo),_tag(tag),_world(world) { ; }
	Object(DX11_MODEL* model, Render* render,const std::string& tag,World* world ) :_model(model), _renderComponent(render), _tag(tag),_world(world){ }
	virtual ~Object() {};
	void Attach(World* world) { _world = world; }

	virtual void Update(double deltaTime) = 0;
	virtual void Draw()= 0;
	//��E��Ƿ�Ҫ�����Լ�������ֵ��true�Ļ���world��List���Ƴ��Լ�
	virtual bool Discard()const = 0;

	void SetPosition(const Vec3& pos) {}
	void SetTexNo(const int texno) { _texNo = texno; }
	const std::string& GetTag()const { return _tag; }
	const Vec3& GetPosition()const { return _position; }
	const Vec3& GetRotarion()const { return _rotate; }
	const Vec3& GetScale()const { return _scale; }
	const Vec3& GetVel()const { return _vel;}
	const int	GetTexNo()const { return _texNo; }
	D3DXMATRIX* GetWorldMatrix(){ return &_worldMtx; }
	DX11_MODEL* GetModel()const { return  _model; }
protected:
	Vec3					_position;
	Vec3					_rotate;
	Vec3					_scale;
	Vec3					_vel;
	bool					_use;
	float					_speed;
	DX11_MODEL*				_model;
	int						_texNo;
	D3DXMATRIX				_worldMtx;
	World* GetWorld()const { return _world; }
	Render*					_renderComponent;
private:
	std::string				_tag;
	World*					_world;

public:

	Object() = default;
};
