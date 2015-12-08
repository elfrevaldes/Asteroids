/***********************************************************************
* Header File:
*    Velocity:
* Author:
*    Logan Carpenter
* Summary:
*
************************************************************************/
#ifndef VELOCITY_H
#define VELOCITY_H
#include <iostream> // for the overloading operators

/*********************************************
* Velocity
*********************************************/
class Velocity
{
private:
	float dx;
	float dy;

public:

	//static float STARTING_DX;
	//static float STARTING_DY;

	/**********************************************************************
	* Constructors
	**********************************************************************/
	inline Velocity() : dx(0), dy(0) {}

	Velocity(float x, float y) : dx(x), dy(y) {}
	Velocity(int angle, int speedIncrementor);
	inline Velocity(const Velocity &vel) { *this = vel; }

	/**********************************************************************
	* Getters
	**********************************************************************/
	inline float getDx() const { return dx; }
	inline float getDy() const { return dy; }

	/**********************************************************************
	* Setters (this setters need some checking)
	**********************************************************************/
	inline void setDx(float nDx) { dx = nDx; }
	inline void setDy(float nDy) { dy = nDy; }
	

	// Changed these to void b/c they don't need to return anything
	inline void addOntoDx(float nDx) { dx += nDx; }
	inline void addOntoDy(float nDy) { dy += nDy; }

	// overloading operator
	Velocity & operator + (const Velocity & rhs);
	Velocity & operator = (const Velocity & rhs);

};

std::ostream & operator << (std::ostream & out, const Velocity & vel);
std::istream & operator >> (std::istream & in, Velocity & vel);

#endif // VELOCITY_H
