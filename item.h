#include "object.h"

class Item : public Object {
public:
	Item(const char* name, const char* description, string alias = "", Object* parent = NULL, bool container = false, bool opens = false, bool opened = true);
	bool Take();
	bool PutIn(Object* container);

	Object* parent;
};
