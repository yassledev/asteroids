#ifndef INPUT_H
#define INPUT_H

#include "common.h"
#include "structs.h"


void handleKeyDown(App* app, SDL_KeyboardEvent* event);
void handleKeyUp(App* app, SDL_KeyboardEvent* event);
void doInput(App* app);

#endif