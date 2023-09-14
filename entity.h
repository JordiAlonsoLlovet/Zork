#pragma once

#include <iostream>
#include <string>
#include <list>
using namespace std;


class Entity {
public:

	Entity(const char* name, const char* description, string alias="");
	~Entity();
	bool Is(const char* name);
	void Look() const;
	void Open(string key) const;

	const char* name;
	const char* description;
	list<string> alias;
};