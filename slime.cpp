#include "slime.h"

slime::slime(ofVec2f position, ofVec2f velocity, float sensor_angle, float sensor_distance, float sensor_radius) {

	pos = position;
	vel = velocity;
	s_ang = sensor_angle;	// degrees
	s_dis = sensor_distance;
	s_rad = sensor_radius;

	lsensor = sensor(pos + (velocity.normalize() * s_dis).rotate(s_ang), s_rad);
	csensor = sensor(pos + (velocity.normalize() * s_dis), s_rad);
	rsensor = sensor(pos + (velocity.normalize() * s_dis).rotate(-s_ang), s_rad);

}