#define RED    RED_LED
#define GREEN  GREEN_LED
#define BLUE   BLUE_LED

#define FIM    "\n\r"

unsigned int   LED[3];

String  inputString="";
boolean stringComplete=false;
String  buffer="";
String  Command="";
boolean wait=0;
int     time = 10000; //Limit time to wait Serial1 answear in milliseconds
int     cont;
char    value[256]="";
char    inByte='A';

//ESP8266
//Network Info
String ssid = "GEDRE-Visitantes";
String passwd = "gedre2013";

//EMONCMS
String Site = "http://emon-gpsnetcms.rhcloud.com/monitor/set.json?";
String Key = "3c314d1b0d6719a2123d56bd7edc8a66";


void SendCmnd(String Value);

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(LED[0],OUTPUT);
  pinMode(LED[1],OUTPUT);
  pinMode(LED[2],OUTPUT);
  inputString.reserve(200);
  cont = 1;
  delay(500);
}

void loop()
{
  delay(1000);
  switch(cont){
  case 1:
    digitalWrite(RED,HIGH);
    TestESP8266();
    cont++;
    break;
  case 2:
    digitalWrite(GREEN,HIGH);
    digitalWrite(RED,LOW);
    Connect();
    cont++;
    break;
  default:
    digitalWrite(BLUE,HIGH);
    digitalWrite(GREEN,LOW);
    SendCmnd("AT\n");
    digitalWrite(BLUE,LOW);
  }
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
  //Value.concat("\n\r");
  Value.toCharArray(value,Value.length());
  //wait = 1;
  buffer = "";
  Serial.println(value);
  Serial1.write(value);
  Serial.write("Recived: ");
  /*
  while(Serial1.available()){
    while(Serial1.available()==0);
    inByte = Serial1.read();
    Serial.write(inByte);
    buffer.concat(inByte); 
  }
  Serial.write("\n");
  Serial1.flush();
*/
}

void serialEvent() {
  while(Serial1.available()) {
    // get the new byte:
    char inChar = (char)Serial1.read(); 
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







