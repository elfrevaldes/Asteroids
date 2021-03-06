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

// I think I figured this thing out
float Point::xMax = windowXMax;
float Point::xMin = windowXMin;
float Point::yMax = windowYMax;
float Point::yMin = windowYMin;

Point Game :: topLeft;
Point Game :: bottomRight;
int Game::nextLevelAsteroidCount;
int Game::level_timer;

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
   
   // moving the starts on the screen
   stars.advance(pShip->getVelocity());

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
	   if (mode == 's')//if it's survival mode
	   {
		   (*asteroidIt)->survivalAsteroidAdvance(pShip->getLocation(), (*asteroidIt)->getLocation());
		   (*asteroidIt)->survivalAdvance();
	   }
	   else
	   {
		   (*asteroidIt)->advance();
	   }
   }
   
   collisionCheck();
   cleanUpZombies();

   // Just checks for next level
   nextLevel();

}

/***************************************
 * GAME :: input
 * accept input from the user
 ***************************************/
void Game :: handleInput(const Interface & ui)
{
	if (ui.isP() /*&& pause*/) 
	{ 
		pause = !pause; 
	}
	//else if (ui.isP() && !pause) { pause = true; }		
	if (!pause)
	{
		if (pShip->isAlive() && timeToPlay)
		{
			if (ui.isLeft()) { pShip->turnLeft(); }

			if (ui.isRight()) { pShip->turnRight(); }

			// fix this mental bug
			if (ui.isUp())
			{
				pShip->setFlames(true);
				pShip->thrust();
			}
			else { pShip->setFlames(false); }

			if (ui.isDown()) { pShip->slowDown(); }


			if (ui.isSpace())
			{
				Bullet* pBullet = new Bullet(*pShip); // can this be done in one line?
				bullets.push_back(pBullet); // push_back(&(new Bullet(*pShip)));
			}

			if (mode == 'b')
			{
				if (ui.isB())
				{
					Bullet* pBullet = new SonicBoom(*pShip);
					bullets.push_back(pBullet);
				}

				if (ui.isN()) { shotgun(); }

				if (ui.isC()) { fourShot(); }
			}//if (mode == 'b')
		}//if (pShip->isAlive() && timeToPlay)
	}
   if (preGame)
   {
	   if (mode != 'N')
	   {
		   if (ui.isR())
		   {
			   preGame = false;
			   timeToPlay = true;
		   }
	   }//if (mode != 'N')

	   if (ui.isB()) { mode = 'b'; }
	   if (ui.isS()) { mode = 's'; }
	   if (ui.isC()) { mode = 'c'; }

   }//if (preGame)

   if (postGame)
   {
	   if (ui.isR())
	   {
		   restartGame();
		   mode = 'N';
		   preGame = true;
		   timeToPlay = false;
		   postGame = false;
		   pShip->setAlive(true);
	   }
   }//if (postGame)
}

/*********************************************
 * GAME :: DRAW
 * Draw everything on the screen
 *********************************************/
