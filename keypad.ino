int h = 0, v = 0;

byte keypad()
{
  static bool no_press_flag = 0;
  for (byte x = 0; x < 2; x++)
  {
    if (digitalRead(buttons[x]) == HIGH);
    else
      break;
    if (x == 1)
    {
      no_press_flag = 1;
      h = 0;
      v = 0;
    }
  }
  if (no_press_flag == 1)
  {
    digitalWrite(7, LOW);
    for (h = 0; h < 2; h++)
    {
      if (digitalRead(buttons[h]) == HIGH)
        continue;
      else
      {
        digitalWrite(7, HIGH);
        if (digitalRead(buttons[h]) == HIGH)
        {
          no_press_flag = 0;
          digitalWrite(7, LOW);
          return h;
        }

      }
    }
  }
  return 4;
}

void get_key()
{
  if (millis() - kdelay > period)
  {
    kdelay = millis();
    switch (keypad())
    {
      case 0:
        if (mechanism_position < 9)
        {
          mechanism_position++;
          delta_position++;
        }
        display_pinion(mechanism_position);
        break;
      case 1:
        if (mechanism_position > 0)
        {
          mechanism_position--;
          delta_position--;
        }
        display_pinion(mechanism_position);
        break;
      default: break;
    }
  }
}
