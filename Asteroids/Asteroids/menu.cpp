#include "menu.h"


/******************************************************************

******************************************************************/
void Menu::chooseMode()
{
	drawText(Point(-100, 200), "So you're the fool, ugh - I mean brave soul, who");
	drawText(Point(-100, 185), "    volunteered to protect planet tacos.");
	drawText(Point(-100, 160), "Well you're not much, but I guess you'll have to do.");


	drawText(Point(-75, (windowYMax / 4) + 15), "Pick your ship by selcting a mode:");
	drawText(Point(-60, (windowYMax / 4) - 15), "press c for classic mode");
	drawText(Point(-60, (windowYMax / 4) - 30), "press s for survival mode");
	drawText(Point(-60, (windowYMax / 4) - 45), "press b for bonus mode");

}


/******************************************************************

******************************************************************/
void Menu::classicModeStartDisplay()
{
	drawText(Point(-75, (windowYMax / 2) + 15), "Classic mode, good choice!");
	drawText(Point(-75, windowYMax / 2), "         press r to play");

	drawText(Point(-250, 100), "Press space to fire                                         .     .     .     .     .     .");
	drawText(Point(-250, 85), " and arrows to move");
	drawShip(Point(0, 100), 0, false); 

	drawText(Point(-250, 0), "Large asteroids will break                                   --->");
	drawText(Point(-250, -15), " into 2 medium and 1 small");
	drawLargeAsteroid(Point(0, 0), 5);
	drawMediumAsteroid(Point(100, 0), 5);
	drawMediumAsteroid(Point(140, 0), 1);
	drawSmallAsteroid(Point(180, 0), 1);

	drawText(Point(-250, -100), "Medium asteroids will break                                --->");
	drawText(Point(-250, -115), " into 2 small asteroids");
	drawMediumAsteroid(Point(0, -100), 5);
	drawSmallAsteroid(Point(90, -100), 1);
	drawSmallAsteroid(Point(120, -100), 1);

}


/******************************************************************

******************************************************************/
void Menu::bonusModeStartDisplay()
{
	drawText(Point(-75, windowYMax / 2), "press r to play bonus mode!");
}


/******************************************************************

******************************************************************/
void Menu::survivalModeStartDisplay()
{
	drawText(Point(-75, windowYMax / 2), "press r to play survival mode!");
}

void Menu::gameOverMessage()
{
	drawText(Point(-100, 200), "Well shucks you lived through the crash, but now you're");
	drawText(Point(-100, 185), " unprotected from the zero pressure of space. As you're ");
	drawText(Point(-100, 170), " blood starts to boil and you whole body expands you remember");
	drawText(Point(-100, 155), " that if you press r you can play again....");
}
