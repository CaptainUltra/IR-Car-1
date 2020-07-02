#include <IRremote.h> //Include the header for IR remote

//Pins
#define RECV_PIN 2 //IR sensor
#define MOTOR_OUTPUT_1 4
#define MOTOR_OUTPUT_2 5
#define MOTOR_OUTPUT_3 6
#define MOTOR_OUTPUT_4 7
#define BLINKER_RIGHT 12
#define BLINKER_LEFT 13
#define HEADLIGHTS 11

IRrecv irrecv(RECV_PIN);
decode_results results;      //Somewhere to store the IR signal results
bool headlightsFlag = false; //To store the state of the headlights. False = off.

//Signal to motor driver for forward direction
void forward()
{
  digitalWrite(MOTOR_OUTPUT_1, HIGH);
  digitalWrite(MOTOR_OUTPUT_2, LOW);
  digitalWrite(MOTOR_OUTPUT_3, LOW);
  digitalWrite(MOTOR_OUTPUT_4, HIGH);
}

//Signal to motor driver for turning left
void left()
{
  digitalWrite(MOTOR_OUTPUT_1, LOW);
  digitalWrite(MOTOR_OUTPUT_2, HIGH);
  digitalWrite(MOTOR_OUTPUT_3, LOW);
  digitalWrite(MOTOR_OUTPUT_4, HIGH);
}

//Signal to motor driver for turning right
void right()
{
  digitalWrite(MOTOR_OUTPUT_1, HIGH);
  digitalWrite(MOTOR_OUTPUT_2, LOW);
  digitalWrite(MOTOR_OUTPUT_3, HIGH);
  digitalWrite(MOTOR_OUTPUT_4, LOW);
}

//Signal to motor driver for backward direction
void backward()
{
  digitalWrite(MOTOR_OUTPUT_1, LOW);
  digitalWrite(MOTOR_OUTPUT_2, HIGH);
  digitalWrite(MOTOR_OUTPUT_3, HIGH);
  digitalWrite(MOTOR_OUTPUT_4, LOW);
}

//Signal to motor driver for stopping
void stop()
{
  digitalWrite(MOTOR_OUTPUT_1, LOW);
  digitalWrite(MOTOR_OUTPUT_2, LOW);
  digitalWrite(MOTOR_OUTPUT_3, LOW);
  digitalWrite(MOTOR_OUTPUT_4, LOW);
}

//Turn LED on and off
void blinker(int pin)
{
  int i = 1;
  while (i <= 3)
  {
    digitalWrite(pin, HIGH);
    delay(750);
    digitalWrite(pin, LOW);
    delay(750);
    i++;
  }
}

//Turn on/off headlights
void headlights()
{
  headlightsFlag = !headlightsFlag;
  if (headlightsFlag)
    digitalWrite(HEADLIGHTS, HIGH);
  else
    digitalWrite(HEADLIGHTS, LOW);
}

//Function to decode signal, print the result and take action
void decodeSignal()
{
  //Print hex signal to serial
  int value = results.value;
  Serial.println("*****************");
  Serial.println(value, HEX);

  //Determine which button is pressed
  //print and take action
  switch (value)
  {
  case 0xFD807F:
    Serial.println("Forward");
    forward();
    break;
  case 0xFD20DF:
    Serial.println("Left");
    left();
    break;
  case 0xFD609F:
    Serial.println("Right");
    right();
    break;
  case 0xFD906F:
    Serial.println("Backward");
    backward();
    break;
  case 0xFDA05F:
    Serial.println("Stop");
    stop();
    break;
  case 0xFD30CF:
    Serial.println("Headlights");
    headlights();
    break;
  case 0xFD10EF:
    Serial.println("Left blinker");
    blinker(BLINKER_LEFT);
    break;
  case 0xFD50AF:
    Serial.println("Right blinker");
    blinker(BLINKER_RIGHT);
    break;
  }

  Serial.println("*****************");
}

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(MOTOR_OUTPUT_1, OUTPUT);
  pinMode(MOTOR_OUTPUT_2, OUTPUT);
  pinMode(MOTOR_OUTPUT_3, OUTPUT);
  pinMode(MOTOR_OUTPUT_4, OUTPUT);
  pinMode(BLINKER_RIGHT, OUTPUT);
  pinMode(BLINKER_LEFT, OUTPUT);
  pinMode(HEADLIGHTS, OUTPUT);
}

void loop()
{
  if (irrecv.decode(&results))
  {
    decodeSignal();
    irrecv.resume(); // Receive the next value
  }
}
