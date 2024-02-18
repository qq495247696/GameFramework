#pragma once
#include "RenderInfo.h"
#include <string>
#define	Vec3			D3DXVECTOR3
class DX11_MODEL;
class World;
class Render;
class Object
{
public:
	Object(Render* render,const std::string& tag, World* world) :_renderComponent(render),_tag(tag), _world(world) { ; }
	Object(const std::string& tag, World* world) :_tag(tag), _world(world) { ; }
	Object(const int texNo,const std::string& tag, World* world) :_texNo(texNo),_tag(tag), _world(world) { ; }
	Object(const int texNo, Render* render, const std::string& tag, World* world) :_texNo(texNo), _renderComponent(render), _tag(tag), _world(world) { ; }
	Object(DX11_MODEL* model, Render* render,const std::string& tag,World* world ) :_model(model), _renderComponent(render), _tag(tag),_world(world){ }
	virtual ~Object() {};
	void Attach(World* world) { _world = world; }

	virtual void Update(double deltaTime) = 0;
	virtual void Draw()= 0;
	//紒E馐欠褚僮约海祷刂凳莟rue的话从world的List中移除自己
	virtual bool Discard()const = 0;

	void SetPosition(const Vec3& pos) { _position = pos; }
	void SetPositionX(const float x) { _position.x = x; }
	void SetPositionZ(const float z) { _position.z = z; }
	void SetRotation(const Vec3& rot) { _rotate = rot; }
	void SetTexNo(const int texno) { _texNo = texno; }
	void SetVel(const Vec3& vel) { _vel = vel; }
	void SetSpeed(const float speed) { _speed = speed; }
	void SetUse(const bool use) { _use = use; }
	const std::string& GetTag()const { return _tag; }
	const float GetSpeed()const { return _speed; }
	const Vec3& GetPosition()const { return _position; }
	const Vec3& GetRotation()const { return _rotate; }
	const Vec3& GetScale()const { return _scale; }
	const Vec3& GetVel()const { return _vel;}
	const int	GetTexNo()const { return _texNo; }
	D3DXMATRIX* GetWorldMatrix(){ return &_worldMtx; }
	DX11_MODEL* GetModel()const { return  _model; }
	World* GetWorld()const { return _world; }
	const int GetHp()const { return _hp; }
	void SetHp(const int hp) { _hp = hp; }
protected:
	Vec3					_position;
	Vec3					_rotate;
	Vec3					_scale;
	Vec3					_vel;
	bool					_use;
	float					_speed;
	DX11_MODEL*				_model;
	int						_texNo;
	int						_hp;
	D3DXMATRIX				_worldMtx;
	Render*					_renderComponent;
private:
	std::string				_tag;
	World*					_world;

public:

	Object() = default;
};
