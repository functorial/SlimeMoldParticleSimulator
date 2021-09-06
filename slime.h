#pragma once

#include "ofMain.h"
#include "sensor.h"

class slime {
public:

	slime(ofVec2f position, ofVec2f velocity, float sensor_angle, float sensor_distance, float sensor_radius);
	slime() = default;

	float s_ang, s_dis, s_rad;
	ofVec2f pos, vel;
	sensor lsensor, csensor, rsensor;
};