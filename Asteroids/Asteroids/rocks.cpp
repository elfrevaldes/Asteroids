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
	drawSmallAsteroid(location, rotation);
}

/**********************************************************************
* FUNCTION Break Apart
*	puts out two small asteroids. 
**********************************************************************/
void MediumAsteroid::breakApart(std::list <Asteroid*> &asteroid)
{
	// First Small rock
	Asteroid* pAsteroid1 = new SmallAsteroid(location);
	Velocity smallAsteroid1Vel;
	smallAsteroid1Vel.setDx(3);
	smallAsteroid1Vel.setDy(0);
	pAsteroid1->setVelocity(velocity + smallAsteroid1Vel); // for a rightward direction
	asteroid.push_back(pAsteroid1);

	// Second Small Asteroid
	Asteroid* pAsteroid2 = new SmallAsteroid(location);
	Velocity smallAsteroid2Vel;
	smallAsteroid2Vel.setDx(-3);
	smallAsteroid2Vel.setDy(0);
	pAsteroid2->setVelocity(velocity + smallAsteroid2Vel); // for a leftward direction
	asteroid.push_back(pAsteroid2);
}

/**********************************************************************
* FUNCTION Draw 
*	draws Medium Asteroid
**********************************************************************/
void MediumAsteroid::draw()
{
	drawMediumAsteroid(location, rotation);
}

/**********************************************************************
*
**********************************************************************/
void LargeAsteroid::breakApart(std::list <Asteroid*> &asteroid)
{
	// First medium Asteroid
	Asteroid* pAsteroid1 = new MediumAsteroid(location);
	Velocity medAsteroid1Vel;
	medAsteroid1Vel.setDx(0);
	medAsteroid1Vel.setDy(1);
	pAsteroid1->setVelocity(velocity + medAsteroid1Vel); // for an upward direction
	asteroid.push_back(pAsteroid1);

	// Second medium Asteroid
	Asteroid* pAsteroid2 = new MediumAsteroid(location);
	Velocity medAsteroid2Vel;
	medAsteroid2Vel.setDx(0);
	medAsteroid2Vel.setDy(-1);
	pAsteroid2->setVelocity(velocity + medAsteroid2Vel); // for a downward direction
	asteroid.push_back(pAsteroid2);

	// Small Asteroid
	Asteroid* pAsteroid3 = new SmallAsteroid(location);
	Velocity smallAsteroid3Vel;
	smallAsteroid3Vel.setDx(2);
	smallAsteroid3Vel.setDy(0);
	pAsteroid3->setVelocity(velocity + smallAsteroid3Vel); // for a rightward direction
	asteroid.push_back(pAsteroid3);
}

/**********************************************************************
* FUNCTION Draw 
*	draws Large Asteroid 
**********************************************************************/
void LargeAsteroid::draw()
{
	drawLargeAsteroid(location, rotation);
}

Asteroid::Asteroid()
{
	rotation = 0;
}


void Asteroid::draw()
{
}

/********************************************************
* ADVANCES FOR ROTATIONS
*********************************************************/
void LargeAsteroid::advance()
{
	FlyingObject::advance();

	rotation += LARGE_ASTEROID_SPIN;
}

void MediumAsteroid::advance()
{
	FlyingObject::advance();

	rotation += MEDIUM_ASTEROID_SPIN;
}

void SmallAsteroid::advance()
{
	FlyingObject::advance();

	rotation += SMALL_ASTEROID_SPIN;
}

//*****************************************for survival mode
void LargeAsteroid::survivalAdvance()
{
	rotation += LARGE_ASTEROID_SPIN;
}

void MediumAsteroid::survivalAdvance()
{
	rotation += MEDIUM_ASTEROID_SPIN;
}

void SmallAsteroid::survivalAdvance()
{
	rotation += SMALL_ASTEROID_SPIN;
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



