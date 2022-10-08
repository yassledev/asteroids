#ifndef BULLET_H
#define BULLET_H

#include "common.h"
#include "structs.h"

#define BULLET_SIZE 4
#define BULLET_SPEED 12
#define MAX_BULLET 30
#define BULLET_DELAY 150

BulletArray* init_bullet_array(void);
Bullet* fire_bullet(Ship* ship);
void shoot_from_ship(int fps, BulletArray* bulletArray, Ship* ship);
void check_bullet_offscreen(Bullet* bullet);
void move_bullets(BulletArray* bulletArray);
void update_fire(App* app, Stage* stage);
void check_bullet_asteroid_collision(Asteroid* a, Stage* stage);
void update_bulletArray_time(BulletArray* bulletArray, int fps);
#endif