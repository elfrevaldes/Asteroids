#ifndef rocks_h
#define rocks_h

#include <list>
#include "flyingObject.h"

#define BIG_ROCK_SIZE 16
#define MEDIUM_ROCK_SIZE 8
#define SMALL_ROCK_SIZE 4

#define BIG_ROCK_SPIN 2
#define MEDIUM_ROCK_SPIN 5
#define SMALL_ROCK_SPIN 10


/**********************************************************************
*  CLASS SMALLASTROID
**********************************************************************/
class Asteroid : public FlyingObject
{
protected:
	int angle;

public:

	Asteroid();

	virtual void breakApart(std::list <Asteroid*> &asteroids) {}

	virtual void advance();

	virtual void draw();

	int spinAmount();

};

/**********************************************************************
*  CLASS SMALLASTROID
**********************************************************************/
class SmallAsteroid : public Asteroid
{
private:

public:

	SmallAsteroid()// : Asteroid(1)
	{
	//	setHealth(1);
	}

	void advance();
	void breakApart(SmallAsteroid);
	void draw();
};

/**********************************************************************
*  CLASS MEDIUMASTROID
**********************************************************************/
class MediumAsteroid : public Asteroid
{
private:


public:

	MediumAsteroid()// : Asteroid(1)
	{
		//setHealth(2);
	}

	void advance();
	void breakApart(SmallAsteroid);
	void draw();



};

/**********************************************************************
*  CLASS LARGE ASTEROID
**********************************************************************/
class LargeAsteroid : public Asteroid
{
private:

public:

	LargeAsteroid(Point)// : Asteroid(1)
	{
		//setHealth(3);
	}

	void advance();
	void breakApart(MediumAsteroid);
	void draw();

};

#endif

