#include "world.h"
#include "entity.h"
#include "globals.h"
#include "room.h"
#include "room4d.h"
#include "pamphlet.cpp"

class Room;

World::World() {
	now = Time::PRESENT;
	auto box = new Object("box", "a small wooden box.", true, "chest", true, true, false);
	Room* entr = new Room("Bridge", "You've reach the begining of your adventure.\nYou stand at the edge of a great canyon with the ruins of a collapsed bridge.\nFar to the north you can see a great castle.");
	Room* p_entr = new Room("Bridge", "You stand at the edge of a great canyon crossed by a stone bridge");
	Room4d* entrance = new Room4d(entr, p_entr);
	auto grove = new Room4d(
		new Room("Grove", "You are in an overgrown forest."),
		new Room("Grove", "You are in an young forest.")
	);
	auto pond = new Room4d(
		new Room("Pond", "A serene glade with a contaminated pond.\nSmells like death."),
		new Room("Pond", "A serene glade with a pond.")
	);
	pond->AddStage(new Room("Pond", "A serene glade with a shimmering pond.\nNow the water is clean and a scaly hand appears from bellow the water holding something shiny.\nYou hear a feminine voice saying \"Thank you\""));
	auto c_ent = new Room4d(
		new Room("Gateway", "You stand in front of the castle. The gate is as big as imposing."),
		new Room("Gateway", "You stand in front of the castle. The gate is as big as imposing.\nJust how old is this place?")
	);
	auto cave = new Room4d(
		new Room("Cave", "You are in the entrance of a dark cave."),
		new Room("Cave", "You are in the entrance of a dark cave.\nYou can see a path going deeper inside, but it's too narrow for you.\nMaybe erosion will open the way in a few centuries.")
	);
	auto passage = new Room4d(
		new Room("Passage", "You move through a narrow and dark tunnel."),
		new Room("Passage", "You move through a narrow and dark tunnel.")
	);
	auto castle = new Room4d(
		new Room("Castle", "You stand on the Palace's main chamber."),
		new Room("Castle", "You stand on the Palace's main chamber.")
	);
	auto jail = new Room4d(
		new Room("Jail", "You've made it to the Palace's jail, but it's too late. You find the long dead bones of the princess on the grond.\nPoor girl must have starved."),
		new Room("Jail", "The jail is empty now, it will be centuries before the princess is brough here.")
	);
	jail->AddStage(new Room("Jail", "You fond the princess! Thanks to the fruits given by a conviniently placed tree the princes has survived until now!\nCongratulations! You did it! You have saved the pricess and beaten Time Dork!"));

	
	auto clock = new Object("clock", "a complex pocket clock. Looks sort of magical, somehow.", box, "watch");
	auto pamphlet = new Object("pamphlet", pamphletText.c_str(), box, "paper");
	auto tree = new Object("tree", "a mighty tree.", false, "", true);
	auto apple = new Object("apple", "a delicious looking apple.", tree, "fruit", true, true, false);
	apple->canPickUp = true;
	auto seed = new Object("seed", "a regular apple seed. With enough time it could make a tree", apple);
	auto sword = new Object("sword", "a glittering magical sword. Perfect for slaying magical beasts!", true, "weapon, blade, excalibur");
	auto trash = new Object("trash", "a bag full of nasty stuff sipping through. Very bad for the environment.", true, "bag, rubbish, garbage");
	auto torch = new Object("torch", "a torch that burns eternally. Looks like it will fit in your inventory.", true, "fire");
	auto earth = new Object("soil", "a small patch of soil inside the jail. As sad as it looks it actually seems like something could grow here.",false, "land, earth, dirt", true);
	auto key = new Object("key", "The key to the Palace", true);

	pond->SetCondition(Action::REMOVE, trash);
	jail->SetCondition(Action::PUT, seed, earth);

	entrance->AddItem(box, 1);
	grove->AddItem(tree, 1);
	pond->AddItem(sword, 2);
	pond->AddItem(trash, 0);
	c_ent->AddItem(torch, 1);
	castle->AddItem(key, 1);
	jail->AddItem(earth, 0);
	
	auto bridge = new Path("north", "south", "A resplendent and firm bridge.", entrance, grove, NULL, Time::PAST);
	auto path1 = new Path("east", "south", "a path leading to the garden's pond.", grove, pond, "a path leading back to the grove.");
	auto path2 = new Path("east", "west", "a path leading to the garden's pond.", c_ent, pond, "a path leading to the Palace.");
	auto path3 = new Path("north", "south", "a path leading to the Palace.", grove, c_ent, "a path leading back to the grove.");
	auto cave_ent = new Path("west", "east", "you can see the entrance of a cave", c_ent, cave, "a path leading to the Palace.");
	auto hpass1 = new Path("north", "south", "a tunnel goes deeper into the darkness.", cave, passage, NULL, Time::PRESENT, "spiders, spider, coweb, cowebs");
	hpass1->Lock("torch", "the way is blocked by a nest of giant spiders. Deadly venomous and keen on human meat.\nThe cave is covered in giant cowebs; they are extremely sticky, but also very flamable.", "The fire quickly ignites the cowebs, and you see the spiders turn to ash.");
	auto hpass2 = new Path("north", "south", "you can see a door.", passage, castle);
	auto door = new Path("south", "north", "there is the Place's imposing door", castle, c_ent, NULL, Time::BOTH, "door, gate");
	door->Lock("key", "The door is tightly locked.", "You unlock the door");
	auto dragon = new Path("north", "south", "there are stairs going down.", castle, jail, "there are stairs going up.", Time::BOTH, "dragon");
	dragon->Lock("sword", "there is a massive Elder Dragon guarding the path to the princess.", "You slay the dragon! That was surprisingly easy...");

	rooms.push_back(entrance);
	rooms.push_back(grove);
	rooms.push_back(pond);
	rooms.push_back(c_ent);
	rooms.push_back(cave);
	rooms.push_back(passage);
	rooms.push_back(castle);
	rooms.push_back(jail);

	paths.push_back(bridge);
	paths.push_back(path1);
	paths.push_back(path2);
	paths.push_back(path3);
	paths.push_back(cave_ent);
	paths.push_back(hpass1);
	paths.push_back(hpass2);
	paths.push_back(door);
	paths.push_back(dragon);

	currentLocation = entrance;
}

