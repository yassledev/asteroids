#include "../headers/bullet.h"

BulletArray* init_bullet_array(void){
    BulletArray* bulletArray = malloc(sizeof(BulletArray));
    for(int i = 0; i < MAX_BULLET; i++){
        bulletArray->bullet[i].alive = false;
    }
    bulletArray->last_shot = BULLET_DELAY;
    return bulletArray;
}

Bullet* fire_bullet(Ship* ship){
    Bullet* bullet = malloc(sizeof(Bullet));
    bullet->position.x = ship->position.x;
    bullet->position.y = ship->position.y;
    bullet->velocity.x = (float)(cosf(ship->angle) * BULLET_SPEED);
    bullet->velocity.y = (float)(sinf(ship->angle) * BULLET_SPEED);
    bullet->alive = true;
    return bullet;
}

void shoot_from_ship(int fps, BulletArray* bulletArray, Ship* ship){
    if(bulletArray->last_shot <= 0){
        for(int i = 0; i < MAX_BULLET; i++){
            Bullet* bullet = &bulletArray->bullet[i];
            if(!bullet->alive){
                bulletArray->bullet[i] = *fire_bullet(ship);
                bulletArray->last_shot = BULLET_DELAY;
                break;
            }
        }
    }
}

void check_bullet_offscreen(Bullet* bullet){
    if (bullet->position.x > SCREEN_WIDTH || bullet->position.y < 0)
        bullet->alive = false;
    if (bullet->position.y > SCREEN_HEIGHT || bullet->position.y < 0)
        bullet->alive = false;
}

void move_bullets(BulletArray* bulletArray){
    for(int i = 0; i < MAX_BULLET; i++){
        Bullet* bullet = &bulletArray->bullet[i];
        if(bullet->alive){
            bullet->position.x += bullet->velocity.x;
            bullet->position.y += bullet->velocity.y;
            check_bullet_offscreen(bullet);
        }
    }
}

void check_bullet_asteroid_collision(Asteroid* a, Stage* stage){
    for(int i = 0; i < MAX_BULLET; i++){
        Bullet* bullet = &stage->bullets->bullet[i];
        if(bullet->alive){
            if (IsPointInsideCircle(a->position.x, a->position.y, a->size, bullet->position.x, bullet->position.y)) {
                a->alive = false;
                bullet->alive = false;
                stage->score += 200;
                split_asteroid(stage->asteroids, a);
            }
        }
    }
}

void update_bulletArray_time(BulletArray* bulletArray, int fps) {
    if (bulletArray->last_shot > 0) {
        bulletArray->last_shot -= fps;
    }
}
void update_fire(App* app, Stage* stage) {
    
    update_bulletArray_time(stage->bullets, app->fps);

    if(app->keyboard[SDL_SCANCODE_SPACE] > 0)
        shoot_from_ship(app->fps, stage->bullets, stage->ship);

    move_bullets(stage->bullets);
}
