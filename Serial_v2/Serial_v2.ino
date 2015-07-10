#define RED    RED_LED
#define GREEN  GREEN_LED
#define BLUE   BLUE_LED

#define FIM    "\n\r"

unsigned int   LED[3];

String    inputString;
boolean   stringComplete=false;
String    buffer;
String    Command;
boolean wait=0;
int     time = 10000; //Limit time to wait Serial1 answear in milliseconds
int     cont;
char    value[256];
char    inByte;

//ESP8266
//Network Info
String ssid = "Deus";
String passwd = "1234567890";

//EMONCMS
String Site = "http://emon-gpsnetcms.rhcloud.com/monitor/set.json?";
String Key = "3c314d1b0d6719a2123d56bd7edc8a66";


void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial2.begin(9600);
  pinMode(LED[0],OUTPUT);
  pinMode(LED[1],OUTPUT);
  pinMode(LED[2],OUTPUT);
  inputString.reserve(200);
  cont = 1;
  TestESP8266();
  Connect();
  delay(500);
}

void loop()
{
  SendCmnd("AT");
  delay(1000);
}

void TestESP8266(){
  Serial.println("Testando:");
  SendCmnd("AT+RST");
  SendCmnd("AT");
  SendCmnd("AT+GMR");
}

void Connect(){

  SendCmnd("AT+CWMODE?");
  SendCmnd("AT+CWMODE=1");
  SendCmnd("AT+CWLAP");

  Command = "AT+CWJAP=";
  Command.concat('"');
  Command.concat(ssid);
  Command.concat('"');
  Command.concat(",");
  Command.concat('"');
  Command.concat(passwd);
  Command.concat('"');
  SendCmnd(Command);

  SendCmnd("AT+CIPSTATUS");

}

void SendCmnd(String Value){
  Value.concat("\n\r");
  buffer = "";
  Value.toCharArray(value,Value.length());
  Serial.print("Send: ");
  Serial.println(value);
  Serial2.print(value);
  Serial.print("Recived: ");

  while(!Serial2.available()){
    while(Serial2.available()==0);
      inByte = Serial2.read();
    Serial.write(inByte);
    buffer.concat(inByte); 
  }
  Serial.write("\n");
  Serial.write("\n");
  Serial2.flush();
}

void serialEvent() {
  while(Serial2.available()) {
    // get the new byte:
    char inChar = (char)Serial2.read(); 
    // add it to the inputString:
    Serial.print(inChar);
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    } 
  }
  Serial.print("\n");
}

