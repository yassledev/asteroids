#include "../headers/draw.h"

void prepareScene(App* app)
{
	SDL_SetRenderDrawColor(app->renderer, 32, 32, 32, 255);
	SDL_RenderClear(app->renderer);
}

void presentScene(App* app)
{
	SDL_RenderPresent(app->renderer);
}

void draw_ship(App* app, Ship* ship) {
	SDL_Point points[SHIP_LINES]; 
	
	const Vector ship_sprite[SHIP_LINES] = {
		-SHIP_SIZE, -SHIP_SIZE,
		SHIP_SIZE, 0.0f,
		-SHIP_SIZE,  SHIP_SIZE,
		-SHIP_SIZE * 0.5f, 0.0f,
		-SHIP_SIZE, -SHIP_SIZE
	};
	
	// Rotate
	for (int i = 0; i < SHIP_LINES; i++)
	{
		points[i].x = ship_sprite[i].x * cosf(ship->angle) - ship_sprite[i].y * sinf(ship->angle);
		points[i].y = ship_sprite[i].x * sinf(ship->angle) + ship_sprite[i].y * cosf(ship->angle);
	}

	// Translate
	for (int i = 0; i < SHIP_LINES; i++)
	{
		points[i].x = (int)(points[i].x + ship->position.x);
		points[i].y = (int)(points[i].y + ship->position.y);
	}

	if (ship->invincible > 0) {
		if(ship->invincible%2 == 0)
			SDL_SetRenderDrawColor(app->renderer, 255, 255, 0, 255);
		else
			SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
	}
	else
		SDL_SetRenderDrawColor(app->renderer, 255, 255, 255, 255);
	
	SDL_RenderDrawLines(app->renderer, points, SHIP_LINES);
}

void draw_bullet(App* app, BulletArray* bulletArray){
	for(int i = 0; i < 100; i++){
		Bullet* bullet = &bulletArray->bullet[i];
		if(bullet->alive){

			SDL_SetRenderDrawColor(app->renderer, 255, 0, 0, 255);
			DrawCircle(app->renderer, (int)bullet->position.x, (int)bullet->position.y, BULLET_SIZE);

		}
	}
}

void draw_asteroid(App* app, AsteroidArray* asteroidArray){
	for(int i = 0; i < MAX_ASTEROID; i++){
		Asteroid* asteroid = &asteroidArray->asteroid[i];
		if(asteroid->alive){
			SDL_SetRenderDrawColor(app->renderer, 255, 255, 0, 255);
			DrawCircle(app->renderer, asteroid->position.x, asteroid->position.y, asteroid->size);
		}
	}

}

void draw_hud(App* app, Stage* stage) {
 
	SDL_SetRenderDrawColor(app->renderer, 255, 255, 255, 255);
	char score[256];
	sprintf(score, "Score : %d", stage->score);
	draw_string(app->renderer, 10, 30, score);

	char lives[12];
	sprintf(lives, "Life : %d", stage->lives);
	draw_string(app->renderer, 10, 60, lives);

	if (stage->ship->teleportation > 0) {
		char teleport[20];
		sprintf(teleport, "%ds before teleport", (stage->ship->teleportation/1000));
		draw_string(app->renderer, (SCREEN_WIDTH /2) + 60 , 30, teleport);
	}
}


void draw_end_title(App* app, Stage* stage) {
	SDL_SetRenderDrawColor(app->renderer, 255, 255, 255, 255);
	draw_string(app->renderer, SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2, "Fin de la partie");

	char score[256];
	sprintf(score, "Score final : %d", stage->score);
	draw_string(app->renderer, SCREEN_WIDTH / 2 - 100, (SCREEN_HEIGHT / 2) + 45, score);
}

void doDraw(App* app, Stage* stage) {

	if (stage->lives != 0)
	{
		draw_ship(app, stage->ship);

		draw_bullet(app, stage->bullets);

		draw_asteroid(app, stage->asteroids);

		draw_hud(app, stage);
	}
	else
	{
		draw_end_title(app, stage);
	}
}

void DrawCircle(SDL_Renderer* renderer, int centreX, int centreY, int radius)
{
   const int diameter = (radius * 2);

   int x = (radius - 1);
   int y = 0;
   int tx = 1;
   int ty = 1;
   int error = (tx - diameter);

   while (x >= y)
   {
      //  Each of the following renders an octant of the circle
      SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

      if (error <= 0)
      {
         ++y;
         error += ty;
         ty += 2;
      }

      if (error > 0)
      {
         --x;
         tx += 2;
         error += (tx - diameter);
      }
   }
}