void World::Look() {
	currentLocation->Get(now)->Look();
	for (list<Path*>::const_iterator it = paths.begin(); it != paths.cend(); ++it)
	{
		Room4d* destination = (*it)->GetDestinationFrom(currentLocation, now);
		if (destination != nullptr) {
			(*it)->Look(currentLocation);
		}
	}
}

bool World::Move(string direction) {
	for (list<Path*>::const_iterator it = paths.begin(); it != paths.cend(); ++it)
	{
		if ((Same((*it)->name, direction) && SameRoom(currentLocation, (*it)->origin)) || (Same((*it)->opposite_name, direction) && SameRoom(currentLocation, (*it)->destination)))
		{
			Room4d* destination = (*it)->GetDestinationFrom(currentLocation, now);
			if (destination != NULL && (*it)->locked) {
				cout << (*it)->messageBlock << "\n";
				return false;
			}
			else if (destination != NULL)
			{
				currentLocation = destination;
				Look();
				return true;
			}
		}
	}
	cout << "You can't go there.\n";
	return false;
}

void World::TimeTravel() {
	if (FindInventory("clock") != NULL)
	{
		if (now == Time::PRESENT) now = Time::PAST;
		else {
			now = Time::PRESENT;
			//check conditions for rooms
			for (list<Room4d*>::const_iterator it = rooms.begin(); it != rooms.cend(); ++it) {
				(*it)->AdvanceStage();
			}
		}
		Look();
	}
}

void World::PrintInventory()
{
	cout << "In your pockets you have: \n";
	for (list<Object*>::const_iterator it = inventory.begin(); it != inventory.cend(); ++it)
	{
		cout << "A ";
		(*it)->Look(false);
		cout << "\n";
	}
}

bool World::PutCommand(vector<string>& args)
{
	bool ret = true;

	if (args.size() > 0 && args[0].length() > 0)
	{
		cout << "\n";
		ret = ParseCommand(args);
	}
		
	return ret;
}

