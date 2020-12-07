#include <stdio.h>
#include <unistd.h>

#include "ev3.h"
#include "ev3_light.h"
#include "ev3_port.h"
#include "ev3_sensor.h"
#include "sensors.h"



int test1(){
  printf("testing\n");
  printf("%s\n",get_color());
  return 0;
}
