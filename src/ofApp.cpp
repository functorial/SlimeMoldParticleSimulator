#include "ofApp.h"

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

		/*
		// Random initial pos and vel
		ofVec2f pos = ofVec2f(ofRandom(0, ofGetWidth()),
			ofRandom(0, ofGetHeight()));
		ofVec2f vel = ofVec2f(ofRandom(-5, 5),
			ofRandom(-5, 5));
		*/

		/*
		// Grid-like initial pos and constant initial vel
		ofVec2f pos = ofVec2f(50 * i, 50 * i);
		ofVec2f vel = ofVec2f(2, -2);
		*/

		// Elliptic initial pos and vel
		float init_rad1 = 50;
		ofVec2f pos = ofVec2f(init_rad1 * cosf(44.0 / 7.0 * float(i) / float(num_slimes1)) + ofGetWidth() / 2, init_rad1 / 2.0 * sinf(44.0 / 7.0 * float(i) / float(num_slimes1)) + ofGetHeight() / 2);
		ofVec2f vel = 3 * ofVec2f(cosf(44.0 / 7.0 * float(i) / float(num_slimes1)), sinf(44.0 / 7.0 * float(i) / float(num_slimes1)));

		slime s = slime(pos, vel, slimes1.s_ang, slimes1.s_dis, slimes1.s_rad);
		slimes1.vec.push_back(s);

	}
	//--------------------------------------------------------------------------------------------------------------------------------------------------

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

		/*
		// Random initial pos and vel
		ofVec2f pos = ofVec2f(ofRandom(0, ofGetWidth()),
							  ofRandom(0, ofGetHeight()));
		ofVec2f vel = ofVec2f(ofRandom(-10, 10),
							  ofRandom(-10, 10));
		*/

		/*
		// Grid-like initial pos and constant initial vel
		ofVec2f pos = ofVec2f(50 * i, 50 * i);
		ofVec2f vel = ofVec2f(2, -2);
		*/

		// Elliptic initial pos and vel
		float init_rad2 = 50;
		ofVec2f pos = 0.5 * ofVec2f(init_rad2 * cosf(44.0 / 7.0 * float(i) / float(num_slimes2)) + ofGetWidth() / 2, init_rad2 / 2.0 * sinf(44.0 / 7.0 * float(i) / float(num_slimes2)) + ofGetHeight() / 2);
		ofVec2f vel = 2 * ofVec2f(cosf(44.0 / 7.0 * float(i) / float(num_slimes2)), 0.5 * sinf(44.0 / 7.0 * float(i) / float(num_slimes2)));

		slime s = slime(pos, vel, slimes2.s_ang, slimes2.s_dis, slimes2.s_rad);
		slimes2.vec.push_back(s);
	}
	//--------------------------------------------------------------------------------------------------------------------------------------------------

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

		/*
		// Random initial pos and vel
		ofVec2f pos = ofVec2f(ofRandom(0, ofGetWidth()),
							  ofRandom(0, ofGetHeight()));
		ofVec2f vel = ofVec2f(ofRandom(-10, 10),
							  ofRandom(-10, 10));
		*/

		/*
		// Grid-like initial pos and constant initial vel
		ofVec2f pos = ofVec2f(50 * i, 50 * i);
		ofVec2f vel = ofVec2f(2, -2);
		*/

		// Elliptic initial pos and vel
		float init_rad3 = 50;
		ofVec2f pos = 1.5 * ofVec2f(init_rad3 * cosf(44.0 / 7.0 * float(i) / float(num_slimes3)) + ofGetWidth() / 2, init_rad3 / 2.0 * sinf(44.0 / 7.0 * float(i) / float(num_slimes3)) + ofGetHeight() / 2);
		ofVec2f vel = ofVec2f(cosf(44.0 / 7.0 * float(i) / float(num_slimes3)), 0.5 * sinf(44.0 / 7.0 * float(i) / float(num_slimes3)));

		slime s = slime(pos, vel, slimes3.s_ang, slimes3.s_dis, slimes3.s_rad);
		slimes3.vec.push_back(s);
	}
	//--------------------------------------------------------------------------------------------------------------------------------------------------

}

//--------------------------------------------------------------
void ofApp::update() {

	slimes1.sense();
	slimes1.move();

	slimes2.sense();
	slimes2.move();

	slimes3.sense();
	slimes3.move();
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
	slimes1.draw(2);
	slimes2.draw(2);
	slimes3.draw(2);
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
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