void Game :: draw(const Interface & ui)
{
	////////////////
	// Menu related draws
	////////////////
	if (preGame)
	{
		if (mode == 'N')
		{
			menu.chooseMode();
		}

		switch (mode)
		{
		case 'b':
			menu.bonusModeStartDisplay();
			break;
		case 'c':
			menu.classicModeStartDisplay();
			break;
		case 's':
			menu.survivalModeStartDisplay();
			break;
		default:
			break;
		}//switch
		std::cout << "Mode = " << mode << std::endl;
	}//if (preGame)
	else if (timeToPlay)
	{
		pShip->draw();

		// Drawing beautiful starts on the screen
		stars.draw();

		//for score
		drawText(Point(windowXMin + 5, windowYMax - 20), "score:");
		drawNumber(Point(windowXMin + 45, windowYMax - 10), getScore());

		//draws lives
		drawText(Point(windowXMax - 55, windowYMax - 20), "lives:");
		drawNumber(Point(windowXMax - 15, windowYMax - 10), pShip->getLives());



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
	}// else if (timeToPlay)
	else if (postGame)
	{
		menu.gameOverMessage();
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
		   (*asteroidIt)->kill();
		   (*asteroidIt)->breakApart(asteroids);
		   pShip->addToLives(-1);

		   if (pShip->getLives() == 0)
		   {
			   timeToPlay = false;
			   postGame = true;
		   }
		   else
		   {
			   restartGame();
		   }
	   }

	  ///////////////////////// FIGURE OUT BOUNCE!!!
/*	  for (list<Asteroid*>::iterator asteroidIt2 = asteroids.begin();
	  asteroidIt2 != asteroids.end();
		  asteroidIt2++)
	  {
		  if (asteroidIt != asteroidIt2) // maybe try this?
		  {
			objectBounce(asteroidIt, asteroidIt2);
		  }
	  }    */
      
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
			addToScore((*asteroidIt)->getReward());
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
* GAME :: object bounce
* gives the deflection of two objects that hit
*********************************************/
void Game::objectBounce(list<Asteroid*>::iterator asteroid1, list<Asteroid*>::iterator asteroid2)
{
	float distance = getClosestDistance((*asteroid1)->getLocation(), (*asteroid2)->getLocation());

	/////////////////////////// ELFRE look here. This is whats giving me troubles
	///////////////////////////   this is being called by Game::collisionCheck() line 171

	//if (distance <  ((*asteroid1)->getSize() + (*asteroid2)->getSize())
	//	&& !(asteroid1 == asteroid2))
	if (distance <=  ((*asteroid1)->getSize() + (*asteroid2)->getSize()) 
		&&!(asteroid1 == asteroid2))
	{
		(*asteroid1)->getVelocity().invertVelocity();
		(*asteroid2)->getVelocity().invertVelocity();

		std::cout << "asteroid on asteroid collision\n";
	}
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

void Game::nextLevel()
{
	// Checks to see if the list is empty
	if (asteroids.empty())
	{
		level_timer--;

		if (level_timer == 0)
		{
			level_timer = TIMER_RESET;
			nextLevelAsteroidCount++;

			// Adds 5 new asteroids to the game
			for (int i = 0; i < nextLevelAsteroidCount; i++)
			{
				Asteroid* pAsteroid = new LargeAsteroid(getRandomPoint());
				asteroids.push_back(pAsteroid);
			}
		}
	}
}

void Game::restartGame()
{
	pShip->setLocation(0, 0);
	pShip->setVelocity(0, 0);

	list<Asteroid*>::iterator asteroidIt = asteroids.begin();
	while (asteroidIt != asteroids.end())
	{
		(*asteroidIt)->kill();
		asteroidIt++;
	}//while
}

// Maybe make this just a line that goes, right now it slows
// down the game after pressing it three times.
void Game::shotgun()
{
	for (int i = SHOTGUN_LEFT_LIMIT; i < SHOTGUN_RIGHT_LIMIT; i++)
	{
		Bullet* pBullet = new Bullet(*pShip, i);
		bullets.push_back(pBullet);
	}
}

/*********************************************
* GAME :: FOUR SHOT
* shoot bullets in the front, back, left, and right.
*********************************************/
void Game::fourShot()
{
	Bullet* pBullet = new Bullet(*pShip);
	bullets.push_back(pBullet);

	Bullet* pBullet2 = new Bullet(*pShip, /*pShip->getAngle() +*/ 90);
	bullets.push_back(pBullet2);

	Bullet* pBullet3 = new Bullet(*pShip, /*pShip->getAngle() +*/ 180);
	bullets.push_back(pBullet3);

	Bullet* pBullet4 = new Bullet(*pShip, /*pShip->getAngle() +*/ 270);
	bullets.push_back(pBullet4);	
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
	/*Game *pGame;
	if (pUI->isN())
	{
		Point topLeft(windowXMin, windowYMax);
		Point bottomRight(windowXMax, windowYMin);
		Game game(topLeft, bottomRight);
		delete p;
		pGame = (Game *)p;
		pGame->advance();
		pGame->handleInput(*pUI);
		pGame->draw(*pUI);
	}
	else
	{*/
	Game *pGame = (Game *)p;
	pGame->draw(*pUI);
	pGame->handleInput(*pUI);
	if (!(pGame->getPause()))
	{
		pGame->advance();
	}
	else
	{
		if (pGame->getPause())
		{
			drawText(Point(-15, windowYMax / 2), "PAUSE");
		}
	}
	//}
	
}


/*********************************
 * Main is pretty sparse.  Just initialize
 * the game and call the display engine.
 * That is all!
 *********************************/
int main(int argc, char ** argv)
{
   Point topLeft(windowXMin, windowYMax);
   Point bottomRight(windowXMax, windowYMin);

   Interface ui(argc, argv, "Asteroids", topLeft, bottomRight);
   Game game(topLeft, bottomRight);
   ui.run(callBack, &game);
   
   return 0;
}
