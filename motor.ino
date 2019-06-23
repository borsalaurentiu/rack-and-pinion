void start_motor (int m1, int m2, int forward, int speed)
{
  if (speed == 0) // oprire
  {
    digitalWrite(m1, 0);
    digitalWrite(m2, 0);
  }
  else
  {
    if (forward)
    {
      digitalWrite(m2, 0);
      analogWrite (m1, speed); // folosire PWM
    }
    else
    {
      digitalWrite(m1, 0);
      analogWrite(m2, speed);
    }
  }
}

void stop_motor()
{
  start_motor (motor_pin_00, motor_pin_01, 0, 0);
}

void set_target(int position, int direction)
{
  long delta_time = complete_rotation_period * position / 10;
  Serial.println(delta_time);
  current_time = millis();
  while (millis() - current_time < delta_time && 0 == enable)
  {
    start_motor(motor_pin_00, motor_pin_01, direction, motor_speed);
    if (0 == direction)
      mechanism_position = (millis() - current_time) / rack_length;
    else
      mechanism_position = 9 - (millis() - current_time) / rack_length;
    real_time_position(mechanism_position + current_mechanism_position);
  }
  stop_motor();
  delay(1000);
}

void test_motor(int direction)
{
  if (0 == direction)
  {
    current_time = millis();
    while (millis() - current_time < complete_rotation_period && 0 != enable && 1 != enable)
    {
      start_motor(motor_pin_00, motor_pin_01, direction, motor_speed);
      mechanism_position = (millis() - current_time) / rack_length;
      real_time_position(mechanism_position);
    }
    stop_motor();
    delay(1000);
  }
  else
  {
    current_time = millis();
    while (millis() - current_time < complete_rotation_period && 0 != enable && 1 != enable)
    {
      start_motor(motor_pin_00, motor_pin_01, direction, motor_speed);
      mechanism_position = 9 - (millis() - current_time) / rack_length;
      real_time_position(mechanism_position);
    }
    stop_motor();
    delay(1000);
  }
}
