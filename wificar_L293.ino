#include <ESP8266WiFi.h>

IPAddress ip(192, 168, 44, 1);
IPAddress gateway(192, 168, 1, 254);
IPAddress subnet(255, 255, 255, 0);
const char *password = "123456789";
const char *ssid = "WifiCarnetwork" ;

WiFiServer server(80); // Port 80
const int IN1 = 2, IN2 = 4, IN3 = 13, IN4 = 12;
const int enable12 = 5 , enable34 = 14;
String header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
String html_1 = "<!DOCTYPE html><html><head><title>MOT Control</title></head><body><div id='main'><h2>MOT Control</h2>";
String html_2 = "<form id='F1' action='Stop'><input class='button' type='submit' value='Stop' ></form><br>";
String html_3 = "<form id='F2' action='Recule'><input class='button' type='submit' value='Recule' ></form><br>";
String html_4 = "<form id='F3' action='Gauche'><input class='button' type='submit' value='Gauche' ></form><br>";
String html_5 = "<form id='F4' action='Droite'><input class='button' type='submit' value='Droite' ></form><br>";
String html_6 = "<form id='F5' action='Avance'><input class='button' type='submit' value='Avance' ></form><br>";
String html_7 = "</div></body></html>";
String request = "";
void setup()
{
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(enable12, OUTPUT);
  pinMode(enable34, OUTPUT);
  digitalWrite(enable12, HIGH);
  digitalWrite(enable34, HIGH);
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(ip, ip, IPAddress(255, 255, 255, 0));   
  WiFi.softAP(ssid, password);
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED,LOW); 

  server.begin();
}

void loop()
{

// Check if a client has connected
    WiFiClient client = server.available();
    if (!client)  {  return;  }
 
    // Read the first line of the request
    request = client.readStringUntil('\r');
 
    if( request.indexOf("Avance") > 0 )  
    { 
    avance();  
    }
    if  ( request.indexOf("Recule") > 0 ) 
    { 
    recule();  
    }

    if  ( request.indexOf("Gauche") > 0 ) 
    { 
    gauche();
    }

    if  ( request.indexOf("Droite") > 0 ) 
    { 
    droite();   
    }

    if  ( request.indexOf("Stop") > 0 ) 
    { 
    stopnow();  
    }
    
    client.flush();
    client.print( header );
    client.print( html_1 );
    client.print( html_2 );
    client.print( html_3 );
    client.print( html_4);
    client.print( html_5);
    client.print( html_6);
    client.print( html_7);
    delay(5);
  
  
}

void avance()
{
  digitalWrite(IN1, HIGH);//moteurG
  digitalWrite(IN2, LOW);//moteurG
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void recule()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void gauche()
{digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  
}
void droite()
{
 digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopnow()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
