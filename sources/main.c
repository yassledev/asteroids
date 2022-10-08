#include "../headers/main.h"

int main(int argc, char *argv[])
{
	App* app = malloc(sizeof(App));
		

	initSDL(app);
	
	// Init Stage;
	Stage* stage = init_stage();
	stage->bullets = init_bullet_array();
	stage->asteroids = init_ast();
	stage->asteroids->asteroid[0] = *new_asteroid();
	stage->asteroids->asteroid[1] = *new_asteroid();

	printf("fin");
	Uint32 next_fps = SDL_GetTicks();
	app->fps = 0;
	while(1){
		prepareScene(app);

		doInput(app);

		doLogic(app, stage);

		doDraw(app, stage);

		presentScene(app);

		//time it takes to render 1 frame in milliseconds
		next_fps += 1000 / 60;
		app->fps = next_fps - SDL_GetTicks();

		if (app->fps >= 0) {

			SDL_Delay(app->fps);
		}
	}

	cleanup(app);

	return 0;
}