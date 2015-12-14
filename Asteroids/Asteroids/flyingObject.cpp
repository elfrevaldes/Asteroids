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
//#include "configuration.h"



/**********************************************************************
* We are checking if it is on the screen (not if it is outside)
**********************************************************************/
bool FlyingObject::isOnScreen()
{
	if (location.getX() < location.getXMax() &&   // ___ ___
		location.getY() < location.getYMax() &&   //|   | * |
		location.getX() > location.getXMin() &&   //|---+---|
		location.getY() > location.getYMin())     //|*__|___|
		return true;

	// not in screen
	return false;
}

/**********************************************************************
*
**********************************************************************/
void FlyingObject::advance()
{
	location.addX(velocity.getDx());
	location.addY(velocity.getDy());
}

void FlyingObject::survivalAsteroidAdvance(Point shipLocation, Point asteroidLocation)
{
	////////////// I need to work on this, but it's late and I'm tired
}

/**********************************************************************
*
**********************************************************************/
void FlyingObject::setVelocity(float nDx, float nDy)
{
	velocity.setDx(nDx);
	velocity.setDy(nDy);
}
