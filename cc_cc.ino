//https://github.com/PaulStoffregen/TimerOne/blob/master/examples/Interrupt/Interrupt.pde


#include <TimerOne.h>

// This example uses the timer interrupt to change pwm duty cycle
// to mantain a constant DC OUTPUT
//  D - Duty Cyle
// V_setpoint = V_input*D
// V_setpoint/V_input = D
double volatile V_input;
const double  Vmax = 40;
// sets setpoint to 5
double V_setpoint = 5;
const int led = LED_BUILTIN;  // the pin with a LED

void setup(void)
{
  pinMode(led, OUTPUT);
  // Voltage to read in DC
  pinMode(A0, INPUT);
  // Timer overflow each 1000 us --> 1 ms
  Timer1.initialize(1000);
  Timer1.attachInterrupt(CCconverter); // blinkLED to run every 0.15 seconds
  Serial.begin(9600);
  noInterrupts();
//  blinkCopy = blinkCount;
  interrupts();
}


// The interrupt will blink the LED, and keep
// track of how many times it has blinked.
int ledState = LOW;
volatile unsigned long blinkCount = 0; // use volatile for shared variables
double readADC(unsigned int port, double multiplier, double bias){
  return analogRead(port)*multiplier + bias;
}




void CCconverter(void)
{
  V_input = readADC(A0, Vmax/1023, 0);
  // TIMER1_A_PIN --> Digital Pin 9
  // TIMER1_B_PIN --> Digital Pin 10
  Timer1.setPwmDuty(TIMER1_A_PIN, (V_setpoint/V_input)*1023);
}


// The main program will print the blink count
// to the Arduino Serial Monitor
void loop(void)
{
//  unsigned long blinkCopy;  // holds a copy of the blinkCount

  // to read a variable which the interrupt code writes, we
  // must temporarily disable interrupts, to be sure it will
  // not change while we are reading.  To minimize the time
  // with interrupts off, just quickly make a copy, and then
  // use the copy while allowing the interrupt to keep working.



}
