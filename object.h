#include "entity.h"

class Object: public Entity {
public:
	Object(const char* name, const char* description, bool canPickUp, string alias = "", bool container = false, bool opens = false, bool opened = true);
	Object(const char* name, const char* description, Object* parent, string alias = "", bool container = false, bool opens = false, bool opened = true);
	~Object();
	void Look(bool extended = true) const;
	void Open();
	bool Take();
	bool PutIn(Object* container);
	Object* Find(string query);
	list<Object*> inside;

	Object* parent;
	bool container;
	bool opens;
	bool opened;
	bool canPickUp;
};