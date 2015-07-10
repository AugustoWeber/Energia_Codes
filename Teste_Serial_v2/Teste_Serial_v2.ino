/**
 * BPS: 9600
 * Data bits: 8
 * Parity: none
 * Stop Bits: 1
 * Flow control: none
 */


//char value[256];
//char Buffer[256];
//String buffer;
//String bufferSerial;
char inByte;
char inByteS;
int cont;
//int i;
#define RED    RED_LED
#define GREEN  GREEN_LED
#define BLUE   BLUE_LED

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial2.begin(9600);
  Serial2.setTimeout(5000);
  pinMode(RED,OUTPUT);
  pinMode(GREEN,OUTPUT);
  pinMode(BLUE,OUTPUT);
  digitalWrite(RED,128);
  digitalWrite(GREEN,0);
  digitalWrite(BLUE,0);
  cont = 0;
  inByte = 0;
  inByteS = 0;
  //CleanBuffer(Buffer);
}

void loop()
{
  if(Serial.available()){
    inByteS = Serial.read();
    Serial2.write(inByteS);
  }
  //delay(50);
  if(Serial2.available()){
    cont++;
    inByte = Serial2.read();
    Serial.print(inByte);
  }

  switch(cont){
  case 0: 
    digitalWrite(RED,128);
    digitalWrite(GREEN,0);
    digitalWrite(BLUE,0);
    //cont++;
    break;
  case 1:
    digitalWrite(RED,0);
    digitalWrite(GREEN,128);
    digitalWrite(BLUE,0);
    //cont++;  
    break;
  case 2:
    digitalWrite(RED,0);
    digitalWrite(GREEN,0);
    digitalWrite(BLUE,128);
    //cont++;  
    break;
  default:
    digitalWrite(RED,128);
    digitalWrite(GREEN,0);
    digitalWrite(BLUE,0);
    cont = 0;
    break;
  } 
  delay(50);
}
