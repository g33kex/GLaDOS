#ifndef BRAIN_H
#define BRAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "motion.h"
#include "sensors.h"
#include "grab.h"

#include "test_motion.h"
#include "test_sensors.h"

/* Functions */
/* @author Mathieu CHAMPION */
void run(void);

/* @author Mathieu CHAMPION */
void pick_and_place_normal(void);

/* @author Mathieu CHAMPION */
void pick_and_place_random(void);

#endif // BRAIN_H
