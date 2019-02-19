#pragma once
#include "Bonus_Holder.h"

//saves data for room features
struct Room_Feature_Data
{
	float real_value = 0;
	char integer_value = 0;
	sf::Vector2f position = sf::Vector2f(0,0);
	Sprite_Sheet_Data *graphic;
};

//this class reprensent a room in the cube. stores all data needed to create and control a separate room
class Room
{
private:
	//XYZ of room
	sf::Vector3<char> coordinates;
	// the hints coordinates that are shown when using column
	sf::Vector3<char> hint;
	//mark of hint, cast (dependance) to see hint and use namely
	dependance hint_type;
	//0 hint is false, 1 hint is true
	bool hint_truth;
	//used for all rooms that will point this room with hints
	//they will produce hint compatible with hint_truth if true
	//if false producing hint will load hint_truth and set loaded to true
	bool hint_truth_loaded;
	//if the room once has been generated(visited) it will set to true, it will stay the same thanks to it
	bool room_initialized;
	//0 this room is not exit room, 1 this is exit room
	bool final_room;
	//floor image
	Visible *background;
	//a special occurance in the room (usually trap)
	Room_Feature *feature;
	//once loaded feature value will generate object when re-entering room
	//randomized 0-9
	//3 for fire trap
	//4 for projectile shooter
	//5 for enemy
	//10 for bonus
	char feature_value;
	//floor type that corresponds to floor image
	char floor_type;
	//when true player acts first in the frame, when false enemy acts first, toggles every frame
	bool alpha;
	//if false that means that feature is dead or deactivated
	bool feature_alive;
	//generates and fits the hint into already loaded room and hint dependencies
	void hint_matching(World<Physical> *mapa, Cube<Room> * cube);
	//for storing data when leaving room
	Room_Feature_Data feature_data;

public:
	Room();
	~Room();
	//constructor that takes coordinates XYZ
	Room(sf::Vector3<char> coordinates);
	sf::Vector3<char> get_coordinates();
	sf::Vector3<char> get_hint();
	dependance get_hint_type();
	bool get_hint_truth();
	void set_hint_truth(bool hint_truth);
	bool get_hint_truth_loaded();
	void set_hint_truth_loaded(bool hint_truth_loaded);
	bool get_room_initialized();
	bool get_final_room();
	Visible *get_background();
	Room_Feature *get_feature();
	char get_feature_value();
	bool get_feature_alive();
	void drop_bonus(World<Physical> *mapa, Sprite_Sheet_Data **graphics, float multiplier);
	char get_floor_type();
	//operation called when leaving the room
	void exit_room(World<Physical> *mapa);
	
	//generate room with hint, features and other values, used once on first enter
	void initialize(World<Physical> *mapa, Cube<Room> * cube, Sprite_Sheet_Data **graphics, float multiplier);
	//main update, updates every object in the room and player
	void update(World<Physical> *mapa);
	
};

