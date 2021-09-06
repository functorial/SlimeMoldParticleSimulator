#pragma once

#include "ofMain.h"

class sensor {
public:
	ofVec2f pos;
	float rad;

	sensor(ofVec2f position, float radius);
	sensor() = default;
};