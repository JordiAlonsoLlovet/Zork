#pragma once

#include <string>
#include <vector>

class Room4d;

enum class Time {
	PAST,
	PRESENT,
	BOTH
};

enum class Action {
	NOTHING,
	REMOVE,
	PUT
};

using namespace std;

bool Same(const string& a, const string& b);
bool Same(const char* a, const string& b);
//bool Same(const string& a, const char* b);
bool SameRoom(const Room4d* a, const Room4d* b);
void Tokenize(const string& line, vector<string>& arguments);
