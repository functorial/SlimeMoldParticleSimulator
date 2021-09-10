#include "slimeSystem.h"

slimeSystem::slimeSystem(vector<slime> c_vec, ofColor c_sen_col, ofColor c_sli_col, float c_s_ang, float c_s_dis, float c_s_rad, vector<slimeSystem*> c_attractSystems, vector<slimeSystem*> c_repelSystems, float c_attractStrength, float c_repelStrength)
{
	vec = c_vec;
	sen_col = c_sen_col;
	sli_col = c_sli_col;
	s_ang = c_s_ang;
	s_dis = c_s_dis;
	s_rad = c_s_rad;
	attractSystems = c_attractSystems;
	repelSystems = c_repelSystems;
	attractStrength = c_attractStrength;
	repelStrength = c_repelStrength;
}