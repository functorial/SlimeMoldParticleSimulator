#pragma once

#include "ofMain.h"

struct sensor {
	sensor(ofVec2f position, float radius);
	sensor() = default;

	ofVec2f pos;
	float rad;

};