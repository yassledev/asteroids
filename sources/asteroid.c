#include "../headers/asteroid.h"

AsteroidArray* init_ast(){
	AsteroidArray* ast = malloc(sizeof(AsteroidArray));
	for(int i = 0; i < MAX_ASTEROID; i++){
		ast->asteroid[i].alive = false;
	}
	ast->last_asteroid = DELAY_ASTEROID;
	return ast;
}

Asteroid* new_asteroid(){
	Asteroid* asteroid = malloc(sizeof(Asteroid));
	asteroid->alive = true;
	asteroid->size = DEFAULT_SIZE;
	asteroid->position.x = (int)(rand() % SCREEN_WIDTH / 2);
	asteroid->position.y = (int)(rand() % SCREEN_HEIGHT / 2);
	asteroid->velocity.x = ASTEROID_VELOCITY * cosf((float)(rand() % 10));
	asteroid->velocity.y = ASTEROID_VELOCITY * sinf((float)(rand() % 10));
	asteroid->angle = 0;
	return asteroid;
}

Asteroid* new_splitted_asteroid(Asteroid* asteroid, float angle, int size){
	Asteroid* splitted = malloc(sizeof(Asteroid));
	splitted->alive = true;
	splitted->size = size;
	splitted->position.x = asteroid->position.x;
	splitted->position.y = asteroid->position.y;
	splitted->velocity.x = ASTEROID_VELOCITY * cosf(angle);
	splitted->velocity.y = ASTEROID_VELOCITY * sinf(angle);
	splitted->angle = 0;
	return splitted;
}

void bounce_asteroid_left_right(Asteroid* asteroid) {
	if (asteroid->position.x > SCREEN_WIDTH)
		asteroid->position.x = 0;
	else if (asteroid->position.x < 0)
		asteroid->position.x = SCREEN_WIDTH;
}

void bounce_asteroid_top_bottom(Asteroid* asteroid) {
	if (asteroid->position.y > SCREEN_HEIGHT)
		asteroid->position.y = 0;
	else if (asteroid->position.y < 0)
		asteroid->position.y = SCREEN_HEIGHT;
}

void bounce_asteroid(Asteroid* asteroid) {
	bounce_asteroid_left_right(asteroid);
	bounce_asteroid_top_bottom(asteroid);
}

void move_asteroid(Asteroid* asteroid) {
	asteroid->position.x += asteroid->velocity.x;
	asteroid->position.y += asteroid->velocity.y;
	asteroid->angle += 0.01f;
}

void update_asteroid_alive(AsteroidArray* AsteroidArray) {
	for (int i = 0; i < MAX_ASTEROID; i++) {
		Asteroid* asteroid = &AsteroidArray->asteroid[i];
		if (asteroid->alive) {

			// Update asteroid position
			move_asteroid(asteroid);

			// Check offscreen
			bounce_asteroid(asteroid);
		}
	}
}

void generate_new_asteroid(AsteroidArray* asteroidArray) {
	for (int i = 0; i < MAX_ASTEROID; i++) {
		Asteroid* asteroid = &asteroidArray->asteroid[i];
		if (!asteroid->alive) {
			asteroidArray->asteroid[i] = *new_asteroid();
			break;
		}
	}
}

void insert_asteroid(AsteroidArray* asteroidArray, Asteroid* asteroid) {
	for (int i = 0; i < MAX_ASTEROID; i++) {
		if (!asteroidArray->asteroid[i].alive) {
			asteroidArray->asteroid[i] = *asteroid;
			return;
		}
	}
}
void create_new_splitted_asteroid(AsteroidArray* asteroidArray, Asteroid* asteroid, int size) {
	float angle = ((float)rand() / (float)RAND_MAX) * 6.283185f;
	Asteroid* asteroid_splitted = new_splitted_asteroid(asteroid, angle, size);
	insert_asteroid(asteroidArray, asteroid_splitted);
}

void split_asteroid(AsteroidArray* asteroidArray, Asteroid* asteroid) {
	
	if (asteroid->size > 12) {

		// Create 2 asteroids
		int size = asteroid->size/2;
		create_new_splitted_asteroid(asteroidArray, asteroid, size);
		create_new_splitted_asteroid(asteroidArray, asteroid, size);
	}
}

void update_asteroidArray_time(AsteroidArray* asteroidArray, int fps) {
	if (asteroidArray->last_asteroid > 0) {
		asteroidArray->last_asteroid -= fps;
	}
}

void spawn_asteroid_randomly(AsteroidArray* asteroidArray){
	if (asteroidArray->last_asteroid <= 0) {
		for (int i = 0; i < MAX_ASTEROID; i++) {
			Asteroid* asteroid = &asteroidArray->asteroid[i];
			if (!asteroid->alive) {
				asteroidArray->asteroid[i] = *new_asteroid();
				asteroidArray->last_asteroid = DELAY_ASTEROID;
				break;
			}
		}
	}
}

void update_asteroid(App* app, Stage* stage) {
	
	update_asteroidArray_time(stage->asteroids, app->fps);
	update_asteroid_alive(stage->asteroids);
	spawn_asteroid_randomly(stage->asteroids);
}