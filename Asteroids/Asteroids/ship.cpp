#include "ship.h"

// Put your ship methods here

void Ship::turnLeft()
{
	angle += ROTATE_AMOUNT;
}

void Ship::turnRight()
{
	angle -= ROTATE_AMOUNT;
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
