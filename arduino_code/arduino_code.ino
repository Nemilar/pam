int digitMatrix[10][8] = {
    {0,2,3,4,0,6,7,8},
    {0,0,0,4,0,0,7,0},
    {0,2,0,4,5,6,0,8},
    {0,2,0,4,5,0,7,8},
    {0,0,3,4,5,0,7,0},
    {0,2,3,0,5,0,7,8},
    {0,2,3,0,5,6,7,8},
    {0,2,0,4,0,0,7,0},
    {0,2,3,4,5,6,7,8},
    {0,2,3,4,5,0,7,0}
};
int c1, c2, m1, m2, nr, ns, hr, hw;

byte inbyte; // for reading serial
char serString[12];

void enableIndicators()
{
  pinMode(A4, OUTPUT);
  digitalWrite(A4, LOW);
}

void turnAllOff()
{
  // disable outputs
  for (int x=2;x<=8;x++)
    pinMode(x, INPUT);
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
}

void writeDigit(int disp, int digit)
{
 // Serial.print("Setting ");
 // Serial.print(disp);
 // Serial.print(" to ");
 // Serial.println(digit);
  pinMode(disp, OUTPUT);
  digitalWrite(disp, LOW);
  for (int i=0;i<=7;i++)
  {
    if (digitMatrix[digit][i] != 0)
    {
      pinMode(digitMatrix[digit][i], OUTPUT);
      digitalWrite(digitMatrix[digit][i], HIGH);
      digitalWrite(10, HIGH);
    }
  }
}

void setup()
{
  Serial.begin(9600);
 // Serial.println("Starting...");
  // pins 5 thrugh 11 are the digital output pins 

}


void loop()
{

  if (Serial.available() == 8)
  {
    Serial.print("bytes=");
    Serial.println(Serial.available());
    Serial.print("Data=");
    c1 = Serial.read() - '0';
    Serial.println(c1);
     Serial.print("Data=");
    c2 = Serial.read() - '0';
    Serial.println(c2);
     Serial.print("Data=");
    m1 = Serial.read() - '0';
     Serial.println(m1);
     Serial.print("Data=");
    m2 = Serial.read() - '0';
     Serial.println(m2);
    Serial.print("Data=");
    nr = Serial.read() - '0';
     Serial.println(nr);
     Serial.print("Data=");
    ns = Serial.read() - '0';
     Serial.println(ns);
     Serial.print("Data=");
    hr = Serial.read() - '0';
     Serial.println(hr);
     Serial.print("Data=");
    hw = Serial.read() - '0';
     Serial.println(hw);

   // Serial.readBytes(serString, 11);
 //   c1 = serString[0] - '0';
 //   c2 = serString[1] - '0';
  //  m1 = serString[2] - '0';
  //  m2 = serString[3] - '0';
    Serial.write("ack");
  }
  else if (Serial.available() > 8)
  {
    Serial.println("Error - more than 8 bytes of data available.");
    for (int x = 0;x<=Serial.available();x++)
      Serial.read();
  }
  writeDigit(A0, c1);
  turnAllOff();
  writeDigit(A1, c2);
  turnAllOff();
  writeDigit(A2, m1);
  turnAllOff();
  writeDigit(A3, m2);
  turnAllOff();  
  
  if (nr == 1)
  {
    enableIndicators();
    pinMode(5, OUTPUT);
    digitalWrite(5, HIGH);
    turnAllOff();
  }
  if (ns == 1)
  {
    enableIndicators();
    pinMode(6, OUTPUT);
    digitalWrite(6, HIGH);
    turnAllOff();
  }
  if (hr == 1)
  {
    enableIndicators();
    pinMode(7, OUTPUT);
    digitalWrite(7, HIGH);
    turnAllOff();
  }
  if (hw == 1)
  {
    enableIndicators();
    pinMode(8, OUTPUT);
    digitalWrite(8, HIGH);
    turnAllOff();
  }
  
}
