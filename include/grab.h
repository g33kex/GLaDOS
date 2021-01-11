#ifndef GRAB_H
#define GRAB_H

#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>

#define LEVER_PORT 66
#define HAND_PORT 67

#define GRAB_SPEED 100
#define LEVER_SPEED 250
#define CLOSED_HAND 10 //0 avant
#define OPENED_HAND -90
#define LEVER_UP -420
#define LEVER_MID -210
#define LEVER_DOWN 40

void lower();
void lower_half();
void lift();
void open_hand();
void close_hand();

bool grab_init();
bool grab_position_init();

uint8_t hand;
uint8_t lever;
#endif // GRAB_H
