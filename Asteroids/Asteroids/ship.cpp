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
	velocity.setDx(velocity.getDx() + (-cos(R_ANGLE)));
	velocity.setDy(velocity.getDy() + (-sin(R_ANGLE)));
	return;
}

void Ship::draw()
{
	if (alive)
		drawShip(location, angle);
}
