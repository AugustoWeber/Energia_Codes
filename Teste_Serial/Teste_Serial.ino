/**
 * BPS: 9600
 * Data bits: 8
 * Parity: none
 * Stop Bits: 1
 * Flow control: none
 */


char value[256];
char Buffer[256];
//String buffer;
//String bufferSerial;
char inByte;
char inByteS;
int cont;
int i;
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
  CleanBuffer(Buffer);
}

void loop()
{
  // put your main code here, to run repeatedly:
  //SendCmnd("AT");
  //Wait for command from Serial1

  //Serial.write("\nEsperando dados...\n");
  //while(!Serial.available());
  if(Serial.available()){
    //bufferSerial="";
    i=0;
    while(Serial.available()){
      inByteS = Serial.read();
      //bufferSerial.concat(inByteS);
      //Serial.write(inByteS);
      Buffer[i] = inByteS;
      i++;
    }
    //SendCmnd(bufferSerial);
    //Serial.write("\n");
    //Serial.write(Buffer);
    Serial2.write(Buffer);
    CleanBuffer(Buffer);
    //cont++;

    delay(500);
    //    while(!Serial2.available());
  }
  
  if(Serial2.available()){
    //bufferSerial="";
    cont++;
    i=0;
    while(Serial2.available()){
      inByte = Serial2.read();
      //bufferSerial.concat(inByteS);
      value[i]=inByte;
      i++;
    }
    //SendCmnd(bufferSerial);
    Serial.print(value);
    CleanBuffer(value);
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
  default:
    digitalWrite(RED,0);
    digitalWrite(GREEN,0);
    digitalWrite(BLUE,128);
    cont = 0;
    break;
  } 
  //Serial2.flush();
  //Serial.flush();
  delay(2500);
}

void CleanBuffer(char *Buffers){
  for(i;i>0;i--)
    Buffers[i]=0;
  Buffers[0]='\0';
  i=0;
}
/*
void SendCmnd(String Value){
 buffer = "";
 
 Value.toCharArray(value,Value.length());
 i = Value.length();
 value[i]={
 '\r','\n','\0'  };
 Serial.write("Send: ");
 Serial.write(value);
 Serial.write("\n");
 Serial2.write(value);
 Serial.write("Recived: ");
 
 delay(100);
 
 while(Serial2.available()){
 inByte = Serial2.read();
 //Serial.write(inByte);
 buffer.concat(inByte); 
 }
 if(buffer == ""){
 Serial.write("VAZIO");
 }
 
 buffer.concat("\n");
 //buffer.toCharArray(Buffer,buffer.length());
 Serial.println(buffer);
 inByte = 0;
 Serial2.flush();
 }
 */
