#ifndef ship_h
#define ship_h

#include "flyingObject.h"

#define SHIP_SIZE 10
#define ROTATE_AMOUNT 6
#define THRUST_AMOUNT 0.5

#define deg2rad(value) ((3.1415 / 180) * (value))


class Ship : public FlyingObject
{
private:
	int angle;
	
public:
	Ship() : FlyingObject() { angle = 90; size = SHIP_SIZE; }
	void turnLeft();
	void turnRight();
	void thrust();

	int getAngle() { return angle; }

	void draw();
};


#endif /* ship_h */
