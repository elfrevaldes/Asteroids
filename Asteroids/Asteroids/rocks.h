#ifndef rocks_h
#define rocks_h

#include <list>
#include "flyingObject.h"
//#include "configuration.h"

#define LARGE_ASTEROID_RADIUS 16
#define MEDIUM_ASTEROID_RADIUS 8
#define SMALL_ASTEROID_RADIUS 6  //I think 6 fit better than 4

#define LARGE_ASTEROID_SPIN 2
#define MEDIUM_ASTEROID_SPIN 5
#define SMALL_ASTEROID_SPIN 10


/**********************************************************************
*  CLASS ASTROID
**********************************************************************/
class Asteroid : public FlyingObject
{
protected:
	int angle;

public:

	Asteroid();

	virtual void breakApart(std::list <Asteroid*> &asteroids) {}
	virtual void draw();

	Velocity getUnitVector();
	Velocity getUnitVector(Velocity object1, Velocity object2);
};

/**********************************************************************
*  CLASS SMALL ASTROID
**********************************************************************/
class SmallAsteroid : public Asteroid
{
private:
	
public:

	SmallAsteroid(Point startPoint)
	{
		setAlive(1);
		location = startPoint;
		size = SMALL_ASTEROID_RADIUS;
	}

	void breakApart();
	void draw();
};

/**********************************************************************
*  CLASS MEDIUM ASTROID
**********************************************************************/
class MediumAsteroid : public Asteroid
{
private:

public:

	MediumAsteroid(Point startPoint)// : Asteroid(1)
	{
		setAlive(1);
		location = startPoint;
		size = MEDIUM_ASTEROID_RADIUS;
	}

	void breakApart(std::list <Asteroid*> &asteroids);
	void draw();
};

/**********************************************************************
*  CLASS LARGE ASTEROID
**********************************************************************/
class LargeAsteroid : public Asteroid
{
private:

public:

	LargeAsteroid(Point startPoint)
	{
		setAlive(1);
		location = startPoint;
		size = LARGE_ASTEROID_RADIUS;
		velocity = getUnitVector();
		location.setWrap(true);
	}

	void breakApart(std::list <Asteroid*> &asteroids);
	void draw();
};

#endif

