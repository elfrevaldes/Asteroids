/***********************************************************************
* Source File:
*    Bird
* Author:
*    Logan Carpenter
* Summary:     qweqweq
*.
************************************************************************/


#include <math.h>

#include "bullet.h"
//#include "constants.h"

Bullet::Bullet(const Ship &ship) : FlyingObject()
{
	alive = BULLET_LIFE;

	//make an intial Velocity for the bullet based on the orientarion of the ship
	Velocity initialVelicity(ship.getAngle(), BULLET_SPEED);
	
	// sets the Velocity of the bullet based on the relative velocity of the ship
	velocity = initialVelicity + ship.getVelocity();

	//puts the location of the bullet at the tip of the ship
	float x = ship.getLocation().getX() + 10 * cos((ship.getAngle()* 3.14) / 180);
	float y = ship.getLocation().getY() + 10 * sin((ship.getAngle()* 3.14) / 180);
	location = Point(x, y);

	//wraps the bullet     // for testing purposes
	location.setWrap(true); 
}

// For shotgun
Bullet::Bullet(Ship &ship, int orientation)
{
	setLocation(ship.getLocation());
	setAlive(true);
	alive = BULLET_LIFE;
	//setVelocity(ship.getVelocity());

	//make an intial Velocity for the bullet based on the orientarion of the ship
	Velocity initialVelicity(ship.getAngle() + orientation, BULLET_SPEED);

	// sets the Velocity of the bullet based on the relative velocity of the ship
	velocity = initialVelicity + ship.getVelocity();

	//puts the location of the bullet at the tip of the ship
	float x = ship.getLocation().getX() + 10 * cos(((ship.getAngle() + orientation)
		* 3.14) / 180);
	float y = ship.getLocation().getY() + 10 * sin(((ship.getAngle() + orientation)
		* 3.14) / 180);
	location = Point(x, y);

	//wraps the bullet     // for testing purposes
	location.setWrap(true);
}


/**********************************************************************
*
**********************************************************************/
void Bullet::draw()
{
	if (alive)
		drawDot(Point(location.getX(), location.getY()));
	if (alive > 0)
	{
		--alive;
		std::cout << "bullet life: " << alive << std::endl;

	}
}

SonicBoom::SonicBoom(const Ship &ship)
{
	alive = BULLET_LIFE;
	size = ship.getSize();

	setLocation(ship.getLocation());
}

void SonicBoom::draw()
{
	if (alive)
	{
		drawCircle(location, size);
	}
	if (alive > 0)
	{
		--alive;
		size += SONICBOOM_SPEED;

		std::cout << "sonic boom life: " << alive << std::endl;
	}
}