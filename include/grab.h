#ifndef GRAB_H
#define GRAB_H

#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>

#define LEVER_PORT 66
#define HAND_PORT 67

#define GRAB_SPEED 100
#define LEVER_SPEED 400
#define CLOSED_HAND 0
#define OPENED_hand -180
#define LEVER_UP 0
#define LEVER_MID 144
#define LEVER_DOWN 300

void lower();
void lower_half();
void lift();
void open_hand();
void close_hand();

bool grab_init();

uint8_t hand;
uint8_t lever;
#endif // GRAB_H
