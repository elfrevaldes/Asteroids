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

Bullet::Bullet(Ship &)
{
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
void Bullet::shoot(float shotAngle)
{
	velocity.setDy(10 * cos((3.14 * shotAngle) / 180.0));
	velocity.setDx(-10 * sin((3.14 * shotAngle) / 180.0));

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

void Bullet::advance()
{
}

