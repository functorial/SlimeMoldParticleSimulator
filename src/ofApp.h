#pragma once

#include "ofMain.h"
#include "ofxFFmpegRecorder.h"
#include "../slimeSystem.h"
#include <stdint.h>

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);

	void sense_slimes(slimeSystem &slimes);
	void move_slimes(slimeSystem &slimes);
	void draw_slimes(slimeSystem &slimes, uint8_t size);

	ofxFFmpegRecorder record;
	ofFbo fbo;
	ofPixels pixel;
	bool isRecordingVideo;

	slimeSystem slimes1, slimes2, slimes3;


};