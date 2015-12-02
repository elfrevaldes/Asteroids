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
#define BULLET_LIFE 40


class Bullet : public FlyingObject
{
private:
	float angle;


public:

	Bullet()
	{
		Point p(200, -200);
		location = p;
	}

	Bullet(Ship&);

	Bullet(float, int);

	float getAngle() { return angle; }

	void setAngle(float nAngle) { angle = nAngle; }

	void setLocation(Point nP) { location = nP; }

	void shoot(float shotAngle);

	bool setHit(bool nHit) { hit = nHit; }

	void draw();
	void advance();
};

#endif 

