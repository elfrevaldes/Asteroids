#ifndef ship_h
#define ship_h

#include "flyingObject.h"
#include "configuration.h"

class Ship : public FlyingObject
{
private:
	int angle;	
	bool flames;
	int lives;

public:
	Ship();

	inline int getAngle() const { return angle; }
	inline int getLives()const { return lives; }

	void turnLeft();
	void turnRight();
	void thrust();
	void slowDown();
	void draw();

	void setFlames(bool nFlames) { flames = nFlames;  }
	void setLives(int nLives) { lives += nLives; }


	Ship & operator = (const Ship &rhs);
};


#endif /* ship_h */
