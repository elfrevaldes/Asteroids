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
#include <limits>
#include <algorithm>

using namespace std;

#define WINDOW_X_SIZE 200
#define WINDOW_Y_SIZE 200

float Point::xMax = 200;
float Point::xMin = -200;
float Point::yMax = 200;
float Point::yMin = -200;

Point Game :: topLeft;
Point Game :: bottomRight;

/***************************************
 * GAME :: getRandomPoint
 * Gets a random point within the boundaries of the world.
 ***************************************/
Point Game :: getRandomPoint() const
{
   int x = random(topLeft.getX(), bottomRight.getX());
   int y = random(bottomRight.getY(), topLeft.getY());
   
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
	   (*bulletIt)->killBullet();   ////temporary fix. I can't remember how to do template functions for kill() in flyingobject.
	   (*bulletIt)->advanceBullet();
	   
   }
   
   for (list<Asteroid*>::iterator asteroidIt = asteroids.begin();
        asteroidIt != asteroids.end();
        asteroidIt++)
   {
      (*asteroidIt)->advance();
   }
   
   checkForCollisions();
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
         pShip->thrust();
      }
      
      if (ui.isSpace())
      {
         Bullet* pBullet = new Bullet(*pShip);
         bullets.push_back(pBullet);
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
 * GAME :: checkForCollisions
 * Check for collisions between any two objects.
 *********************************************/
void Game::checkForCollisions()
{
   // go through each Asteroid
   for (list<Asteroid*>::iterator asteroidIt = asteroids.begin();
        asteroidIt != asteroids.end();
        asteroidIt++)
   {
      // check for collision with the ship
      if (isCollision(*pShip, **asteroidIt))
      {
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
   
   // we only collide if we're both alive
   if (obj1.isAlive() && obj2.isAlive())
   {
      float diff = getClosestDistance(obj1, obj2);
      float tooClose = obj1.getSize() + obj2.getSize();  //add to flying object
      
      if (diff < tooClose)
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
float Game :: getClosestDistance(const FlyingObject &obj1, const FlyingObject &obj2) const
{
   // from Br. Helfrich:
   // find the maximum distance traveled
   float dMax = max(abs(obj1.getVelocity().getDx()), abs(obj1.getVelocity().getDy()));
   dMax = max(dMax, abs(obj2.getVelocity().getDx()));
   dMax = max(dMax, abs(obj2.getVelocity().getDy()));
   dMax = max(dMax, 0.1f); // when dx and dy are 0.0. Go through the loop once.
   
   // we will advance by this number
   float distMin = std::numeric_limits<float>::max();
   for (float i = 0.0; i <= dMax; i++)
   {
      Point point1(obj1.getLocation().getX() + (obj1.getVelocity().getDx() * i / dMax),
                     obj1.getLocation().getY() + (obj1.getVelocity().getDy() * i / dMax));
      Point point2(obj2.getLocation().getX() + (obj2.getVelocity().getDx() * i / dMax),
                     obj2.getLocation().getY() + (obj2.getVelocity().getDy() * i / dMax));
      
      float xDiff = point1.getX() - point2.getX();
      float yDiff = point1.getY() - point2.getY();
      
      float distSquared = (xDiff * xDiff) +(yDiff * yDiff);
      
      distMin = min(distMin, distSquared);
   }
   
   return sqrt(distMin);
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
         delete pBullet;
         
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
