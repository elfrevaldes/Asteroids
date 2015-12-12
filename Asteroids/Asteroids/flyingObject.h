/***********************************************************************
* Source File:
*    Move
* Author:
*    Logan Carpenter
* Summary:
*
************************************************************************/


#ifndef FLYINGOBJECT_H
#define FLYINGOBJECT_H

#include <iostream>
#include "velocity.h"
#include "point.h"
#include "uiDraw.h"
#include "configuration.h"

/**********************************************************************
*
**********************************************************************/
class FlyingObject
{
protected:
	Velocity velocity;
	Point location;
	int size;
	int alive; //holds both alive and lives

public:
	// adding a basic constructor to take care of configuration
	FlyingObject() : velocity(), alive(true), location(), size(0) {}


	void advance(); // all objects advance
	inline virtual void kill() { alive = false; std::cout << "alive = false.\n"; }

	// Checks to see if the object is within the bounds of the screen
	bool isOnScreen();
	Point getLocation() const { return location; }
	Velocity getVelocity() const { return velocity; }
	int isAlive() const { return alive; }
	inline float getSize() const { return size; }



	void setVelocity(float nDx, float nDy);
	inline void setVelocity(Velocity nVel) { velocity.setDx(nVel.getDx()); velocity.setDy(nVel.getDy()); }
	
	void setAlive(int nAlive) { alive = nAlive; }
	// Needed a set location
	void setLocation(Point location) { this->location = location; }
	void setLocation(float nX, float nY) { location.setX(nX); location.setY(nY); }

	virtual void draw() {}
};

#endif  //FLYINGOBJECT_H
