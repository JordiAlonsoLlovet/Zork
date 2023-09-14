#pragma once

#include "globals.h"
#include "entity.h"
#include "room4d.h"

// -------------------------------------------------
bool Same(const string& a, const string& b)
{
	return _stricmp(a.c_str(), b.c_str()) == 0;
}

bool Same(const char* a, const string& b)
{
	return _stricmp(a, b.c_str()) == 0;
}

bool Same(const string& a, const char* b)
{
	return _stricmp(a.c_str(), b) == 0;
}

bool SameEnt(Entity* a, Entity* b)
{
	return _stricmp(a->name, b->name) == 0;
}

bool SameRoom(const Room4d* a, const Room4d* b) {
	return _stricmp(a->name, b->name) == 0;
}

void Tokenize(const string& line, vector<string>& arguments)
{
	const char* str = line.c_str();

	do
	{
		const char* begin = str;

		while (*str != ' ' && *str)
			str++;

		arguments.push_back(string(begin, str));
	} while (0 != *str++);
}
