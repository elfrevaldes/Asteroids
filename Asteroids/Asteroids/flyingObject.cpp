/***********************************************************************
* Source File:
*    Move
* Author:
*    Logan Carpenter
* Summary:
*
************************************************************************/

#include <iostream>
#include "flyingObject.h"
//#include "constants.h"

// my constants for error checking
const int UPPER_X_LIMIT = 200;
const int LOWER_X_LIMIT = -200;
const int UPPER_Y_LIMIT = 200;
const int LOWER_Y_LIMIT = -200;

void FlyingObject::kill()
{
}

/**********************************************************************
*
**********************************************************************/
void FlyingObject::advance()
{
	location.addX(velocity.getDx());
	location.addY(velocity.getDy());


}

/**********************************************************************
*
**********************************************************************/
void FlyingObject::setVelocity(float nDx, float nDy)
{
	velocity.setDx(nDx);
	velocity.setDy(nDy);
}

// Setter for the radius (they aren't using radius)
//void FlyingObject::setRadius(int radius)
//{
//	this->radius = radius;
//}

// Checks to see if the object is within the screen bounds
void FlyingObject::collide()
{
	// Basically if the point goes off the screen
	if (location.getX() >= UPPER_X_LIMIT // X too far right
		|| location.getX() <= LOWER_X_LIMIT // X too far left
		|| location.getY() >= UPPER_Y_LIMIT // Y too high
		|| location.getY() <= LOWER_Y_LIMIT) // Y too low
	{
		alive = false; // Kill b/c hit something
	}
}