# Experiments

## KW_flap4.ino

Testing four servos on a Kniwwelino, driving via ServoEasing. Works acceptably with 3 servos, but the fourth is jittercity.

## KW_flap4standard.ino

As `KW_flap4.ino`, but using standard Servo library to check the interrupt handling in ServoEasing doesn't affect servo performance detrimentally. Conclusion: it doesn't, and we're no better-off using Servo.

