#ifndef STAGE_H
#define STAGE_H

#include "common.h"
#include "structs.h"

Stage* init_stage(void);

void doLogic(Stage* stage);
void check_asteroid_collision(Stage* stage);
bool IsPointInsideCircle(float cx, float cy, float radius, float x, float y);
#endif