#include "rocks.h"
#include <list>

// Put your Rock methods here

/**********************************************************************
*  FUNCTION Draw 
*	draws Small Asteroid
**********************************************************************/
void SmallAsteroid::breakApart()
{

}

/**********************************************************************
*
**********************************************************************/
void SmallAsteroid::draw()
{
	drawSmallAsteroid(location, 5);
}

/**********************************************************************
* FUNCTION Break Apart
*	puts out two small asteroids. 
**********************************************************************/
void MediumAsteroid::breakApart(std::list <Asteroid*> &asteroid)
{
	Asteroid* asteroid1 = new SmallAsteroid(location);
	asteroid1->setVelocity(velocity + Velocity((float)2.0, (float)0.0));
	asteroid.push_back(asteroid1);

	Asteroid* asteroid2 = new SmallAsteroid(location);
	asteroid2->setVelocity(velocity + Velocity((float)-2.0, (float)0.0));
	asteroid.push_back(asteroid2);
}

/**********************************************************************
* FUNCTION Draw 
*	draws Medium Asteroid
**********************************************************************/
void MediumAsteroid::draw()
{
	drawMediumAsteroid(location, 5);
}

/**********************************************************************
*
**********************************************************************/
void LargeAsteroid::breakApart(std::list <Asteroid*> &asteroid)
{
	//pointer medium asteroid
	Asteroid* asteroid1 = new MediumAsteroid(location);
	Velocity vel1(getUnitVector(velocity, Velocity((float)0.0, (float)-1)));
	asteroid1->setVelocity(vel1 + Velocity((float)0.0, (float)-1));
	asteroid.push_back(asteroid1);

	Asteroid* asteroid2 = new MediumAsteroid(location);
	Velocity vel2(getUnitVector(velocity, Velocity((float)0.0, (float)1)));
	asteroid2->setVelocity(vel2 + Velocity((float)0.0, (float)1));
	asteroid.push_back(asteroid2);

	Asteroid* asteroid3 = new SmallAsteroid(location);
	Velocity vel3(getUnitVector(velocity, Velocity((float)1, (float)0.0)));
	asteroid3->setVelocity(vel3 + Velocity((float).25, (float)0.0));
	asteroid.push_back(asteroid3);
}

/**********************************************************************
* FUNCTION Draw 
*	draws Large Asteroid
**********************************************************************/
void LargeAsteroid::draw()
{
	drawLargeAsteroid(location, 5);
}

Asteroid::Asteroid()
{
}


void Asteroid::draw()
{
}

/**********************************************************************
* FUNCTION Get Unit Vector ()
*	makes a unit vector with random direction from two random numbers.
**********************************************************************/
Velocity Asteroid::getUnitVector()
{
	//need to be doubles for random function
	double x = random(-1, 1);
	double y = random(-1, 1);
	double magnitude;

	do 
	{
		x = random(-1, 1);
		y = random(-1, 1);
		magnitude = sqrt(pow(x, 2) + pow(y, 2));

	} while (x == 0 && y == 0);
	
	//Some vector math. The unitVector will have a random direction
	//with a speed of 1    need to be floats for Velocity constructor
	Velocity unitVector((float)magnitude*(float)x, (float)magnitude*(float)y);

	return unitVector;
}

/**********************************************************************
* FUNCTION Get Unit Vector (Vel, Vel)
*	finds the magnitude of the dot product of two velocities.
*	(adds the two velocities to gether and makes them equal to 1)
**********************************************************************/
Velocity Asteroid::getUnitVector(Velocity object1, Velocity object2)
{
	float x = object1.getDx() * object2.getDx();
	float y = object1.getDy() * object2.getDy();

	float magnitude = sqrt(pow(x, 2) + pow(y, 2));

	Velocity unitVector(magnitude*x, magnitude*y);

	return unitVector;
}

