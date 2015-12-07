/***********************************************************************
* Source File:
*    Bird
* Author:
*    Logan Carpenter
* Summary:     qweqweq
*.
************************************************************************/


#include <math.h>

#include "bullet.h"
//#include "constants.h"

Bullet::Bullet(const Ship &s) : FlyingObject()
{
	alive = BULLET_LIFE;
	Velocity initialVelicity(s.getAngle(), BULLET_SPEED);
	// setting the velocity of the bullet to plus the speed of the ship
	velocity = initialVelicity + s.getVelocity();
	location = s.getLocation();
	location.setWrap(true); // for testing purposes
}


/**********************************************************************
*
**********************************************************************/
void Bullet::draw()
{
	if (alive)
		drawDot(Point(location.getX(), location.getY()));
	if(alive > 0)
	--alive;	
}


