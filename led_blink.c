
//including the TimerOne library it helps in working with Hardware Timers and Interrupts in arduino.
#include <TimerOne.h>

//using macros we are defined variable constants temprature sensor pin,led pin,and threshole temperature i.e.,30^c;
#define TEMP_SENSOR_PIN A0
#define LED_PIN 13
#define THRESHOLD_TEMP 30


//defining the required variables
float temperature;
bool ledState = LOW;


//In void we are going to initialize the pins and timers which runs only once.
void setup() {
  pinMode(TEMP_SENSOR_PIN, INPUT);//temperature pin A0 is initialized as input.
  pinMode(LED_PIN, OUTPUT);   //led pin 13 is initialized as output.
  Timer1.initialize(250000); // initializing timer1, and set a 1/4 second period.
  Timer1.attachInterrupt(blinkLed); // attaching  blinkLed() function as a timer overflow interrupt.
}



void loop() {
  temperature = analogRead(TEMP_SENSOR_PIN) * 0.48828125;  /*It reads the temperature from the sensor, converts the analog       reading  to a temperature in degrees Celsius, and stores it in the temperature variable*/
  
  if (temperature < THRESHOLD_TEMP) {           /*If the temperature is below the threshold, it sets the period of Timer1 to       250 milliseconds  otherwise, it sets the period to 500 milliseconds.*/
  
    Timer1.setPeriod(250000); // 250 ms
  } else {
    Timer1.setPeriod(500000); // 500 ms
  }
}

void blinkLed() {             //it is a ISR  it is called whenever the timer overflows.It toggles LED to ON and OFF.
  ledState = !ledState;
  digitalWrite(LED_PIN, ledState);
}


