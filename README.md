# Arduino controlled car with hand gestures from OpenCV
 Using a pre-built [Arduino kit](https://www.ebay.co.uk/itm/Smart-Car-Smart-Robot-Car-Chassis-Kit-Tracking-Motor-2WD-Ultrasonic-Arduino-MCU/274068571943?ssPageName=STRK%3AMEBIDX%3AIT&_trksid=p2057872.m2749.l2649d) I connected the parts (including some additionaly bought) and wrote Arduino C code using the Arduino IDE to move the car whilst avoiding any objects in its path.

# Installation instructions
To be able to run the program you need the Arduino car to be connected to the device (get the USB address to perform the communication from ls /dev/tty.* - similar to /dev/tty.usbserial-14120). 

Make sure you have the following libraries and packages:

	1. Python 2.7.16
    2. OpenCV 4.5.4
    3. mediapipe 0.8.9


# Libraries, hardware, etc.
Here is a list of some of the code libraries that I used:

* [Servo.h](https://www.arduino.cc/reference/en/libraries/servo/)

The hardware:

* [The full kit](https://www.ebay.co.uk/itm/Smart-Car-Smart-Robot-Car-Chassis-Kit-Tracking-Motor-2WD-Ultrasonic-Arduino-MCU/274068571943?ssPageName=STRK%3AMEBIDX%3AIT&_trksid=p2057872.m2749.l2649)

	**That includes:**
	1. 2 x DC Motors
	2. 1 x Acrylic Robot Chasis
	3. 2 x 2.51” Rubber Wheels
	4. 1 x AA Battery Holder

	**Main sensors:**
	1. 1 x HC-SR04 Ultrasonic Sensor
	2. 1 x Servo Motor (SG90)
	3. 1 x Arduino Uno
	4. 1 x L298N Dual H-Bridge Motor Driver 
	5. 1 x Arduino Sensor Shield v.5

# Roadmap and project status
Some planned work for the future includes:

* improving the power suply distribution from the power source (4 x AA batteries) to the Sensor Shield v.5
* fixing the Bluetooth Serial Wireless Module
