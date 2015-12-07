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
void FlyingObject::setVelocity(float nDx, float nDy)
{
	velocity.setDx(nDx);
	velocity.setDy(nDy);
}
