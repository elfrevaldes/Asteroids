/*********************************************************************
 * File: game.cpp
 * Author: Br. Burton
 *
 * This file is provided as the instructor's "half" of the project.
 *
 * Please DO NOT provide, share, or distribute this file to students
 * of other sections or semesters.
 *********************************************************************/

#include "game.h"
//#include "configuration.h"
#include <limits>
#include <algorithm>

using namespace std;

// did the profesor add this because if he did not we need to get rid of this
#define WINDOW_X_SIZE 200
#define WINDOW_Y_SIZE 200

// we need to figure how to do this
//float Point::xMax = Game::getXMax();
float Point::xMax =  WINDOW_X_SIZE;
float Point::xMin = -WINDOW_X_SIZE;
float Point::yMax =  WINDOW_Y_SIZE;
float Point::yMin = -WINDOW_Y_SIZE;


Point Game :: topLeft;
Point Game :: bottomRight;

/***************************************
 * GAME :: getRandomPoint
 * Gets a random point within the boundaries of the world.
 * WHY NOT TO CREATE A CONSTRUCTOR THAT does this?
 ***************************************/
Point Game :: getRandomPoint() const
{
	int x;
	int y;

	do
	{
		x = random(topLeft.getX(), bottomRight.getX());
		y = random(bottomRight.getY(), topLeft.getY());
	
	} while (x < 50 && x > -50 && y < 50 && y > -50);

	Point p(x, y);

	return p;
}


/***************************************
 * GAME :: ADVANCE
 * advance the game one unit of time
 ***************************************/
void Game :: advance()
{
   pShip->advance();
   
   for (list<Bullet*>::iterator bulletIt = bullets.begin();
   bulletIt != bullets.end();
	   bulletIt++)
   {
	   (*bulletIt)->advance();  
   }
   
   for (list<Asteroid*>::iterator asteroidIt = asteroids.begin();
        asteroidIt != asteroids.end();
        asteroidIt++)
   {
      (*asteroidIt)->FlyingObject::advance();
   }
   
   collisionCheck();
   cleanUpZombies();

}

/***************************************
 * GAME :: input
 * accept input from the user
 ***************************************/
void Game :: handleInput(const Interface & ui)
{
   if (pShip->isAlive())
   {
      if (ui.isLeft())
      {
         pShip->turnLeft();
      }
      
      if (ui.isRight())
      {
         pShip->turnRight();
      }
      
      if (ui.isDown())
      {
		 pShip->setFlames(true);
         pShip->thrust();
      }
	  else
	  {
		  pShip->setFlames(false);
	  }

	  if (ui.isUp())
	  {
		  pShip->slowDown();
	  }


      if (ui.isSpace())
      {
         Bullet* pBullet = new Bullet(*pShip); // can this be done in one line?
         bullets.push_back(pBullet); // push_back(&(new Bullet(*pShip)));
      }
   }
}

/*********************************************
 * GAME :: DRAW
 * Draw everything on the screen
 *********************************************/
void Game :: draw(const Interface & ui)
{
	pShip->draw();
   
   for (list<Bullet*>::iterator bulletIt = bullets.begin();
        bulletIt != bullets.end();
        bulletIt++)
   {
      (*bulletIt)->draw();
   }
   
   for (list<Asteroid*>::iterator asteroidIt = asteroids.begin();
        asteroidIt != asteroids.end();
        asteroidIt++)
   {
      (*asteroidIt)->draw();      
   }
}

/*********************************************
 * GAME :: collisionCheck
 * Check for collisions between any two objects.
 *********************************************/
void Game::collisionCheck()
{
   // go through each Asteroid
   for (list<Asteroid*>::iterator asteroidIt = asteroids.begin();
        asteroidIt != asteroids.end();
        asteroidIt++)
   {
      // check for collision with the ship
      if (isCollision(*pShip, **asteroidIt))
      {
		 std::cout << "ship hit by asteroid.\n";
         pShip->kill();
         (*asteroidIt)->kill();
         (*asteroidIt)->breakApart(asteroids);
      }
      
      // go through each bullet
      for (list<Bullet*>::iterator bulletIt = bullets.begin();
           bulletIt != bullets.end();
           bulletIt++)
      {
         // check for collision between this asteroid and this bullet
         if (isCollision(**bulletIt, **asteroidIt))
         {
			std::cout << "Bullet hit an asteroid.\n";
            (*bulletIt)->kill();                     //add to flying object
            (*asteroidIt)->kill();
            (*asteroidIt)->breakApart(asteroids);
         }
      }
   }
}

/******************************************************
 * Function: isCollision
 * Description: Determine if two objects are colliding
 ******************************************************/
bool Game :: isCollision(const FlyingObject &obj1, const FlyingObject &obj2) const
{
   bool collision = false;
   
   // both objects need to be alive in order to check
   if (obj1.isAlive() && obj2.isAlive())
   {
      float difference = getClosestDistance(obj1.getLocation(), obj2.getLocation());
      float killDistance = obj1.getSize() + obj2.getSize();  //add to flying object
      
      if (difference < killDistance)
      {
         // we have a hit!
         collision = true;
      }
   }
   
   return collision;
}



/**********************************************************
 * Function: getClosestDistance
 * Description: Determine how close these two objects will
 *   get in between the frames.
 **********************************************************/
float Game::getClosestDistance(Point object1, Point object2) const
{
	// pathagorian theorm for the win
	double distance =
		sqrt(pow(object1.getX() - object2.getX(), 2) +
			pow(object1.getY() - object2.getY(), 2));

	return distance;
}


/*********************************************
 * GAME :: cleanUpZombies()
 * Look for and remove any objects that are dead.
 *********************************************/
void Game::cleanUpZombies()
{
   // Look for dead bullets
   list<Bullet*>::iterator bulletIt = bullets.begin();
   while (bulletIt != bullets.end())
   {
      Bullet* pBullet = *bulletIt;
      
      if (!pBullet->isAlive())
      {
         // first deallocate
		  std::cout << "bullet life: " << pBullet->isAlive() << std::endl;

         delete pBullet;
		 std::cout << "deleting bullet\n";
		 
         // now remove from list and advance
         bulletIt = bullets.erase(bulletIt);
      }
      else
      {
         bulletIt++; // advance
      }
   }
   
   // Look for dead asteroids
   list<Asteroid*>::iterator asteroidIt = asteroids.begin();
   while (asteroidIt != asteroids.end())
   {
      Asteroid* pAsteroid = *asteroidIt;
      
      if (!pAsteroid->isAlive())
      {
         // first deallocate
         delete pAsteroid;
         
         // now remove from list and advance
         asteroidIt = asteroids.erase(asteroidIt);
      }
      else
      {
         asteroidIt++; // advance
      }
   }
}


/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface *pUI, void *p)
{
   Game *pGame = (Game *)p;
   
   pGame->advance();
   pGame->handleInput(*pUI);
   pGame->draw(*pUI);
}


/*********************************
 * Main is pretty sparse.  Just initialize
 * the game and call the display engine.
 * That is all!
 *********************************/
int main(int argc, char ** argv)
{
   Point topLeft(-WINDOW_X_SIZE, WINDOW_Y_SIZE);
   Point bottomRight(WINDOW_X_SIZE, -WINDOW_Y_SIZE);

   Interface ui(argc, argv, "Asteroids", topLeft, bottomRight);
   Game game(topLeft, bottomRight);
   ui.run(callBack, &game);
   
   return 0;
}
