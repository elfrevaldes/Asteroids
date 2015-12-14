#ifndef menu_h
#define menu_h

#include "point.h"
#include "uiDraw.h"

class Menu
{
public:

	void chooseMode();

	void classicModeStartDisplay();
	void bonusModeStartDisplay();
	void survivalModeStartDisplay();

	void gameOverMessage();


};


#endif  /* menu.h   */
