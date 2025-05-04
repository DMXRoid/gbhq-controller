#include <ESP32Servo.h>

class ServoController {
	public:
		ServoController();
		void addServo(int, int);
		void setServoPosition(int, int);
	private:
		Servo servos[3];
};

ServoController* getServoController();
void initServos();