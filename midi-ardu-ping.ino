// by Jenner Hanni
// http://github.com/wicker
//
// Code from Bruce Allen 
// http://playground.arduino.cc/mMain/MaxSonar

const int pwPin = 7;

long pulse, inches, cm;  
int outOctave, count;

void setup() {
  count = 0;
  
  Serial.begin(9600);
  Serial.println("0, 0, Header, 0, 1, 120");
  Serial.println("1, 0, Start_track");   
}

void loop() {
  pinMode(pwPin, INPUT);
  
  pulse = pulseIn(pwPin, HIGH);
  inches = pulse/147;
  cm = inches * 2.54;
  delay(250);
  
  if (inches <= 7) 
    outOctave = 10;
  else if (inches >= 24)
    outOctave = 120;
  else
    outOctave =  inches*5;
    
  Serial.print("1, ");
  Serial.print(count);
  Serial.print(", Note_on_c, 11, ");
  Serial.print(outOctave);
  Serial.println(", 127");
  
  if (count > 2000)
  {
    Serial.print("1, ");
    Serial.print(count + 50);
    Serial.println(", End_track");
    Serial.println("0, 0, End_of_file");
    return;
  }
  count = count + 100;
}
