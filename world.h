#include <list>
#include <vector>
#include<string>
#include "room4d.h"
#include "path.h"
#include "object.h"

 
class World {
public:
	World();
	~World();
	void Look();
	bool PutCommand(vector<string>& args);
	bool ParseCommand(vector<string>& args);
	bool Move(std::string direction);
	void PrintInventory();
	void TimeTravel();
	list<Entity*> GetAvailables();
	Path* FindPath(string entity);
	Object* FindRoom(string entity);
	Object* FindInventory(string entity);
	Object* FindInReach(string entity);
	//Path* FindPath(string entity);

	list<Room4d*> rooms;
	list<Path*> paths;
	Time now;
	Room4d* currentLocation;
	list<Object*> inventory;
};
