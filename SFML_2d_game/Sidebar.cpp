#include "Sidebar.h"
#include "Plane.h"

Sidebar::Sidebar() {

	font.loadFromFile("ff.ttf");
	setFont(font);
	setPosition(710, 25);
	setCharacterSize(20);

}

void Sidebar::update(Plane& plane) {

	string enm_lvl;

	if (plane.enemy_lvl > 2) {
		enm_lvl = "BOSS";
	}
	else {
		enm_lvl = to_string(plane.enemy_lvl);
	}


	setString("BEACH DEFENCE \n \n POINTS:  " + to_string(plane.player_points) + 
		"\n \n ENEMY LEVEL:  " + enm_lvl);

	

}




