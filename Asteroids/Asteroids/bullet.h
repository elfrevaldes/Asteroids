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



#define BULLET_SPEED 5
// like a timer
#define BULLET_LIFE 40


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

	void draw();
	//void advance(); // defined in FlyingObject
};

#endif 

