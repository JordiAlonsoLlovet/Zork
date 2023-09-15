#include "path.h"
#include "room4d.h"
#include "object.h"

Path::Path(const char* name, const char* opposite_name, const char* description, Room4d* origin, Room4d* destination, const char* opposite_desc, Time t, string alias) :
	Entity(name, description, alias), opposite_name(opposite_name), origin(origin), destination(destination), timeline(t), opposite_desc(opposite_desc)
{
	if (opposite_desc == NULL) opposite_desc = description;
}

Path::~Path()
{}

bool Path::IsNow(Time now) {
	return timeline == now || timeline == Time::BOTH;
}

bool Path::OpositeIs(const char* n) {
	if (Same(n, opposite_name)) {
		return true;
	}
	else {
		for (list<string>::const_iterator it = alias.begin(); it != alias.cend(); ++it)
		{
			if (Same(*it, n))
				return true;
		}
		return false;
	}
}

void Path::Look(Room4d* from) 
{
	string d;
	if (locked) 
		cout << "To the " << name << " you see that " << messageBlock << "\n";
	else if (_stricmp(from->name, origin->name) == 0)
		cout << "To the " << name << " you see " << description << "\n";
	else if (_stricmp(from->name, destination->name) == 0)
		cout << "To the " << opposite_name << " you see " << description << "\n";
	
}

bool Path::Unlock(string k)
{
	if (!locked) cout << "This path is already open.\n";
	else if (Same(key, k))
	{
		locked = false;
		cout << messageOpen << "\n";
		return true;
	}
	return false;
}

void Path::Lock(const char* k, const char* block, const char* open)
{
	locked = true;
	key = k;
	messageBlock = block;
	messageOpen = open;
}

Room4d* Path::GetDestinationFrom(Room4d* from, Time t) {
	if (!IsNow(t)) return NULL;
	if (_stricmp(from->name, origin->name) == 0) return destination;
	else if (_stricmp(from->name, destination->name) == 0) return origin;
	else return NULL;
}

