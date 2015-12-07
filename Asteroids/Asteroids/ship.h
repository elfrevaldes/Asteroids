#ifndef ship_h
#define ship_h

#include "flyingObject.h"

#define SHIP_SIZE 10
#define ROTATE_AMOUNT 6
#define THRUST_AMOUNT 0.5
#define MAX_SHIP_SPEED 2.0
#define deg2rad(value) ((3.1415 / 180) * (value))
#define ABS(value) ((value > 0)? value : value * -1)

class Ship : public FlyingObject
{
private:
	int angle;	
public:
	Ship() : FlyingObject() { angle = 90; size = SHIP_SIZE; location.setWrap(true); }
	inline int getAngle() const { return angle; }
	void turnLeft();
	void turnRight();
	void thrust();
	void slowDown();
	void draw();

	Ship & operator = (const Ship &rhs);
};


#endif /* ship_h */
