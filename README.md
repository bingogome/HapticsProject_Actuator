# HapticsProject_Actuator

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

## Simulation - 2D
![alt text](https://github.com/bingogome/HapticsProject_Actuator/blob/main/image_simulation.png?raw=true)

## Simulation - 3D
TODO