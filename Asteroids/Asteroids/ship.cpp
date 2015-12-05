#include "ship.h"

// Put your ship methods here

void Ship::turnLeft()
{
	angle += ROTATE_AMOUNT;
	if (angle > 360)
		angle = angle % 360;
}

void Ship::turnRight()
{
	angle -= ROTATE_AMOUNT;
	if (angle < 0)
		angle += 360;
}

void Ship::thrust()
{
	velocity.setDx(velocity.getDx() + (cos(deg2rad(angle))));
	velocity.setDy(velocity.getDy() + (sin(deg2rad(angle))));
	return;
}

void Ship::draw()
{
	if (alive)
		drawShip(location, angle);
}
