# SlimeMoldParticleSimulator

A slime particle is simulated as a particle with three circular sensors ahead of it. Using the sensors the slime particle can be programmed to rotate towards other slime particles within the sensor radii. The sensor radius, distance, and angle are all parameters which may be modified.

Model is based on [this paper](https://uwe-repository.worktribe.com/output/980579) by Jeff Jones, although some slight modifications are present. 

# Example: 3 species system
Different slime species may be defined, and may be programmed to interact with one another with a repelling or attracting force. 
* GREEN: 200 particles, slow speed, strongly attracted to itself, mildly repelled by others.
* RED: 100 particles, fast speed, wide sensor angle, strongly attracted to itself, mildly attracted to others.
* BLUE: 200 particles, far sensor distance, mildly attracted to itself, strongly repelled by others.

The glowing effect seen in the GIFS below are the sensors drawn with low transparency. 

## Random Initial Position and Velocity
Video recording is broken into 2 GIFs at 20 frames per second.
<p align="center">
    <img src="example11.gif"/>
    <img src="example12.gif"/>
</p>

## Elliptic Initial Position and Velocity
Video recording is broken into 3 GIFs at 20 frames per second.
<p align="center">
    <img src="example21.gif"/>
    <img src="example22.gif"/>
    <img src="example23.gif"/>
</p>

## To use:

1) Install [OpenFrameworks](https://openframeworks.cc/ja/).
2) (For recording video) Download and unzip [ofxFFmpegRecorder](https://github.com/Furkanzmc/ofxFFmpegRecorder) into the `OpenFrameworks/addons/` folder.
3) Clone this project into your `Openframeworks/apps/myApps/` folder and run.

By default, the simulation will be recorded into the `bin/data/` folder. You can stop/start recording by pressing `r` during the simulation. 
