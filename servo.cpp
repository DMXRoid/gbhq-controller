#include <ESP32Servo.h>
#include "servo.h"
#include "util.h"

ServoController* servoController;
Servo s;
ServoController::ServoController() {

}

void ServoController::addServo(int index, int pin) {
	servos[index] = Servo();
	servos[index].setPeriodHertz(50);
	servos[index].attach(pin, 500, 2400);
}

void ServoController::setServoPosition(int index, int position) {
	String l = "Setting servo ";
	l += index;
	l += " poaition to ";
	l += position;
	log(l);
	log(servos[index].read());
	servos[index].write(position);
	
}
ServoController* getServoController() {
	return servoController;
}

void initServos() {
	log("servo setup start");
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);

	servoController = new ServoController();
	getServoController()->addServo(0, 33);	
	log("Servo Setup Complete");
}