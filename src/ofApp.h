#pragma once

#include "ofMain.h"
#include "ofxFFmpegRecorder.h"
#include "../slimeSystem.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);

	ofxFFmpegRecorder record;
	ofFbo fbo;
	ofPixels pixel;
	bool isRecordingVideo;

	slimeSystem slimes1, slimes2, slimes3;
};