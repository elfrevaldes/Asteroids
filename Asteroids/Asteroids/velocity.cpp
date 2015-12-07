#include "velocity.h"


std::ostream & operator << (std::ostream & out, const Velocity & vel)
{
	out << "(" << vel.getDx() << ", " << vel.getDy() << ")";
	return out;
}

/*******************************************
* POINT extraction
*       Prompt for coordinates
******************************************/
std::istream & operator >> (std::istream & in, Velocity & vel)
{
	float dx;
	float dy;
	in >> dx >> dy;

	vel.setDx(dx);
	vel.setDy(dy);

	return in;
}

/*******************************************
* Velocity constructor that takes the angle
* and the speed to initialize everything
* (why to do it somewhere else?)
******************************************/
Velocity::Velocity(float angle, float speedIncrementor)
{
	setDx(speedIncrementor * cos((3.1415 * angle) / 180));
	setDy(speedIncrementor * sin((3.1415 * angle) / 180));
}

Velocity & Velocity::operator+(const Velocity & rhs)
{
	Velocity * temp = new Velocity(rhs); //*(new Velocity(rhs));
	temp->addOntoDx(this->getDx());
	temp->addOntoDy(this->getDy());
	return *temp;
}

Velocity & Velocity::operator=(const Velocity & rhs)
{
	this->setDx(rhs.getDx());
	this->setDy(rhs.getDy());
	return *this;
}
