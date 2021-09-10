#include "ofApp.h"

//--------------------------------------------------------------
void sense_slimes(slimeSystem& system) {

	for (unsigned int i = 0; i < system.vec.size(); i++) {
		slime* s = &system.vec[i];

		// Sense pheremones
		float lsense = 0;
		float csense = 0;
		float rsense = 0;
		for (unsigned int k = 0; k < system.attractSystems.size(); k++) {
			for (unsigned int j = 0; j < (system.attractSystems[k])->vec.size(); j++) {
				if (((system.attractSystems[k])->vec[j].pos - s->lsensor.pos).length() <= s->lsensor.rad) { lsense += 1 * system.attractStrength; }
				if (((system.attractSystems[k])->vec[j].pos - s->csensor.pos).length() <= s->csensor.rad) { csense += 1 * system.attractStrength; }
				if (((system.attractSystems[k])->vec[j].pos - s->rsensor.pos).length() <= s->rsensor.rad) { rsense += 1 * system.attractStrength; }
			}
		}
		for (unsigned int k = 0; k < system.repelSystems.size(); k++) {
			for (unsigned int j = 0; j < (system.repelSystems[k])->vec.size(); j++) {
				if (((system.repelSystems[k])->vec[j].pos - s->lsensor.pos).length() <= s->lsensor.rad) { lsense -= 1 * system.repelStrength; }
				if (((system.repelSystems[k])->vec[j].pos - s->csensor.pos).length() <= s->csensor.rad) { csense -= 1 * system.repelStrength; }
				if (((system.repelSystems[k])->vec[j].pos - s->rsensor.pos).length() <= s->rsensor.rad) { rsense -= 1 * system.repelStrength; }
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
		s->vel.rotate(n * system.s_ang);
		s->lsensor.pos.rotate(n * system.s_ang, s->pos);
		s->csensor.pos.rotate(n * system.s_ang, s->pos);
		s->rsensor.pos.rotate(n * system.s_ang, s->pos);
	}
}

//--------------------------------------------------------------
void move_slimes(slimeSystem& system) {
	for (unsigned int i = 0; i < system.vec.size(); i++) {
		slime* s = &system.vec[i];

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

//--------------------------------------------------------------
void draw_slimes(slimeSystem& system, int size) {
	for (unsigned int i = 0; i < system.vec.size(); i++) {
		ofSetColor(system.sli_col);
		ofDrawCircle(system.vec[i].pos, size);
		ofSetColor(system.sen_col);
		ofDrawCircle(system.vec[i].lsensor.pos, system.vec[i].lsensor.rad);
		ofDrawCircle(system.vec[i].csensor.pos, system.vec[i].csensor.rad);
		ofDrawCircle(system.vec[i].rsensor.pos, system.vec[i].rsensor.rad);
	}
}

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);

	// Set up video recorder
	fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGB);
	record.setup(true, false);
	record.setWidth(ofGetWidth());
	record.setHeight(ofGetHeight());
	record.setFFmpegPath(ofToDataPath("ffmpeg.exe"));
	record.setFps(60);
	record.setOutputPath(ofToDataPath("slime_" + ofToString(ofGetSystemTimeMillis()) + ".mp4", true));
	record.startCustomRecord();
	isRecordingVideo = true;


	// Set up a slime system RED
	//--------------------------------------------------------------------------------------------------------------------------------------------------
	int num_slimes1 = 100;
	slimes1.s_ang = 50;		// degrees
	slimes1.s_dis = 20;		// pixels
	slimes1.s_rad = 15;		// pixels
	slimes1.sen_col = ofColor(255, 50, 50, 5);	// RGB + transparency
	slimes1.sli_col = ofColor(255, 100, 100);


	slimes1.attractSystems = vector<slimeSystem*>{ &slimes1 };
	slimes1.attractStrength = 1.0;
	slimes1.repelSystems = vector<slimeSystem*>{ &slimes2, &slimes3 };
	slimes1.repelStrength = -0.5;

	for (int i = 0; i < num_slimes1; ++i) {

		// Random initial pos and vel
		ofVec2f pos = ofVec2f(ofRandom(0, ofGetWidth()),
							  ofRandom(0, ofGetHeight()));
		ofVec2f vel = ofVec2f(ofRandom(-5, 5),
							  ofRandom(-5, 5));

		/*
		// Grid-like initial pos and constant initial vel
		ofVec2f pos = ofVec2f(50 * i, 50 * i);
		ofVec2f vel = ofVec2f(2, -2);
		*/

		/*
		// Elliptic initial pos and vel
		float init_rad1 = 50;
		ofVec2f pos = ofVec2f(init_rad1 * cosf(44.0 / 7.0 * float(i) / float(num_slimes1)) + ofGetWidth() / 2, init_rad1 / 2.0 * sinf(44.0 / 7.0 * float(i) / float(num_slimes1)) + ofGetHeight() / 2);
		ofVec2f vel = 3 * ofVec2f(cosf(44.0 / 7.0 * float(i) / float(num_slimes1)), sinf(44.0 / 7.0 * float(i) / float(num_slimes1)));
		*/

		slime s = slime(pos, vel, slimes1.s_ang, slimes1.s_dis, slimes1.s_rad);
		slimes1.vec.push_back(s);

	}

	// Set up a slime system BLUE
	//--------------------------------------------------------------------------------------------------------------------------------------------------
	int num_slimes2 = 200;
	slimes2.s_ang = 40;		// degrees
	slimes2.s_dis = 30;		// pixels
	slimes2.s_rad = 15;		// pixels
	slimes2.sen_col = ofColor(50, 50, 255, 5);	// RGB + transparency
	slimes2.sli_col = ofColor(100, 100, 255);
	slimes2.attractSystems = vector<slimeSystem*>{ &slimes2 };
	slimes2.attractStrength = 1.0;
	slimes2.repelSystems = vector<slimeSystem*>{ &slimes1, &slimes3 };
	slimes2.repelStrength = 3.0;

	for (int i = 0; i < num_slimes2; ++i) {

		// Random initial pos and vel
		ofVec2f pos = ofVec2f(ofRandom(0, ofGetWidth()),
							  ofRandom(0, ofGetHeight()));
		ofVec2f vel = ofVec2f(ofRandom(-3.5, 3.5),
							  ofRandom(-3.5, 3.5));

		/*
		// Grid-like initial pos and constant initial vel
		ofVec2f pos = ofVec2f(50 * i, 50 * i);
		ofVec2f vel = ofVec2f(2, -2);
		*/

		/*
		// Elliptic initial pos and vel
		float init_rad2 = 50;
		ofVec2f pos = 0.5 * ofVec2f(init_rad2 * cosf(44.0 / 7.0 * float(i) / float(num_slimes2)) + ofGetWidth() / 2, init_rad2 / 2.0 * sinf(44.0 / 7.0 * float(i) / float(num_slimes2)) + ofGetHeight() / 2);
		ofVec2f vel = 2 * ofVec2f(cosf(44.0 / 7.0 * float(i) / float(num_slimes2)), 0.5 * sinf(44.0 / 7.0 * float(i) / float(num_slimes2)));
		*/

		slime s = slime(pos, vel, slimes2.s_ang, slimes2.s_dis, slimes2.s_rad);
		slimes2.vec.push_back(s);
	}

	// Set up a slime system GREEN
	//--------------------------------------------------------------------------------------------------------------------------------------------------
	int num_slimes3 = 200;
	slimes3.s_ang = 40;	// degrees
	slimes3.s_dis = 20;	// pixels
	slimes3.s_rad = 15;	// pixels
	slimes3.sen_col = ofColor(50, 255, 50, 2);	// RGB + transparency
	slimes3.sli_col = ofColor(100, 255, 100);
	slimes3.attractSystems = vector<slimeSystem*>{ &slimes3 };
	slimes3.attractStrength = 1.0;
	slimes3.repelSystems = vector<slimeSystem*>{ &slimes2, &slimes1 };
	slimes3.repelStrength = 0.3;

	for (int i = 0; i < num_slimes2; ++i) {

		// Random initial pos and vel
		ofVec2f pos = ofVec2f(ofRandom(0, ofGetWidth()),
							  ofRandom(0, ofGetHeight()));
		ofVec2f vel = ofVec2f(ofRandom(-2, 2),
							  ofRandom(-2, 2));

		/*
		// Grid-like initial pos and constant initial vel
		ofVec2f pos = ofVec2f(50 * i, 50 * i);
		ofVec2f vel = ofVec2f(2, -2);
		*/

		/*
		// Elliptic initial pos and vel
		float init_rad3 = 50;
		ofVec2f pos = 1.5 * ofVec2f(init_rad3 * cosf(44.0 / 7.0 * float(i) / float(num_slimes3)) + ofGetWidth() / 2, init_rad3 / 2.0 * sinf(44.0 / 7.0 * float(i) / float(num_slimes3)) + ofGetHeight() / 2);
		ofVec2f vel = ofVec2f(cosf(44.0 / 7.0 * float(i) / float(num_slimes3)), 0.5 * sinf(44.0 / 7.0 * float(i) / float(num_slimes3)));
		*/

		slime s = slime(pos, vel, slimes3.s_ang, slimes3.s_dis, slimes3.s_rad);
		slimes3.vec.push_back(s);
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	sense_slimes(slimes1);
	move_slimes(slimes1);

	sense_slimes(slimes2);
	move_slimes(slimes2);

	sense_slimes(slimes3);
	move_slimes(slimes3);
}

//--------------------------------------------------------------
void ofApp::draw() {
	if (record.isRecording()) {
		if (isRecordingVideo) {
			fbo.readToPixels(pixel);
			if (pixel.getHeight() > 0 && pixel.getWidth() > 0) {
				record.addFrame(pixel);
			}
		}
	}

	fbo.begin();
	ofClear(255, 255, 255, 0);
	ofBackground(0, 0, 0);
	draw_slimes(slimes1, 2);
	draw_slimes(slimes2, 2);
	draw_slimes(slimes3, 2);
	fbo.end();

	fbo.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key) {
	case 'r':
		isRecordingVideo = !isRecordingVideo;
		if (record.isRecording()) {
			record.stop();
		}
		else {
			record.setOutputPath(ofToDataPath("slime_" + ofToString(ofGetSystemTimeMillis()) + ".mp4", true));
			record.startCustomRecord();
		}
		break;

	default:
		break;
	}
}

//--------------------------------------------------------------