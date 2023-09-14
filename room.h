#pragma once

#include <string>
#include <list>
#include "entity.h"

class Object;

class Room : public Entity
{
public:
	Room(const char* name, const char* description);
	~Room();
	void Look() const;
	void Drop(Object* item);
	//Path* GetExit(const string& direction) const;

	list<Object*> items;

};