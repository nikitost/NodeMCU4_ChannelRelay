#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

/* Установите здесь свои SSID и пароль */
const char* ssid = "NodeMCU";       // SSID
const char* password = "001234567800";  // password

/* Настройки IP адреса */
IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);

uint8_t LED1pin = D1;
bool LED1status = LOW;

uint8_t LED2pin = D2;
bool LED2status = LOW;

uint8_t LED3pin = D3;
bool LED3status = LOW;

uint8_t LED4pin = D4;
bool LED4status = LOW;

void setup() 
{   
  Serial.begin(115200);
  pinMode(LED1pin, OUTPUT);
  pinMode(LED2pin, OUTPUT);
  pinMode(LED3pin, OUTPUT);
  pinMode(LED4pin, OUTPUT);

  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);
  
  server.on("/", handle_OnConnect);
  server.on("/led1on", handle_led1on);
  server.on("/led1off", handle_led1off);
  server.on("/led2on", handle_led2on);
  server.on("/led2off", handle_led2off);
  server.on("/led3on", handle_led3on);
  server.on("/led3off", handle_led3off);
  server.on("/led4on", handle_led4on);
  server.on("/led4off", handle_led4off);
  server.on("/led23on", handle_led23on);
  server.on("/led23off", handle_led23off);
  server.on("/led14on", handle_led14on);
  server.on("/led14off", handle_led14off);
  server.on("/ledallon", handle_ledallon);
  server.on("/ledalloff", handle_ledalloff);
  server.onNotFound(handle_NotFound);
  
  server.begin();
  //Serial.println("HTTP server started");
}

void loop() 
{
  server.handleClient();
  if(LED1status)
    digitalWrite(LED1pin, HIGH);
  else
    digitalWrite(LED1pin, LOW);
  
  if(LED2status)
    digitalWrite(LED2pin, HIGH);
  else
    digitalWrite(LED2pin, LOW);

  if(LED3status)
    digitalWrite(LED3pin, HIGH);
  else
    digitalWrite(LED3pin, LOW);
  
  if(LED4status)
    digitalWrite(LED4pin, HIGH);
  else
    digitalWrite(LED4pin, LOW);
}

void handle_OnConnect() 
{ 
  /*
  Serial.print("GPIO1 Status: ");
  if(LED1status)
    Serial.print("ON");
  else
    Serial.print("OFF");

  Serial.print(" | GPIO2 Status: ");
  if(LED2status)
    Serial.print("ON");
  else
    Serial.print("OFF");

  Serial.print("GPIO3 Status: ");
  if(LED3status)
    Serial.print("ON");
  else
    Serial.print("OFF");

  Serial.print(" | GPIO4 Status: ");
  if(LED4status)
    Serial.print("ON");
  else
    Serial.print("OFF");
    
  Serial.println("");*/
  server.send(200, "text/html", SendHTML(LED1status,LED2status,LED3status,LED4status)); 
}

void handle_led1on() 
{
  LED1status = HIGH;
  //Serial.println("GPIO8 Status: ON");
  server.send(200, "text/html", SendHTML(true,LED2status,LED3status,LED4status)); 
}

void handle_led1off() 
{
  LED1status = LOW;
  //Serial.println("GPIO8 Status: OFF");
  server.send(200, "text/html", SendHTML(false,LED2status,LED3status,LED4status)); 
}

void handle_led2on() 
{
  LED2status = HIGH;
  //Serial.println("GPIO7 Status: ON");
  server.send(200, "text/html", SendHTML(LED1status,true,LED3status,LED4status)); 
}

void handle_led2off() 
{
  LED2status = LOW;
  //Serial.println("GPIO7 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status,false,LED3status,LED4status)); 
}

void handle_led3on() 
{
  LED3status = HIGH;
  //Serial.println("GPIO6 Status: ON");
  server.send(200, "text/html", SendHTML(LED1status,LED2status,true,LED4status)); 
}

void handle_led3off() 
{
  LED3status = LOW;
  //Serial.println("GPIO6 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status,LED2status,false,LED4status)); 
}

