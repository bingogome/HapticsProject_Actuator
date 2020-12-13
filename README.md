# HapticsProject_Actuator

## Modes
1. MODE_SAME: Under this mode, the actuators vibrate at the same frequency and amplitude.
2. MODE_CLOCKWISE: Under this mode, the actuators vibrate in the clockwise direction.
3. MODE_CCLKWISE: Under this mode, the actuators vibrate in the counter-clockwise direction.
4. MODE_PLANARDIRECTION: Under this mode, the actuators roll toward a user-specified (automatic set if certain sensors were available) direction in 2D space.
5. MODE_SPATIALDIRECTION: Under this mode, the actuators roll toward a user-specified (automatic set if certain sensors were available) direction in 3D space.

## Parameters
1. freqLevel: 1~5, vibration frequency = 1/(0.01*freqLevel)
2. ampLevel: 0.0~1.0, vibration amplitude
3. rollLevel: 1~5, rolling speed
4. motorPinDir: planar direction