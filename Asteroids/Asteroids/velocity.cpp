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
// Put your velocity methods here
