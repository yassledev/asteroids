#ifndef SHIP_H
#define SHIP_h

#include "common.h"
#include "structs.h"

#define SHIP_ROTATE_SPEED 0.1f
#define SHIP_VELOCITY 0.08f
#define SHIP_LINES 5
#define SHIP_SIZE 15
#define MAX_VELOCITY 2.0f
#define INVINCIBILITY_DELAY 2250
#define TELEPORTATION_DELAY 10000

Ship* create_ship();

// Rotate ship
void rotate_ship_left(Ship* ship);
void rotate_ship_right(Ship* ship);

// Bounce ship
void bounce_ship_left_right(Ship* ship);
void bounce_ship_top_bottom(Ship* ship);
void bounce_ship(Ship* ship);

// Velocity
void check_max_velocity_accelerate(Ship* ship);
void check_max_velocity_deccelerate(Ship* ship);
void accelerate_ship(Ship* ship);
void deccelerate_ship(Ship* ship);

// Position
void move_ship(Ship* ship);
void teleport_ship(Ship* ship);

// Update 
void check_keyboard_ship(App* app, Ship* ship);
void update_ship(App* app, Ship* ship);
void check_bullet_asteroid_ship(Asteroid* asteroid, Ship* ship);
#endif