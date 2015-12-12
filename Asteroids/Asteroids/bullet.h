/**********************************************************************
* Description:
* Inputs:
* Outputs:
* Return:
**********************************************************************/

#ifndef BULLET_H
#define BULLET_H

#include "flyingObject.h"
#include "bullet.h"
#include "uiDraw.h"
#include "ship.h"
#include "configuration.h"

class Bullet : public FlyingObject
{
private:
	float angle; // bullet has no angle


public:

	Bullet()
	{
		Point p(200, -200);
		location = p;
	}
	// are we changing the ship?
	Bullet(const Ship& s);

	// For shotgun
	Bullet(Ship& ship, int orentation);

	virtual void draw();
	//void advance(); // defined in FlyingObject
};

// I thought that making this a bullet would be a good
// way to keep everything the same and just add this
// awesome new "bullet"
class SonicBoom : public Bullet
{
private:

public:
	SonicBoom(const Ship &ship);

	void draw();
	
	// Makes it a giant blast that kills everything
	inline void kill() {};
};

#endif 

