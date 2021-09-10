#pragma once

#include "slime.h"

struct slimeSystem {
	slimeSystem(vector<slime> c_vec, ofColor c_sen_col, ofColor c_sli_col, float c_s_ang, float c_s_dis, float c_s_rad, vector<slimeSystem*> c_attractSystems, vector<slimeSystem*> c_repelSystems, float c_attractStrength, float c_repelStrength);
	slimeSystem() = default;

	vector<slime> vec;
	ofColor sen_col, sli_col;

	float s_ang, s_dis, s_rad;

	vector<slimeSystem*> attractSystems, repelSystems;
	float attractStrength, repelStrength;

};
