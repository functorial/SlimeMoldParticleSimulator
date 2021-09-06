# SlimeMoldParticleSimulator

A slime particle is simulated as a particle with three circular sensors ahead of it. Using the sensors the slime particle can be programmed to rotate towards other slime particles within the sensor radii. The sensor radius, distance, and angle are all parameters which may be modified.

Different slime species may be defined, and may be programmed to interact with one another with a repelling or attracting force. 



To use:
1) Install [OpenFrameworks](https://openframeworks.cc/ja/).
2) (For recording video) Download and unzip [ofxFFmpegRecorder](https://github.com/Furkanzmc/ofxFFmpegRecorder) into the `OpenFrameworks/addons/` folder.
3) Use the OpenFrameworks project generator to generate a project. Make sure to include the ofxFFmpeg addon.
4) (For recording video) Download and unzip [FFmpeg](https://ffmpeg.org/). Put the ffmpeg.exe into the `bin/data/` folder of your project.
5) Add the sensor, slime, slimeSystem, ofApp, and ofMain files here to the project.

Project is based on [this paper](https://uwe-repository.worktribe.com/output/980579) by Jeff Jones. 