bool World::ParseCommand(vector<string>& args)
{
	bool ret = true;

	switch (args.size())
	{
	case 1: // commands with no arguments ------------------------------
	{
		if (Same(args[0], "look") || Same(args[0], "l"))
		{
			Look();
		}
		else if (Same(args[0], "north") || Same(args[0], "south") || Same(args[0], "east") || Same(args[0], "west"))
		{
			Move(args[0]);
		}
		else if (Same(args[0], "inventory") || Same(args[0], "i"))
		{
			PrintInventory();
		}
		else if (Same(args[0], "clock") || Same(args[0], "c") || Same(args[0], "watch")) {
			TimeTravel();
		}
		else
			ret = false;
		break;
	}
	case 2: // commands with one argument ------------------------------
	{
		if (Same(args[0], "look") || Same(args[0], "l") || Same(args[0], "examine") || Same(args[0], "ex"))
		{
			Object* l = FindInReach(args[1]);
			if (l == NULL) l = FindInventory(args[1]);
			if (l != NULL) l->Look();
			else cout << "That's not in sight.\n";
		}
		else if (Same(args[0], "go"))
		{
			Move(args[1]);
		}
		else if (Same(args[0], "take") || Same(args[0], "pick") || Same(args[0], "grab") || Same(args[0], "get"))
		{
			Object* target = FindInReach(args[1]);
			if (target == NULL) cout << "That's not in here\n";
			else if (target->Take()) {
				currentLocation->Get(now)->items.remove(target);
				inventory.push_back(target);
			}
		}
		else if (Same(args[0], "open") || Same(args[0], "break") || Same(args[0], "eat") || Same(args[0], "unlock"))
		{
			Object* target = FindInReach(args[1]);
			if (target == NULL) {
				target = FindInventory(args[1]);
			}
			if (target == NULL) {
				Path* p = FindPath(args[1]);
				if (p != NULL) {
					cout << "Maybe you need an item to open the way?\n";
				}
				else cout << "There is no " << args[1] << " here.\n";
			}
			else target->Open();
		}
		else if (Same(args[0], "drop") || Same(args[0], "put"))
		{
			Object* target = FindInventory(args[1]);
			if (target == NULL) cout << "You don't have that.\n";
			else
			{
				currentLocation->Get(now)->Drop(target);
				inventory.remove(target);
			}
		}
		else if (Same(args[0], "use"))
		{
			if (Same(args[1], "clock") || Same(args[0], "watch")) {
				TimeTravel();
			}
			
		}
		else
			ret = false;
		break;
	}
	case 3: // commands with two arguments ------------------------------
	{
		if (Same(args[0], "look"))
		{
			Object* l = FindInReach(args[2]);
			if (l != NULL) l->Look();
			else cout << "That's not in sight.\n";
		}
		else
			ret = false;
		break;
	}
	case 4: // commands with three arguments ------------------------------
	{
		if (Same(args[0], "open") || Same(args[0], "unlock") || Same(args[0], "hit") || Same(args[0], "attack") || Same(args[0], "burn"))
		{
			Path* p = FindPath(args[1]);
			Object* key = FindInventory(args[3]);
			if (p == NULL) cout << "There is no " << args[1] << " in here.\n";
			else if (key == NULL) cout << "You don't have the " << args[1] << ".\n";
			else {
				p->Unlock(key->name);
			}
		}
		else if (Same(args[0], "use"))
		{
			Path* p = FindPath(args[3]);
			Object* key = FindInventory(args[1]);
			if (p == NULL) cout << "There is no " << args[3] << " in here.\n";
			else if (key == NULL) cout << "You don't have the " << args[3] << ".\n";
			else {
				p->Unlock(key->name);
			}
		}
		else if (Same(args[0], "drop") || Same(args[0], "put"))
		{
			Object* container = FindInventory(args[3]); //See if the contaner is in the inventory
			if (container == NULL) container = FindRoom(args[3]); //Else look in the room
			if (container != NULL) {
				Object* t = FindInventory(args[1]);
				if (t == NULL) cout << "You don't have a" << args[1] << "\n";
				else if (t->PutIn(container));
			}
			else cout << "There is no" << args[3] << "around.\n";
			
		}
		else
			ret = false;
		break;
	}
	default:
		ret = false;
	}
	cout << "\n";
	return ret;
}


// FIND TARGET OF ACTION//

Path* World::FindPath(string entity)
{
	for (list<Path*>::const_iterator it = paths.begin(); it != paths.cend(); ++it)
	{
		if (((*it)->Is(entity.c_str()) && SameRoom(currentLocation, (*it)->origin)) || (((*it)->OpositeIs(entity.c_str()) && SameRoom(currentLocation, (*it)->destination))))
		{
			return *it;
		}
	}
	return NULL;
}

Object* World::FindRoom(string entity)
{
	list<Object*> a = currentLocation->Get(now)->items;
	for (list<Object*>::const_iterator it = a.begin(); it != a.cend(); ++it)
	{
		if ((*it)->Is(entity.c_str()))
			return *it;
	}
	return NULL;
}

Object* World::FindInventory(string entity)
{
	list<Object*> a = inventory;
	for (list<Object*>::const_iterator it = a.begin(); it != a.cend(); ++it)
	{
		if ((*it)->Is(entity.c_str()))
			return *it;
	}
	return NULL;
}

Object* World::FindInReach(string entity) 
{
	Object* r = FindRoom(entity);
	if (r != NULL) return r;
	list<Object*> a = currentLocation->Get(now)->items;
	for (list<Object*>::const_iterator it = a.begin(); it != a.cend(); ++it)
	{
		if ((*it)->Is(entity.c_str()))
			return *it;
		else if ((*it)->container)
		{
			r = (*it)->Find(entity);
			if (r != NULL) return r;
		}
	}
	for (list<Object*>::const_iterator it = inventory.begin(); it != inventory.cend(); ++it)
	{
		if ((*it)->container)
		{
			r = (*it)->Find(entity);
			if (r != NULL) return r;
		}
	}
	return NULL;
}