void handle_led4on() 
{
  LED4status = HIGH;
  //Serial.println("GPIO5 Status: ON");
  server.send(200, "text/html", SendHTML(LED1status,LED2status,LED3status,true)); 
}

void handle_led4off() 
{
  LED4status = LOW;
  //Serial.println("GPIO5 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status,LED2status,LED3status,false)); 
}

void handle_led23on() 
{
  LED2status = HIGH;
  LED3status = HIGH;
  server.send(200, "text/html", SendHTML(LED1status,true,true,LED4status)); 
}

void handle_led23off() 
{
  LED2status = LOW;
  LED3status = LOW;
  server.send(200, "text/html", SendHTML(LED1status,false,false,LED4status)); 
}

void handle_led14on() 
{
  LED1status = HIGH;
  LED4status = HIGH;
  server.send(200, "text/html", SendHTML(true,LED2status,LED3status,true)); 
}

void handle_led14off() 
{
  LED1status = LOW;
  LED4status = LOW;
  server.send(200, "text/html", SendHTML(false,LED2status,LED3status,false)); 
}

void handle_ledallon() 
{
  LED1status = HIGH;
  LED2status = HIGH;
  LED3status = HIGH;
  LED4status = HIGH;
  server.send(200, "text/html", SendHTML(true,true,true,true)); 
}

void handle_ledalloff() 
{
  LED1status = LOW;
  LED2status = LOW;
  LED3status = LOW;
  LED4status = LOW;
  server.send(200, "text/html", SendHTML(false,false,false,false)); 
}

void handle_NotFound()
{
  server.send(404, "text/plain", "Not found");
}

String SendHTML(uint8_t led1stat,uint8_t led2stat, uint8_t led3stat,uint8_t led4stat)
{
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>LED Control</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #1abc9c;}\n";
  ptr +=".button-on:active {background-color: #16a085;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>Light Web Server</h1>\n";

  //ledNstat передают хендлы в эту функцию
  
  if(led1stat)
    ptr +="<p>LED1: OFF</p><a class=\"button button-on\" href=\"/led1off\">ON</a>\n";
  else
    ptr +="<p>LED1: ON</p><a class=\"button button-off\" href=\"/led1on\">OFF</a>\n";

  if(led2stat)
    ptr +="<p>LED2: OFF</p><a class=\"button button-on\" href=\"/led2off\">ON</a>\n";
  else
    ptr +="<p>LED2: ON</p><a class=\"button button-off\" href=\"/led2on\">OFF</a>\n";

  if(led3stat)
    ptr +="<p>LED3: OFF</p><a class=\"button button-on\" href=\"/led3off\">ON</a>\n";
  else
    ptr +="<p>LED3: ON</p><a class=\"button button-off\" href=\"/led3on\">OFF</a>\n";

  if(led4stat)
    ptr +="<p>LED4: OFF</p><a class=\"button button-on\" href=\"/led4off\">ON</a>\n";
  else
    ptr +="<p>LED4: ON</p><a class=\"button button-off\" href=\"/led4on\">OFF</a>\n";

  if(led1stat & led4stat)
    ptr +="<p>LED1+4</p><a class=\"button button-on\" href=\"/led14off\">ON</a>\n";
  else
    ptr +="<p>LED1+4</p><a class=\"button button-off\" href=\"/led14on\">OFF</a>\n";

  if(led2stat & led3stat)
    ptr +="<p>LED2+3</p><a class=\"button button-on\" href=\"/led23off\">ON</a>\n";
  else
    ptr +="<p>LED2+3</p><a class=\"button button-off\" href=\"/led23on\">OFF</a>\n";

  if(led1stat & led2stat & led3stat & led4stat)
    ptr +="<p>All LED</p><a class=\"button button-on\" href=\"/ledalloff\">ON</a>\n";
  else
    ptr +="<p>All LED</p><a class=\"button button-off\" href=\"/ledallon\">OFF</a>\n";
    
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
