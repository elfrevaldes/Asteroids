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

/**********************************************************************
*
**********************************************************************/
void FlyingObject::survivalAsteroidAdvance(Point &shipLocation, Point &asteroidLocation)
{
	float asteroidGravity = .1;

	float xDiff = shipLocation.getX() - asteroidLocation.getX();
	float yDiff = shipLocation.getY() - asteroidLocation.getY();

	float magnitude = sqrt(pow(xDiff, 2) + pow(yDiff, 2));

	Velocity tempVel(xDiff, yDiff);
	velocity.addOntoDx(asteroidGravity * (xDiff / magnitude));
	velocity.addOntoDy(asteroidGravity * (yDiff / magnitude));	
	
	/*if (shipLocation.getX() > asteroidLocation.getX())
		asteroidLocation.addX(3);
	else
		asteroidLocation.addX(-3);

	if (shipLocation.getY() > asteroidLocation.getY())
		asteroidLocation.addY(3);
	else
		asteroidLocation.addY(-3);	
*/
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
