#ifndef COMMON_H
#define COMMON_H

#include <SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define SCREEN_WIDTH   800
#define SCREEN_HEIGHT  600
#define PI 3.14159265359
#define MAX_KEYBOARD_KEYS 350
#define MAX_LIVES 3

#define MAX_ASTEROID 50

#include "asteroid.h"
#include "ship.h"
#include "bullet.h"
#include "stage.h"
#include "init.h"
#include "draw.h"
#include "input.h"
#include "font.h"

#endif COMMON_H