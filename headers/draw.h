#ifndef DRAW_H
#define DRAW_H

#include "common.h"
#include "structs.h"

void prepareScene(App* app);
void presentScene(App* app);

void DrawCircle(SDL_Renderer* renderer, int centreX, int centreY, int radius);

// Draw all entities
void doDraw(App* app, Stage* stage);

void draw_ship(App* app, Ship* ship);
void draw_bullet(App* app, BulletArray* bulletArray);
void draw_asteroids(App* app, AsteroidArray* asteroidArray);
void draw_hud(App* app, Stage* stage);
void draw_end_title(App* app, Stage* stage);

#endif