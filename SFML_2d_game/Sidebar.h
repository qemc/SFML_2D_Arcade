#pragma once

#include "Plane.h"



class Sidebar : public Text {

private:
	Font font;

public:

	Sidebar();
	void update(Plane& plane);



};
