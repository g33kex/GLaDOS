#ifndef GRAB_H
#define GRAB_H

#include <stdint.h>
#include <unistd.h>

#define LEVER_PORT 66;
#define HAND_port 67;

void lower();
void lower_half();
void lift();
void open_hand();
void close_hand();

uint8_t hand;
uint8_t lever;
#endif // GRAB_H
