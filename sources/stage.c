#include "../headers/stage.h"

Stage* init_stage(void) {
	// Initialise stage
	Stage* stage = malloc(sizeof(Stage));
	stage->ship = create_ship();
	stage->asteroids = NULL;
	stage->bullets = NULL;
	stage->score = 0;
	stage->lives = MAX_LIVES;
	return stage;
}

void doLogic(App* app, Stage* stage){

	if (stage->lives > 0)
	{
		// Update Ship
		update_ship(app, stage->ship);

		// Update bullet
		update_fire(app, stage);

		// Update asteroid
		update_asteroid(app, stage);

		check_asteroid_collision(stage);
	}

}
void check_asteroid_collision(Stage* stage) {

	for (int i = 0; i < MAX_ASTEROID; i++) {
		Asteroid* asteroid = &stage->asteroids->asteroid[i];
		if (asteroid != NULL && asteroid->alive) {
			
			check_bullet_asteroid_collision(asteroid, stage);

			if(stage->ship->invincible <= 0)
				check_bullet_asteroid_ship(asteroid, stage);
		}
	}
}

bool IsPointInsideCircle(float cx, float cy, float radius, float x, float y)
{
	return sqrt((x - cx) * (x - cx) + (y - cy) * (y - cy)) < radius;
}