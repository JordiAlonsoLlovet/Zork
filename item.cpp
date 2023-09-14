#include "item.h"

Item::Item(const char* name, const char* description, string alias, Object* parent, bool container, bool opens, bool opened) :
	Object(name, description, parent, alias, container, opens, opened)
{
	if(parent != NULL) parent->inside.push_back(this);
}

bool Item::PutIn(Object* container) {
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

bool Item::Take() {
	if (parent != NULL) {
		parent->inside.remove(this);
		parent = NULL;
	}
	return true;
}
