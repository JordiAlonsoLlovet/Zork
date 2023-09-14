
#pragma once

#include <string>
#include "globals.h"
#include "entity.h"

class Room4d;
class Object;

using namespace std;

class Path : public Entity
{
public:
	Path(const char* name, const char* opposite_name, const char* description, Room4d* origin, Room4d* destination, const char* opposite_desc = NULL, Time t = Time::BOTH, string alias = "");
	~Path();

	void Look(Room4d* from);
	bool IsNow(Time now);
	bool OpositeIs(const char* name);
	void Lock(const char* key, const char* block, const char* open);
	bool Unlock(string k);
	Room4d* GetDestinationFrom(Room4d* origin, Time t);

	bool locked;
	const char* key;
	const char* messageBlock;
	const char* messageOpen;
	const char* opposite_desc;
	string opposite_name;
	Room4d* origin;
	Room4d* destination;
	Time timeline;

};