#ifndef GRAB_H
#define GRAB_H

#include <stdint.h>
#include <unistd.h>

void lower();
void lower_half();
void lift();
void open_hand();
void close_hand();

uint8_t hand;
uint8_t lever;
#endif // GRAB_H
