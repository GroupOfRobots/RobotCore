#ifndef _CONTROLLER_INCLUDED_
#define _CONTROLLER_INCLUDED_

#include <ctime>
#include <ratio>
#include <chrono>
#include <cstdio>

#define MAX_THROTTLE 580
#define MAX_STEERING 150
#define MAX_ANGLE 14
#define MAX_OUTPUT 900

#define KP 50
#define KD 23
#define KP_THROTTLE 0.009
#define KI_THROTTLE 0.1

#define SPEED_MAX_ERROR 500
#define SPEED_MAX_INTEGRAL 5000

class Controller {
	private:
		std::chrono::high_resolution_clock::time_point timePointPrevious;
		std::chrono::high_resolution_clock::time_point timePoint;

		float angle;
		float anglePrevious;
		float anglePIDKp;
		float anglePIDKi;
		float anglePIDKd;
		float anglePIDIntegral;
		float anglePIDError;

		float speed;
		float speedPrevious;
		float speedFiltered;
		float speedPIDKp;
		float speedPIDKi;
		float speedPIDKd;
		float speedPIDIntegral;
		float speedPIDError;

		// PI controller implementation (Proportional, integral). DT is in miliseconds
		float speedControl(float value, float setPoint, float dt);
		// PD controller implementation(Proportional, derivative). DT is in miliseconds
		float stabilityControl(float value, float setPoint, float dt);
	public:
		Controller();
		~Controller();
		void setSpeedPID(float kp, float ki, float kd);
		void setStabilityPID(float kp, float ki, float kd);
		void calculateSpeed(float angle, float speedLeft, float speedRight, int steering, int throttle, float &speedLeftNew, float &speedRightNew);
		float timerValue();
		void restartTimer();
};

#endif