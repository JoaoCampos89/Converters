//https://github.com/PaulStoffregen/TimerOne/blob/master/examples/Interrupt/Interrupt.pde


#include <TimerOne.h>

// This example uses the timer interrupt to change pwm duty cycle
// to use as inverter



const int led = LED_BUILTIN;  // the pin with a LED
// As the switch frequency is 1000 hz and timer overflow
// sin table counter is half of counter
int sin_table[10];
int f = 60;
int fs = 1200;
int timeIncrement;


int counter;
// max_counter is calculated based in T = 1/60 Ts = 1/fs
// max_counter = (int) T/Ts
// for fs = 1200
// max_counter = (int) (1/60)/(1/1200) = 20
unsigned int const max_counter = 20;
// stage 0 = PWM on positive cycle
// stage 1 = PWM on negative cycle
unsigned int stage = 0;


void setup(void)
{
  timeIncrement = 1/fs;
  pinMode(led, OUTPUT);
  // create sine_table with
  for (size_t i = 0; i < max_counter/2 i++) {
    sin_table[i] = sin(2*PI()*f*i*timeIncrement);
    /* code */
  }
  // Voltage to read in DC
  //pinMode(A0, INPUT);
  // Timer overflow frequency = 1/(833*10^-6) --> 1200 Hz
  Timer1.initialize(833);
  Timer1.attachInterrupt(CAconverter); // blinkLED to run every 0.15 seconds
  Serial.begin(9600);
  noInterrupts();
//  blinkCopy = blinkCount;
  interrupts();
}

const i
// The interrupt will blink the LED, and keep
// track of how many times it has blinked.
int ledState = LOW;
volatile unsigned long blinkCount = 0; // use volatile for shared variables
double readADC(unsigned int port, double multiplier, double bias){
  return analogRead(port)*multiplier + bias;
}




void CAconverter(void)
{
  if(counter>max_counter){
    counter = 0;
    stage = !stage;
    if(stage){
      Timer1.disablePwm(TIMER1_A_PIN);
      Timer1.pwm(TIMER1_B_PIN, 0);
    }else{
      Timer1.pwm(TIMER1_B_PIN, 0);
      Timer1.disablePwm(TIMER1_B_PIN);
    }
  }

  if(stage){
    //Timer1.disablePwm(TIMER1_A_PIN);
    Timer1.setPwmDuty(TIMER1_B_PIN, 1023*sin_table[counter]);
  }else{
    Timer1.setPwmDuty(TIMER1_A_PIN, 1023*sin_table[counter]);
  }

  counter ++;
}


// The main program will print the blink count
// to the Arduino Serial Monitor
void loop(void)
{

}
