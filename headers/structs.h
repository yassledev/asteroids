#ifndef STRUCTS_H
#define STRUCTS_H

#include "common.h"

typedef struct App {
	SDL_Renderer* renderer;
	SDL_Window* window;
	int keyboard[MAX_KEYBOARD_KEYS];
	int fps;
} App;
App app;

typedef struct Vector {
	float x;
	float y;
} Vector;

typedef struct Ship {
	Vector position;
	Vector velocity;
	Vector points[5];
	float angle;
	int invincible;
	int teleportation;
} Ship;

typedef struct Asteroid {
	int size;
	Vector position;
	Vector velocity;
	bool alive;
	float angle;
} Asteroid;

typedef struct AsteroidArray{
	Asteroid asteroid[MAX_ASTEROID];

	// Lastest asteroid time
	time_t last_asteroid;
} AsteroidArray;

typedef struct Bullet {
	Vector position;
	Vector velocity;
	bool alive;
	float angle;
	float createdTime;
} Bullet;

typedef struct BulletArray {
    Bullet bullet[100];
    time_t last_shot;
} BulletArray;

typedef struct Stage {

	// Current ship
	Ship* ship;

	// Asteroids display
	AsteroidArray* asteroids;

	// Bullets display
	BulletArray* bullets;

	// Number lives
	int lives;

	// Player score
	int score;
} Stage;

#endif STRUCTS_H