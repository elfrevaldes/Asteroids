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

Bullet::Bullet(Ship & ship)
{
	velocity.setDx(1 * cos((3.14 * ship.getAngle()) / 180.0));
	velocity.setDy(1 * sin((3.14 * ship.getAngle()) / 180.0));
	location = ship.getLocation();
	life = 40;
}

/**********************************************************************
*
**********************************************************************/
Bullet::Bullet(float angle, int gameLevel)
{
	//if (gameLevel == 1)
	//{
	//	//Point p(SCREEN_X_MAX, SCREEN_Y_MIN);/////////////////////
	//	location = p;
	//}
	//else if (gameLevel == 2)
	//{
	//	//Point p(0, SCREEN_Y_MIN);////////////////////////////
	//	location = p;
	//}

	alive = true;
	shoot(angle);
}

/**********************************************************************
*
**********************************************************************/
void Bullet::killBullet()
{
	//for (list<Bullet*>::iterator bulletIt = bullets.begin();
	//bulletIt != bullets.end();
	//	bulletIt++)
	//{
	//	(*bulletIt) = bullets.erase(*bulletIt);

	//}

	list<Bullet*>::iterator bulletIt = bullets.begin();


	// checks to see if the asteroid is alive, 
	// if not it deletes from the vector
	while (bulletIt != bullets.end())
	{
		if (!(*bulletIt)->isAlive())
		{
			bulletIt = bullets.erase(bulletIt);
		}
		else
		{
			bulletIt++;
		}
	}
}


/**********************************************************************
*
**********************************************************************/
void Bullet::shoot(float shotAngle)
{
	velocity.setDy(10 * cos((3.14 * shotAngle)/* / 180.0)*/));
	velocity.setDx(-10 * sin((3.14 * shotAngle)/* / 180.0)*/));

	//advance();
}

/**********************************************************************
*
**********************************************************************/
void Bullet::draw()
{
	drawDot(Point(location.getX(), location.getY()));
	advance();
}

void Bullet::advanceBullet()
{
	location.addX(velocity.getDx());
	location.addY(velocity.getDy());
	life--;
}

