#ifndef ship_h
#define ship_h

#include "flyingObject.h"
#include "configuration.h"

class Ship : public FlyingObject
{
private:
	int angle;	
	bool flames;

public:
	Ship();

	inline int getAngle() const { return angle; }
	void turnLeft();
	void turnRight();
	void thrust();
	void slowDown();
	void draw();

	void setFlames(bool nFlames) { flames = nFlames;  }


	Ship & operator = (const Ship &rhs);
};


#endif /* ship_h */
