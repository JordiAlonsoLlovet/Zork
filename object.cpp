#include "object.h"

Object::Object(const char* name, const char* description, bool canPickUp, string alias, bool container, bool opens, bool opened) :
	Entity(name, description, alias), canPickUp(canPickUp), container(container), opens(opens), opened(opened)
{

}

Object::Object(const char* name, const char* description, Object* parent, string alias, bool container, bool opens, bool opened) :
	Entity(name, description, alias), canPickUp(canPickUp), container(container), opens(opens), opened(opened), parent(parent)
{
	canPickUp = true;
	if (parent != NULL) parent->inside.push_back(this);
}

void Object::Look(bool extended) const
{
	if (extended) {
		cout << description << "\n";
		if (opened)
		{
			for (list<Object*>::const_iterator it = inside.begin(); it != inside.cend(); ++it)
			{
				cout << "There is a ";
				(*it)->Look(false);
				cout << " inside.\n";
			}
		}
	}
	else cout << name;
}

bool Object::PutIn(Object* container) {
	if (!canPickUp)
	{
		cout << "Wait... How do you have that?\n";
		return false;
	}
	if (!container->container) cout << "This " << container->name << "can't hold anything inside";
	else if (!container->opened) cout << "This " << container->name << "is closed";
	else {
		if (parent != NULL) {
			parent->inside.remove(this);
		}
		parent = container;
		container->inside.push_back(this);
		return true;
	}
	return false;
}

bool Object::Take() {
	if (canPickUp) {
		if (parent != NULL) {
			parent->inside.remove(this);
			parent = NULL;
		}
		cout << "You put the " << name << " in your inventory.\n";
		return true;
	}
	else {
		cout << "You can't pick this up." << "\n";
		return false;
	}
	
}

void Object::Open() {
	if (!opens) cout << name << " can't be opened.\n";
	else if (opened) cout << name << " is already open.\n";
	else {
		opened = true;
		cout << "You pry the " << name << " open.\n";
		Look();
	}

}

Object* Object::Find(string query) {
	for (list<Object*>::const_iterator it = inside.begin(); it != inside.cend(); ++it)
	{
		if ((*it)->Is(query.c_str()))
			return *it;
	}
	return NULL;
}