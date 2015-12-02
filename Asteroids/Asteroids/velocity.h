/***********************************************************************
* Header File:
*    Velocity:
* Author:
*    Logan Carpenter
* Summary:
*
************************************************************************/


#ifndef VELOCITY_H
#define VELOCITY_H

#include <iostream>
#include "point.h"

/*********************************************
* Velocity
*
*********************************************/
class Velocity
{
private:
	float dx;
	float dy;

public:

	//static float STARTING_DX;
	//static float STARTING_DY;

	/**********************************************************************
	* Constructors
	**********************************************************************/
	Velocity()
	{
		dx = 0;
		dy = 0;
	}

	Velocity(float nDx, float nDy)
	{
		dx = nDx;
		dy = nDy;
	}

	/**********************************************************************
	* Getters
	**********************************************************************/
	float getDx() { return dx; }
	float getDy() { return dy; }

	/**********************************************************************
	* Setters
	**********************************************************************/
	void setDx(float nDx) { dx = nDx; }
	void setDy(float nDy) { dy = nDy; }

	// Changed these to void b/c they don't need to return anything
	void addOntoDx(float nDx) { dx += nDx; }
	void addOntoDy(float nDy) { dy += nDy; }

};

#endif // VELOCITY_H
