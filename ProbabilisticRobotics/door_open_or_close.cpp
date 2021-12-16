#include "door_open_or_close.h"

SensorRobot::SensorRobot(float z_open_X_open, float z_closed_X_open,
						 float z_open_X_closed, float z_closed_X_closed) {

	this->sensor_p_z_open_when_X_open = z_open_X_open;
	this->sensor_p_z_closed_when_X_open = z_closed_X_open;
	this->sensor_p_z_open_when_X_closed = z_open_X_closed;
	this->sensor_p_z_closed_when_X_closed = z_closed_X_closed;
}

void SensorRobot::updatePredictedBeliefs() {
	this->pred_bel_X_open = state_p_X_open_U_Xm1_open * bel_X_open
							+ state_p_X_open_U_Xm1_closed * bel_X_closed;

	this->pred_bel_X_closed = state_p_X_closed_U_Xm1_open * bel_X_open
								+ state_p_X_closed_U_Xm1_closed * bel_X_closed;

	updateBeliefs();
}

void SensorRobot::updateBeliefs() {
	this->bel_X_open = sensor_p_z_open_when_X_open * this->pred_bel_X_open;

	this->bel_X_closed = sensor_p_z_open_when_X_closed * this->pred_bel_X_closed;

	normalizer = 1.0 / (this->bel_X_open + this->bel_X_closed);

	this->bel_X_open *= normalizer;
	this->bel_X_closed *= normalizer;
}

void SensorRobot::performAction(int action) {
	if (action == 0) { // do_nothing
		this->state_p_X_open_U_Xm1_open = 1;
		this->state_p_X_closed_U_Xm1_open = 0;
		this->state_p_X_open_U_Xm1_closed = 0;
		this->state_p_X_closed_U_Xm1_closed = 1;
	}

	else if (action == 1) { // push
		this->state_p_X_open_U_Xm1_open = 1;
		this->state_p_X_closed_U_Xm1_open = 0;
		this->state_p_X_open_U_Xm1_closed = this->sensor_p_z_closed_when_X_closed;
		this->state_p_X_closed_U_Xm1_closed = this->sensor_p_z_open_when_X_closed;
	}

	updatePredictedBeliefs();
}

void SensorRobot::showBeliefs() {
	std::cout << "\nbel(X = is_open) = " << this->bel_X_open << "\n"
		<< "bel(X = is_closed) = " << this->bel_X_closed << std::endl;
}