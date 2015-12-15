#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#define WINDOW_X_SIZE 400
#define WINDOW_Y_SIZE 400
#define INITIAL_ASTEROID_COUNT 1

//********** For Game
const float windowXMax = WINDOW_X_SIZE;
const float windowXMin = -WINDOW_X_SIZE;
const float windowYMax = WINDOW_Y_SIZE;
const float windowYMin = -WINDOW_Y_SIZE;

const int NEXT_LEVEL_ASTEROID_COUNT = 5;
const int TIMER_RESET = 120; // Roughly 4 seconds

const int SHOTGUN_LEFT_LIMIT = -5;
const int SHOTGUN_RIGHT_LIMIT = 5;

//********* For Flying Object
#define MAX_SURVIVAL_SPEED 3

//********* For Bullet
#define BULLET_SPEED 15
// like a timer
#define BULLET_LIFE 50

//********* For Sonic Boom
#define SONICBOOM_SPEED 5

//********* For Rocks
#define LARGE_ASTEROID_RADIUS 20
#define MEDIUM_ASTEROID_RADIUS 12
#define SMALL_ASTEROID_RADIUS 8  //I think 6 fit better than 4

#define LARGE_ASTEROID_SPIN 2
#define MEDIUM_ASTEROID_SPIN 5
#define SMALL_ASTEROID_SPIN 10

//********* For Ship
#define SHIP_SIZE 10
#define ROTATE_AMOUNT 6
#define THRUST_AMOUNT 0.5
#define MAX_SHIP_SPEED 2.0
#define deg2rad(value) ((3.1415 / 180) * (value))
#define ABS(value) ((value > 0)? value : value * -1)

#endif

