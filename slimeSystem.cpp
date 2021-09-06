#include "slimeSystem.h"

void slimeSystem::sense() {

	for (unsigned int i = 0; i < vec.size(); i++) {
		slime* s = &vec[i];

		// Sense pheremones
		float lsense = 0;
		float csense = 0;
		float rsense = 0;
		for (unsigned int k = 0; k < attractSystems.size(); k++) {
			for (unsigned int j = 0; j < (attractSystems[k])->vec.size(); j++) {
				if (((attractSystems[k])->vec[j].pos - s->lsensor.pos).length() <= s->lsensor.rad) { lsense += 1 * attractStrength; }
				if (((attractSystems[k])->vec[j].pos - s->csensor.pos).length() <= s->csensor.rad) { csense += 1 * attractStrength; }
				if (((attractSystems[k])->vec[j].pos - s->rsensor.pos).length() <= s->rsensor.rad) { rsense += 1 * attractStrength; }
			}
		}
		for (unsigned int k = 0; k < repelSystems.size(); k++) {
			for (unsigned int j = 0; j < (repelSystems[k])->vec.size(); j++) {
				if (((repelSystems[k])->vec[j].pos - s->lsensor.pos).length() <= s->lsensor.rad) { lsense -= 1 * repelStrength; }
				if (((repelSystems[k])->vec[j].pos - s->csensor.pos).length() <= s->csensor.rad) { csense -= 1 * repelStrength; }
				if (((repelSystems[k])->vec[j].pos - s->rsensor.pos).length() <= s->rsensor.rad) { rsense -= 1 * repelStrength; }
			}
		}

		// Rotate slime based on pheremone readings
		// Case1: Turn left
		int n;
		if (lsense > csense && csense >= rsense) {
			n = 1;
		}
		// Case2: Turn right
		else if (lsense <= csense && csense < rsense) {
			n = -1;
		}
		/*
		// Case3: Turn left or right randomly
		else if (lsense > csense && csense < rsense) {
			n = (rand() % 2) * 2 - 1;	// -1 or 1
		}
		*/
		// Else: Continue in same direction
		else {
			n = 0;
		}
		s->vel.rotate(n * s_ang);
		s->lsensor.pos.rotate(n * s_ang, s->pos);
		s->csensor.pos.rotate(n * s_ang, s->pos);
		s->rsensor.pos.rotate(n * s_ang, s->pos);
	}
}

void slimeSystem::move() {
	for (unsigned int i = 0; i < vec.size(); i++) {
		slime* s = &vec[i];

		// Move particle
		s->pos += s->vel;
		s->lsensor.pos += s->vel;
		s->csensor.pos += s->vel;
		s->rsensor.pos += s->vel;

		// Bounce off sides of window by angle of incidence 
		if (s->pos.x < 0) {
			s->pos.x *= -1;
			s->vel.x *= -1;
		}
		else if (s->pos.x >= ofGetWidth()) {
			s->pos.x -= 2 * (s->pos.x - ofGetWidth());
			s->vel.x *= -1;
		}
		if (s->pos.y < 0) {
			s->pos.y *= -1;
			s->vel.y *= -1;
		}
		else if (s->pos.y >= ofGetHeight()) {
			s->pos.y -= 2 * (s->pos.y - ofGetHeight());
			s->vel.y *= -1;
		}

		s->lsensor.pos = s->pos + (s->vel.getNormalized() * s->s_dis).rotate(s->s_ang);
		s->csensor.pos = s->pos + (s->vel.getNormalized() * s->s_dis);
		s->rsensor.pos = s->pos + (s->vel.getNormalized() * s->s_dis).rotate(-s->s_ang);

	}
}

void slimeSystem::draw(int size) {
	for (unsigned int i = 0; i < vec.size(); i++) {
		ofSetColor(sli_col);
		ofDrawCircle(vec[i].pos, size);
		ofSetColor(sen_col);
		ofDrawCircle(vec[i].lsensor.pos, vec[i].lsensor.rad);
		ofDrawCircle(vec[i].csensor.pos, vec[i].csensor.rad);
		ofDrawCircle(vec[i].rsensor.pos, vec[i].rsensor.rad);
	}
}