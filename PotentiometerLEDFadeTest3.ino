#define BLUE 3
#define GREEN 5
#define RED 6
#define DIAL A0

class Vector3Int
{
  public: int X = 0;
  public: int Y = 0;
  public: int Z = 0;

  Vector3Int(int Xin, int Yin, int Zin)
  {
    X = Xin;
    Y = Yin;
    Z = Zin;
  }
};

void setup() {
  // put your setup code here, to run once:
pinMode(RED, OUTPUT);
pinMode(GREEN, OUTPUT);
pinMode(BLUE, OUTPUT);
digitalWrite(RED, HIGH);
digitalWrite(GREEN, LOW);
digitalWrite(BLUE, LOW);
Serial.begin(9600);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  //Serial.println(analogRead(DIAL));

  Vector3Int ledValues = GetLedVector2(analogRead(DIAL));

  String test = "Red: ";
  test = test + ledValues.X;
  test = test + "Green: ";
  test = test + ledValues.Y;
  test = test + "Blue: ";
  test = test + ledValues.Z;
  //String read = analogRead(DIAL);
  Serial.println(analogRead(DIAL) + test);
   analogWrite(RED, ledValues.X);
   analogWrite(GREEN, ledValues.Y);
   analogWrite(BLUE, ledValues.Z);
   delay(100);
}

Vector3Int GetLedVector(int input)
{
  int scaledInput = map((long)input, 0, 1023, 0, 255);

  return Vector3Int(
    constrain(127*sin(scaledInput/(25.5*PI) + (PI/2)), 0, 255),
    constrain(127*sin(scaledInput/ (25.5*PI)), 0, 255),
    constrain(127*sin(scaledInput/ (25.5*PI) - (PI/2)), 0 ,255)
  );
}

Vector3Int GetLedVector2(int input)
{
  input = constrain(input, 0, 1023);

  return Vector3Int(
    (int)GetRedLEDValue(input),
    GetGreenLEDValue(input),
    GetBlueLEDValue(input)
  );
}

float GetRedLEDValue(int input)
{
  if (input < 342)
  {
    // y = (-255/341)x + 255
    return -255*(float)input/341 +255;
  }
  else if (input < 683)
  {
    return 0;
  }
  else if (input < 1024)
  {
    // y = (255*x)/341 - 510
    return 255*(float)input/341 - 510;
  }
  else return 0;
}

int GetGreenLEDValue(int input)
{
  if (input < 342)
  {
    // y= 255x/341
    return (255 * (float)input)/341;
  }
  else if (input < 683)
  {
    // y = (-255 * x)/ 341 + 510
    return ((-255 * (float)input)/ 341) + 510;
  }
  else return 0;
}

int GetBlueLEDValue(int input)
{
  if (input < 341)
  {
    return 0;
  }
  else if ((float)input < 683)
  {
    // y = 255x/341 -255
    return ((255*(float)input)/341) - 255;
  }
  else if ((float)input < 1024)
  {
    // y = (-255 * x)/341 + 765
    return ((-255 * (float)input)/341) + 765;
  }
  else return 0;
}

