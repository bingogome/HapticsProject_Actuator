# HapticsProject_Actuator

## Directories
1. /HapticProject: Integrated audio frequency recognition and actuator module. It is separated from the /HapticProject_Actuator and /HapticProject_Actuator_Simulation. Please see /Media/videos/integrated_demo for a demo video. 

External libraries required: 
 *  arduinoFFT
 *  AdafruitBusIO
 *  Adafruit VEML 6075
 *  Use Sketch -> include library -> manage libraries
 *  Search for the libraries and install them

2. /HapticProject_Actuator and /HapticProject_Actuator_Simulation: the vanilla version of the actuator driver. The following sections Environments, Modes, Parameters, Simulation is intended for this vanilla version, but not fot the /HapticProject integrated version
3. /Media: images, animations, and videos.

## Environments
1. ENABLE_SIMULATION: Enable Processing graphical simulation
2. ENABLE_MOTORS: Enable motor signal output from Arduino Uno

## Modes
1. MODE_SAME: Under this mode, the actuators vibrate at the same frequency and amplitude.
2. MODE_CLOCKWISE: Under this mode, the actuators vibrate in the clockwise direction.
3. MODE_CCLKWISE: Under this mode, the actuators vibrate in the counter-clockwise direction.
4. MODE_PLANARDIRECTION: Under this mode, the actuators roll toward a user-specified (automatic set if certain sensors were available) direction in 2D space.
5. MODE_SPATIALDIRECTION: Under this mode, the actuators roll toward a user-specified (automatic set if certain sensors were available) direction in 3D space. - TODO

## Parameters
1. freqLevel: 1~5, vibration frequency = 1/(0.01*freqLevel)
2. ampLevel: 0.0~1.0, vibration amplitude
3. rollLevel: 1~5, rolling speed
4. motorPinDir: planar direction
5. gyroscopeVector: current body pose - TODO
6. motorPinDir3D: 3D spatial direction - TODO

## Simulation - 2D Planar direction
1. For more simulation please see in the Media folder.
2. In the image, the actuators roll toward motor 5, representing forward direction.
![alt text](https://github.com/bingogome/HapticsProject_Actuator/blob/main/media/gif/gif_simulation.gif?raw=true)
![alt text](https://github.com/bingogome/HapticsProject_Actuator/blob/main/media/images/planar_direction.png)

## Simulation - 3D
TODO