#include <TimerOne.h>

#include <LiquidCrystal.h>
LiquidCrystal lcd(27, 26, 25, 24, 23, 22);

#define motor_pin_00 9
#define motor_pin_01 10

volatile int enable = -1;
volatile boolean first = false, t = false;
boolean sketch = true;

long current_time, complete_rotation_period, kdelay;  //ms
int mechanism_position = 0, current_mechanism_position = 0, delta_position = 0; //cm
int rack_length; //mm
int motor_speed, linear_velocity, acceleration;


const int period = 60; //ms
const byte buttons[2] = {5, 6};

void setup() {
  digitalWrite(motor_pin_00, 0);
  digitalWrite(motor_pin_01, 0);
  pinMode(motor_pin_00, OUTPUT);
  pinMode(motor_pin_01, OUTPUT);

  pinMode(7, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(2), mode1, RISING);
  attachInterrupt(digitalPinToInterrupt(3), mode2, RISING);

  lcd.begin(16, 2);
  lcd.setCursor(0, 1);
  lcd.print("0 _________o 100");

  motor_speed = 50;
  rack_length = 100;
  complete_rotation_period = 1000;
  Serial.begin(9600);
  Timer1.initialize(2000000);         // initialize timer1, and set a 1/2 second period
  Timer1.attachInterrupt(callback);  // attaches callback() as a timer overflow interrupt
}

void callback()
{
  t = not t;
  if (t == true)
  {
    linear_velocity = rack_length*100/complete_rotation_period;
    lcd.setCursor(0, 0);
    lcd.print("v = ");
    lcd.setCursor(4, 0);
    lcd.print(linear_velocity);
  //  lcd.setCursor(6, 0);
    lcd.print(" cm/s ");
  }
  else
  {
    acceleration = 0;
    lcd.setCursor(0, 0);
    lcd.print("a = ");
    lcd.setCursor(4, 0);
    lcd.print(acceleration);
    lcd.setCursor(5, 0);
    lcd.print(" cm/s^2");

  }
}


void loop() {

  switch (enable)
  {
    case -1:
      if (sketch == true)
      {
        test_motor(0);
        test_motor(1);
        sketch = false;
      }
      break;

    case 0:
      draw_position();
      stop_motor();
      if (delta_position > 0)
        set_target(delta_position, 0);
      else
        set_target(-delta_position, 1);
      enable = -1;
      current_mechanism_position = mechanism_position;
      delta_position = 0;
      break;

    case 1:
      draw_position();
      get_key();
      break;

    default: break;
  }
}
