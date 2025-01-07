//ARDUINO UNO
unsigned int val[] = {35, 38, 35, 20, 20, 20, 25, 5, 140, 255, 0, 20, 20, 20, 25, 35, 45, 55, 58, 56, 25};

void setup()
{
  pinMode(9, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop()
{
  
  int potValue = analogRead(A0);

  
  int delayTime = map(potValue, 0, 1023, 150, 1100);

  digitalWrite(13, HIGH);
  for (int i = 0; i <= 20; i++)
  {
    analogWrite(9, val[i]);
    delay(20);  
  }
  digitalWrite(13, LOW);
  analogWrite(9, 0);
  delay(delayTime); 
}
