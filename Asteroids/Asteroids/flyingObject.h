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

/**********************************************************************
*
**********************************************************************/
class FlyingObject
{
protected:
	Velocity velocity;
	Point location;
	int alive;
	// size = radius
	int size;

	// Checks to see if the object is within the bounds of the screen
	//void collide(); // this function is wrong see (game.h)

public:
	// adding a basic constructor to take care of basic configuration
	FlyingObject() : velocity(), alive(true), location(), size(0) {}


	void advance(); // all objects advance
	inline void kill() { alive = false; }

	// Checks to see if the object is within the bounds of the screen
	bool isOnScreen();
	Point getLocation() const { return location; }
	Velocity getVelocity() const { return velocity; }
	bool isAlive() const { return alive; }
	inline float getSize() const { return size; }

	void setVelocity(float nDx, float nDy);
	
	void setAlive(bool nAlive) { alive = nAlive; }
	// Needed a set location
	void setLocation(Point location) { this->location = location; }
	void setLocation(float nX, float nY) { location.setX(nX); location.setY(nY); }

	virtual void draw() = 0;
};

#endif  //FLYINGOBJECT_H
