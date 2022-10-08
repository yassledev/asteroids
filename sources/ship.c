#include "../headers/ship.h"

Ship* create_ship() {
	Ship* ship = malloc(sizeof(Ship));
	ship->position.x = SCREEN_WIDTH / 2;
	ship->position.y = SCREEN_HEIGHT / 2;
	ship->velocity.x = 0;
    ship->velocity.y = 0;
	ship->angle = 0;
	ship->invincible = 0;
	ship->teleportation = 0;
	return ship;
}

void rotate_ship_left(Ship* ship) {
	ship->angle -= SHIP_ROTATE_SPEED;
}
void rotate_ship_right(Ship* ship) {
	ship->angle += SHIP_ROTATE_SPEED;
}

void bounce_ship_left_right(Ship* ship) {
	if (ship->position.x > SCREEN_WIDTH)
		ship->position.x = 0;
	else if (ship->position.x < 0)
		ship->position.x = SCREEN_WIDTH;
}

void bounce_ship_top_bottom(Ship* ship) {
	if (ship->position.y > SCREEN_HEIGHT)
		ship->position.y = 0;
	else if (ship->position.y < 0)
		ship->position.y = SCREEN_HEIGHT;
}

void bounce_ship(Ship* ship) {
	bounce_ship_left_right(ship);
	bounce_ship_top_bottom(ship);
}

void check_max_velocity_accelerate(Ship* ship) {
	Vector* v = &ship->velocity;
	if (v->x > MAX_VELOCITY)
		v->x = MAX_VELOCITY;

	if (v->y > MAX_VELOCITY)
		v->y = MAX_VELOCITY;
}

void check_max_velocity_deccelerate(Ship* ship) {
	Vector* v = &ship->velocity;
	if (v->x < -MAX_VELOCITY)
		v->x = -MAX_VELOCITY;

	if (v->y < -MAX_VELOCITY)
		v->y = -MAX_VELOCITY;
}

void move_ship(Ship* ship) {
	ship->position.x += ship->velocity.x;
	ship->position.y += ship->velocity.y;
}

void accelerate_ship(Ship* ship) {
	ship->velocity.x += cos(ship->angle) * SHIP_VELOCITY;
	ship->velocity.y += sin(ship->angle) * SHIP_VELOCITY;
	check_max_velocity_accelerate(ship);
}
void deccelerate_ship(Ship* ship) {
	ship->velocity.x -= cosf(ship->angle) * SHIP_VELOCITY;
	ship->velocity.y -= sinf(ship->angle) * SHIP_VELOCITY;
	check_max_velocity_deccelerate(ship);

}

void teleport_ship(Ship* ship) {
	if (ship->teleportation <= 0) {
		ship->position.x = (int)(rand() % SCREEN_WIDTH);
		ship->position.y = (int)(rand() % SCREEN_HEIGHT);
		ship->teleportation = TELEPORTATION_DELAY;
		ship->invincible = INVINCIBILITY_DELAY;
	}
}

void check_keyboard_ship(App* app, Ship* ship) {
	// Rotate right
	if (app->keyboard[SDL_SCANCODE_RIGHT] > 0)
		rotate_ship_right(ship);

	// Rotate left
	if (app->keyboard[SDL_SCANCODE_LEFT] > 0)
		rotate_ship_left(ship);

	// Acceleration
	if (app->keyboard[SDL_SCANCODE_UP] > 0)
		accelerate_ship(ship);
	
	// Stress button teleportation
	if (app->keyboard[SDL_SCANCODE_Q] > 0)
		teleport_ship(ship);

}

void update_ship(App* app, Ship* ship) {

	// Check keyboard
	check_keyboard_ship(app, ship);

	// Check ship invincibility
	if (ship->invincible > 0)
		ship->invincible -= app->fps;

	// Check ship 
	if (ship->teleportation > 0)
		ship->teleportation -= app->fps;

	// Move ship
	move_ship(ship);

	// Bounce ship
	bounce_ship(ship);
}

void check_bullet_asteroid_ship(Asteroid* asteroid, Stage* stage) {

	if(IsPointInsideCircle(asteroid->position.x, asteroid->position.y, asteroid->size, stage->ship->position.x, stage->ship->position.y)) {
		stage->ship->position.x = SCREEN_WIDTH / 2;
		stage->ship->position.y = SCREEN_HEIGHT / 2;
		stage->ship->velocity.x = 0;
		stage->ship->velocity.y = 0;
		stage->ship->angle = 0;
		stage->ship->invincible = INVINCIBILITY_DELAY;
		stage->lives--;
	}
}