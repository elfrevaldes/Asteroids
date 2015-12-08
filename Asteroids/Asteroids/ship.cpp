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

	float xShip = ((cos(deg2rad(angle))) * THRUST_AMOUNT);
	float yShip = ((sin(deg2rad(angle))) * THRUST_AMOUNT);
	velocity.setDx(velocity.getDx() + xShip);
	velocity.setDy(velocity.getDy() + yShip);
	return;
}

void Ship::slowDown()
{
	float xShip = ((cos(deg2rad(angle))) * THRUST_AMOUNT);
	float yShip = ((sin(deg2rad(angle))) * THRUST_AMOUNT);
	velocity.setDx(velocity.getDx() - xShip);
	velocity.setDy(velocity.getDy() - yShip);
	return;
}

void Ship::draw()
{
	if (alive)
		drawShip(location, angle, flames);
}

Ship & Ship::operator=(const Ship & rhs)
{
	this->alive = rhs.isAlive();
	this->angle = rhs.getAngle();
	this->location = rhs.getLocation();
	this->size = rhs.getSize();
	return *this;
}
