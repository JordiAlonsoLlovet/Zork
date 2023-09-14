#include "room.h"
#include "object.h"

Room::Room(const char* name, const char* description) :
	Entity(name, description, "")
{

}

void Room::Look() const 
{
	cout << "**" << name << "**\n";
	cout << description << "\n";
	for (auto it = items.begin(); it != items.cend(); ++it)
	{
		cout << "There is a ";
		(*it)->Look(false);
		cout << ".\n";
	}
}

void Room::Drop(Object* item) 
{
	items.push_back(item);
}