#pragma once
#include "UtilsD2.h"
#include "Enemy.h"
#include "CollidableObject.h"
#include "GrafixD2.h"
class ObjContainer
{
protected:
	std::vector<CollidableObject*>list;
public:
	ObjContainer() {}
	virtual ~ObjContainer()
	{
		std::for_each(list.begin(), list.end(), delete_ptr<CollidableObject>);
	}
	void Add(CollidableObject* obj);
	CollidableObject* GetObj(UINT index);
	virtual void Rasterize() = 0;
	virtual void Update(CollidableObject& player,float& dt) = 0;
	virtual void DoCollision(CollidableObject& obj) {};
	virtual void Remove(UINT& index)
	{
		size_t size = list.size();
		auto ptr1 = list.begin() + index;
		std::for_each(ptr1, ptr1 + 1, delete_ptr<CollidableObject >);
		list.erase(ptr1);
		list.resize(size - 1);
	}
	
};