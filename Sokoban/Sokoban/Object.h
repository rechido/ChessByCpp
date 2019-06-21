#pragma once
#include "eObjectType.h"

class Object
{
public:
	Object() = delete;
	Object(eObjectType objectType);
	~Object();

	bool hasNext();

	void SetObjectType(eObjectType objectType);
	eObjectType GetObjectType();
	
	void SetNextObject(Object* nextObject);
	Object* GetNextObject();

private:
	eObjectType mObjectType;
	Object* mNext;
};

