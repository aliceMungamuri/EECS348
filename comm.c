#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "eecs388_lib.h"

void auto_brake(int devid)
{
uint16_t dist = 0;

if ('Y' == ser_read(devid) && 'Y' == ser_read(devid)) { // checks that the first two bytes so we know data is starting
uint16_t dist_L = ser_read(devid); //Reads the low byte 3-low 8 bits of distance
uint16_t dist_H = ser_read(devid); //Reads the high byte 4 -high 8 bits of distance



// Skip the remaining 5 bytes
for (int i = 0; i < 5; i++) {
ser_read(devid);
}

// Combine high and low bytes into a single 16-bit distance
dist = (dist_H << 8) | dist_L;

// Debug print
printf("Distance: %d cm\n", dist);

// LED control logic based on distance
if (dist > 200) {
gpio_write(GREEN_LED, ON);
gpio_write(RED_LED, OFF);
} else if (dist > 100) {
gpio_write(GREEN_LED, ON);
gpio_write(RED_LED, ON); // Yellow = Red + Green
} else if (dist > 60) {
gpio_write(RED_LED, ON);
gpio_write(GREEN_LED, OFF);
} else {
gpio_write(RED_LED, ON);
gpio_write(GREEN_LED, OFF);
delay(100);
gpio_write(RED_LED, OFF); //corresponding pwm signal
delay(100);
}
}
}

// TASK 2

int read_from_pi(int devid) //corresponding pwm signalk how long the ints are or - so might have to change
{ char ARRAY[60];
int angle=0;

if (ser_isready(devid)) {
ser_readline(devid, 60, ARRAY);
sscanf(ARRAY, "%d", &angle); // string to int
// printf("angle %d \n", angle);
return angle;
}

return 0; // default if no input available
}





void steering(int gpio, int pos)
{
// Task-3:
// Your code goes here (Use Lab 05 for reference)
// Check the project document to understand the task corresponding pwm signal
// printf("here\n");
if (pos<0) pos = 0;
if (pos>180) pos = 180;
int pulseRate = (2400 - 544)/180;
int pulsePeriod = (pulseRate * pos) + 544;
//Set gpio high for required pulse width
gpio_write(gpio, ON);
// Delay for the pulse widthchar ARRAY[6];
int angle;
delay_usec(pulsePeriod);
// Set gpio low for remainder of the 20 us cycle
gpio_write(gpio, OFF);
// Loop through the angles
delay_usec(20000 - pulsePeriod);
// YOUR CODE HERE
// Basically, you need to take the input angle "pos" and generate the
//corresponding pwm signal
// To generate the pwm signals, use gpio_write() and delay_usec()
}// // TASK 2



int main()
{
// initialize UART channels
// auto_brake(lidar_to_hifive); // measuring distance using lidar and braking
ser_setup(0); // uart0
ser_setup(1); // uart1
int pi_to_hifive = 1; //The connection with Pi uses uart 1
int lidar_to_hifive = 0; //the lidar uses uart 0
printf("\nUsing UART %d for Pi -> HiFive", pi_to_hifive);
printf("\nUsing UART %d for Lidar -> HiFive", lidar_to_hifive);
//Initializing PINs

gpio_mode(PIN_19, OUTPUT);
gpio_mode(RED_LED, OUTPUT);

gpio_mode(BLUE_LED, OUTPUT);
gpio_mode(GREEN_LED, OUTPUT);

printf("Setup completed.\n");
printf("Begin the main loop.\n");

while (1) {

auto_brake(lidar_to_hifive); // measuring distance using lidar and braking
//int angle = read_from_pi(pi_to_hifive); //getting turn direction from pi
//printf("\nangle=%d", angle)
int gpio = PIN_19;
for (int i = 0; i < 10; i++){
// Here, we set the angle to 180 if the prediction from the DNN is a positive angle
// and 0 if the prediction is a negative angle.
// This is so that it is easier to see the movement of the servo.
// You are welcome to pass the angle values directly to the steering function.
// If the servo function is written correctly, it should still work,
// only the movements of the servo will be more subtle
//if(angle>0){
// steering(gpio, angle);
//}
//else {
// steering(gpio, 0);
// }
// Uncomment the line below to see the actual angles on the servo.
// Remember to comment out the if-else statement above!
// steering(gpio, angle);
}

}
return 0;
}
