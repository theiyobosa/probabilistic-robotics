#ifndef SENSORROBOT_H
#define SENSORROBOT_H

#include <iostream>

/////////////////////////////////////////////////////////////////////////////
//////////////////////// CODE FOR EXAMPLE [2.4.2] ///////////////////////////
/////////////////////////////////////////////////////////////////////////////

//This robot will have STATE DATA (X), MEASUREMENT DATA (z), and CONTROL DATA (u) all at time t
//It will also have a belief of its state variables (X) at any time t
class SensorRobot {

private:
	
	// Beliefs
	float bel_X_open = 0.5; // bel(X = open)
	float bel_X_closed = 0.5; // bel(X = closed)

	// Predicted beliefs
	float pred_bel_X_open;
	float pred_bel_X_closed;

	// Sensor data noisiness
	float sensor_p_z_open_when_X_open;
	float sensor_p_z_closed_when_X_open;
	float sensor_p_z_open_when_X_closed;
	float sensor_p_z_closed_when_X_closed;

	// State probabilities
	float state_p_X_open_U_Xm1_open; // p(Xt = is_open | Ut, X[t-1] = is_open)
	float state_p_X_closed_U_Xm1_open; // p(Xt = is_closed | Ut, X[t-1] = is_open)
	float state_p_X_open_U_Xm1_closed; // p(Xt = is_open | Ut, X[t-1] = is_closed)
	float state_p_X_closed_U_Xm1_closed; // p(Xt = is_closed | Ut, X[t-1] = is_closed)

	float normalizer;

	void updatePredictedBeliefs();

	void updateBeliefs();

public:
	SensorRobot(float z_open_X_open, float z_closed_X_open,
				float z_open_X_closed, float z_closed_X_closed);

	// do_nothing = 0, push = 1
	void performAction(int action);

	void showBeliefs();
};

#endif