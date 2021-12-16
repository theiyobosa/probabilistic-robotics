#include "door_open_or_close.h"

int main() {
	SensorRobot robot = SensorRobot(0.6, 0.4, 0.2, 0.8);

	// first step
	robot.performAction(0);

	robot.showBeliefs();

	// second step
	robot.performAction(1);

	robot.showBeliefs();
}