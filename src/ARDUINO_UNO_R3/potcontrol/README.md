# DYNAMIC MANUAL CONTROL WITH POTENTIOMETERS

## DESCRIPTION

This program is designed to test the conversion of input values into degrees for a servo.

It will take the input range from an analog pin and then map them to a degree range from 0 to 180.

A potentiometer (variable resistor) will be used to direct input values into the analog pin, which is converted to a degree according to the mapped range.

This degree will then be sent to a servo to control its rotation position.

This process will repeat for as long as the test conditions and program are active.

## PROGRAM STEPS

### INPUT
`analog value`


### PROCESS

1. Set up a potentiometer to control analog input.
2. Map analog input values to a degree range from 0 to 180.
3. Transmit converted degree values to servo control.
4. Run tests for servo control:
  - Calibration test
  - Manual control test


### OUTPUT
`servo movement`

## PRIMARY CONCEPTS

1. Analog values will be converted to digital values.
2. Analog input pins are required for potentiometer.
3. Digital PWM pins (marked with a ~) are required for servo control. 
4. Analog range: 0-1023 (10-bit or 2^10)
5. Wrapper functions are needed for complex processing of nested functions in the Unity Testing Framework.
