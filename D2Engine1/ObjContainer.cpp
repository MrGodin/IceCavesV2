#include "ObjContainer.h"

void ObjContainer::Add(CollidableObject* obj)
{
	
	list.push_back(obj);
	
}

CollidableObject* ObjContainer::GetObj(UINT index)
{
	assert(index >= 0);
	assert(index < list.size());
	return list[index];
};