#ifndef rocks_h
#define rocks_h

#include <list>
#include "flyingObject.h"
#include "configuration.h"

/**********************************************************************
*  CLASS ASTROID
**********************************************************************/
class Asteroid : public FlyingObject
{
protected:
	int rotation;
	int reward;
	int angle;

public:

	Asteroid();

	virtual void breakApart(std::list <Asteroid*> &asteroids) {}
	virtual void draw();
	virtual void advance() {}
	virtual void survivalAdvance() {}

	int getReward() { return reward; }
	

	Velocity getUnitVector();
	Velocity getUnitVector(Velocity object1, Velocity object2);

	//friend bool operator==(const Asteroid& lhs, const Asteroid& rhs);
	
};
//needs to be on the outside of the class becasue it has a lhs. 
//bool operator==(const Asteroid& lhs, const Asteroid& rhs) { return (&lhs == &rhs); }

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
		reward = 10;
	}

	void breakApart();
	void draw();
	void advance();
	void survivalAdvance();
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
		reward = 15;
	}

	void breakApart(std::list <Asteroid*> &asteroids);
	void draw();
	void advance();
	void survivalAdvance();
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
		reward = 20;
	}

	void breakApart(std::list <Asteroid*> &asteroids);
	void draw();
	void advance();
	void survivalAdvance();
};

#endif

