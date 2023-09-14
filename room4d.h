#pragma once

#include <string>
#include <list>
#include "globals.h"
#include "room.h"

class Path;

class Room4d
{
public:

	Room4d(Room* present, Room* past);
	~Room4d();


	Room* Get(Time t);
	Path* GetExit(const string& direction) const;
	void MoveStage();
	void AddStage(Room* r);
	void AddItem(Object* i, int stage);
	void AdvanceStage();
	void SetCondition(Action a, Object* i, Object* c = NULL);

	Room* stages[2];
	Room* past;

	const char* name;

private: 
	int stage = 0;
	struct {
		Action action;
		const char* object;
		const char* container;
	} condition;
	bool CheckCondition();
};