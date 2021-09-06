#pragma once

#include "slime.h"

class slimeSystem {
public:

	vector<slime> vec;
	ofColor sen_col, sli_col;

	float s_ang, s_dis, s_rad;

	vector<slimeSystem*> attractSystems, repelSystems;
	float attractStrength, repelStrength;

	slimeSystem() = default;

	void sense();
	void move();
	void draw(int size);
};
