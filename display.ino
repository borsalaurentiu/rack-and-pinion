void display_pinion(int pinion)
{
  lcd.setCursor(0, 1);
  lcd.print("0 __________ 100");
  lcd.setCursor(11 - pinion, 1);
  lcd.print("o");
}

void draw_position()
{
  if (first == true)
  {
    if (10 == mechanism_position)
      mechanism_position--;
    display_pinion(mechanism_position);
    first = false;
  }
  stop_motor();
}

void real_time_position(int rack_position)
{
  if (rack_position >= 0)
  {
    for (int i = 0; i < 10; i++)
    {
      lcd.setCursor(i + 2, 1);
      if (i <= rack_position)
      {
        lcd.print((char)0xFF);
      }
      else
      {
        lcd.print("_");
      }
    }
  }
}
