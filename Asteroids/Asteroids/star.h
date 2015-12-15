#ifndef STAR_H
#define STAR_H

#include "point.h"
#include "uiDraw.h"
#include "velocity.h"
#include <list>
using std::list;
class Star
{
private:
	list <Point*> stars;
	// we don't want overlap starts
	bool isPointInList(const Point &pt) 
	{
		for (list<Point*>::iterator itPt = stars.begin(); itPt != stars.end(); itPt++)
		{
			if ((*itPt) == &pt)
				return true;
		}
		return false;
	}
public:
	Star(int numStar = 100) 
	{
		for (int i = 0; i < numStar; i++)
		{
			Point *pt;
			do
			{
				pt = new Point(random(Point().getXMin(), Point().getXMax()),
					           random(Point().getXMin(), Point().getXMax()));
				pt->setWrap(true);
			}
			 while (isPointInList(pt));
			stars.push_back(pt);
		}
	}
	void draw() 
	{ 
		for (list<Point*>::iterator pt = stars.begin(); pt != stars.end(); pt++)
		{
			if (random(1, 100) < 99)
				drawStar(*(*pt), 4);
		}
	}
	void advance(Velocity vel)
	{
		int dx = -vel.getDx() / 2;
		int dy = -vel.getDy() / 2;
		for (list<Point*>::iterator pt = stars.begin(); pt != stars.end(); pt++)
		{
			(*pt)->addX(dx);
			(*pt)->addY(dy);
		}
	}
};

#endif