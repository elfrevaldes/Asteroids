/*********************************************************************
 * File: game.h
 * Author: Br. Burton
 *
 * This file is provided as the instructor's "half" of the project.
 *
 * Please DO NOT provide, share, or distribute this file to students
 * of other sections or semesters.
 *********************************************************************/

#ifndef game_h
#define game_h


/****************************************
 * The game of Asteroids
 ****************************************/

#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"

#include "flyingObject.h"
#include "ship.h"
#include "rocks.h"
#include "bullet.h"
#include "configuration.h"

#include <list>
using namespace std;


/*****************************************
 * GAME
 * The main game class containing all the state
 *****************************************/
class Game
{
public:
   // create the game
	Game(Point tl, Point br) 
   {
      topLeft = tl;
      bottomRight = br;
	  nextLevelAsteroidCount = INITIAL_ASTEROID_COUNT;
	  level_timer = TIMER_RESET;
      
      pShip = new Ship;
	  score = 0;
      
      for (int i = 0; i < INITIAL_ASTEROID_COUNT; i++)
      {
         Asteroid* pAsteroid = new LargeAsteroid(getRandomPoint());
         asteroids.push_back(pAsteroid);
      }
   }
   
   // handle user input
   void handleInput(const Interface & ui);
   
   //handle score
   int getScore() { return score; }
   void addToScore(int scoreAdd) { score += scoreAdd; }
   
   // advance the game
   void advance();
   
   // draw stuff
   void draw(const Interface & ui);

   // Checks if all the asteroids are destroyed
   void nextLevel();
   
   static int getXMin() { return topLeft.getX(); }
   static int getXMax() { return bottomRight.getX(); }
   static int getYMin() { return bottomRight.getY(); }
   static int getYMax() { return topLeft.getY(); }
   
private:
   static Point topLeft;
   static Point bottomRight;
   static int nextLevelAsteroidCount;
   
   Ship* pShip;
   
   list<Bullet*> bullets;
   list<Asteroid*> asteroids;
   
   Point getRandomPoint() const;
   void collisionCheck();
   void cleanUpZombies();
   
   bool isCollision(const FlyingObject &obj1, const FlyingObject &obj2) const;
   float getClosestDistance(Point, Point/*const FlyingObject &obj1, const FlyingObject &obj2*/) const;
   
   void objectBounce(list<Asteroid*>::iterator asteroid1, list<Asteroid*>::iterator asteroid2);
   
   // For the few seconds before each new level begins
   static int level_timer;
   //int level_timer;
   int score;
};


#endif /* game_h */
