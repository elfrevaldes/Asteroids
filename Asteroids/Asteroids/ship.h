#ifndef ship_h
#define ship_h

#include "flyingObject.h"

#define SHIP_SIZE 10
#define ROTATE_AMOUNT 6
#define THRUST_AMOUNT 0.5

#define R_ANGLE ((3.1415 / 180) * angle)


class Ship : public FlyingObject
{
private:
	int angle;
	
public:
	Ship() : FlyingObject() { angle = 90; size = SHIP_SIZE; }
	void turnLeft();
	void turnRight();
	void thrust();

	void draw();
};


#endif /* ship_h */
