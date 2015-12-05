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
	bool alive;
	bool hit;
	// Needs a radius for drawing asteroids and error checking
	// int radius; // don't need this because the proffesor gave size = radius
	int size;

	// Checks to see if the object is within the bounds of the screen
	void collide();

public:
	// adding a basic constructor to take care of basic configuration
	FlyingObject() : velocity(), alive(true), location(), hit(false), size(0) {}

	void kill();
	inline float getSize() const { return size; }

	void advance(); // all objects advance
	bool isAlive() const { return alive; }

	Point getLocation() const { return location; }
	Velocity getVelocity() const { return velocity; }

	// Getter for the radius
	// int getRadius() const { return radius; }

	void setVelocity(float nDx, float nDy);
	void setLocation(float nX, float nY) { location.setX(nX); location.setY(nY); }
	void setAlive(bool nAlive) { alive = nAlive; }
	void setHit(bool nHit) { hit = nHit; }

	// Needed a set location
	void setLocation(Point location) { this->location = location; }
	// Setter for the radius

	//void setRadius(int radius);

	virtual void draw() = 0;
};

#endif  //FLYINGOBJECT_H
