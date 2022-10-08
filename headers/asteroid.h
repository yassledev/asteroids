#ifndef ASTEROID_H
#define ASTEROID_H

#include "common.h"
#include "structs.h"

#define ASTEROID_LINES 10
#define ASTEROID_VELOCITY 2.1f
#define DEFAULT_SIZE 40
#define DELAY_ASTEROID 2500

AsteroidArray* init_ast(void);
Asteroid* new_asteroid();
Asteroid* new_splitted_asteroid(Asteroid* asteroid, float angle, int size);

// Bounce asteroid
void bounce_asteroid_left_right(Asteroid* asteroid);
void bounce_asteroid_top_bottom(Asteroid* asteroid);
void bounce_asteroid(Asteroid* asteroid);

// update asteroid
void move_asteroid(Asteroid* asteroid);
void update_asteroid(AsteroidArray* AsteroidArray);
void generate_new_asteroid(AsteroidArray* AsteroidArray);

// splitted asteroid
void split_asteroid(AsteroidArray* asteroidArray, Asteroid* asteroid);
void insert_asteroid(AsteroidArray* asteroidArray, Asteroid* asteroid);
void create_new_splitted_asteroid(AsteroidArray* asteroidArray, Asteroid* asteroid, int size);

// spawn asteroid
void update_asteroid(App* app, Stage* stage);
void update_asteroid_alive(AsteroidArray* AsteroidArray);
void update_asteroidArray_time(AsteroidArray* asteroidArray, int fps);
void spawn_asteroid_randomly(AsteroidArray* asteroidArray);
#endif