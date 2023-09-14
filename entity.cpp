#include "entity.h";
#include "globals.h"

Entity::Entity(const char* name, const char* description, string aliases) :
	name(name), description(description)
{

	string delimiter = ", ";

	size_t pos = 0;
	std::string token;
	while ((pos = aliases.find(delimiter)) != std::string::npos) {
		token = aliases.substr(0, pos);
		alias.push_back(token);
		aliases.erase(0, pos + delimiter.length());
	}
	if (aliases.size() > 0) 
		alias.push_back(aliases);
}

Entity::~Entity()
{}

void Entity::Look() const {

}

bool Entity::Is(const char* n) {
	if (Same(n, name)) {
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

void Entity::Open(string key = "") const
{
	cout << "That doesn't make sense.\n";
}

