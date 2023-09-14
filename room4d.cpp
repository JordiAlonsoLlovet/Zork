#include "room4d.h"
#include "globals.h"
#include "object.h"

Room4d::Room4d(Room* present, Room* past):
	past(past)
{
	stages[0] = present;
	name = present->name;
};

Room* Room4d::Get(Time t)
{
	if (t == Time::PAST)
		return past;
	else return stages[stage];
}

void Room4d::AddStage(Room* r)
{
	stages[1] = r;
}

void Room4d::AddItem(Object* i, int s)
{
	if (s == 0) past->Drop(i);
	else stages[s - 1]->Drop(i);
}

void Room4d::SetCondition(Action a, Object* i, Object* c)
{
	condition.action = a;
	condition.object = i->name;
	if (c == NULL)
		condition.container = NULL;
	else
		condition.container = c->name;
}

void Room4d::AdvanceStage() {
	if (CheckCondition())
		stage = 1;
	else stage = 0;
	
}

bool Room4d::CheckCondition() {
	if (condition.action == Action::NOTHING) return false;
	if (condition.container != NULL) {
		for (list<Object*>::const_iterator it = past->items.begin(); it != past->items.cend(); ++it)
		{
			if ((*it)->Is(condition.container)) {
				for (list<Object*>::const_iterator it2 = (*it)->inside.begin(); it2 != (*it)->inside.cend(); ++it2)
				{
					if ((*it2)->Is(condition.object)) {
						return condition.action == Action::PUT;
					}
				}
			}
		}
	}
	else {
		for (list<Object*>::const_iterator it = past->items.begin(); it != past->items.cend(); ++it)
		{
			if ((*it)->Is(condition.object)) {
				return condition.action == Action::PUT;
			}
		}
	}
	return condition.action == Action::REMOVE;
}
