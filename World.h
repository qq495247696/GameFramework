/*********************************************************************
 * \file   World.h
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#pragma once
#include <list>
#include <vector>
#include <string>
#include "object.h"
class World
{
public:
	World() = default;
	~World() 
	{
		for (auto x : _objectList)
		{
			delete x;
		}
		_objectList.clear();
	}

	void Update(double deltaTime)
	{
		for (auto x : _objectList)
		{
			x->Update(deltaTime);
		}
	}

	void Draw() 
	{
		for (auto x : _objectList)
		{
			x->Draw();
		}
	}

	void AddObject(Object* object)
	{
		_objectList.push_back(object);
	}

	template<typename T>
	std::vector<T> GetObjectsWithTag(const std::string& tag)
	{
		std::vector<T*> return_entity;

		for (auto x : _objectList)
		{
			if (x->GetTag() != tag) continue;

			if (T* t = dynamic_cast<T*>(x))
			{
				return_entity.push_back(t);
			}
		}
		return return_entity;
	}

	template<typename T >
	T* GetObjectWithTag(const std::string& tag)
	{
		for (auto x : _objectList)
		{
			if (x->GetTag() != tag) continue;

			if (T* t = dynamic_cast<T*>(x))
			{
				return t;
			}
		}
	}

	void CleanUp()
	{
		for (auto it = _objectList.begin(); it != _objectList.end(); )
		{
			if ((*it)->Discard())
			{
				delete* it;
				it = _objectList.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
private:
	std::list<Object*>	_objectList;
};
