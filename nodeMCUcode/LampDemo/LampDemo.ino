#include <ESP8266WiFi.h> //In cludes wifi library
#include <ESP8266HTTPClient.h> //Includes http client library. (Allows for fetching of data)
#include <Adafruit_NeoPixel.h> //RGB strip library
#define PIN 14 //set up rgb strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(5, PIN, NEO_GRB + NEO_KHZ800); // intalize the RGB strip

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "StudentNet";
char pass[] = "4153334021";

void setup()
{
  // Debug console
  Serial.begin(9600);
  Serial.println("Init");
  
  WiFi.begin(ssid, pass); //set up wifi
  while (WiFi.status() != WL_CONNECTED) { //wait untill wifi is connected
    Serial.print("Connecting.");
    delay(500);
  }
  Serial.println("Connected!");
  Serial.println(WiFi.localIP()); //print out ip

  strip.begin();
  strip.show(); // Initialize all leds to 'off'
 
}

void loop() {

  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status

    HTTPClient http;  //Declare an object of class HTTPClient

    http.begin("http://10.1.9.244:3000/v1");  //Specify request destination. This should be the ip of the computer that is acting as the server.
    int httpCode = http.GET(); //Send the request

    if (httpCode > 0) { //Check the returning code to see if the request was sucessfull

      String turnOn = http.getString();   //Get the request response payload
      Serial.println(turnOn);
      if (turnOn == "true") {
        //turn on light
        strip.setPixelColor(0, 255, 255, 255);
        strip.setPixelColor(1, 255, 255, 255);
        strip.setPixelColor(2, 255, 255, 255);
        strip.setPixelColor(3, 255, 255, 255); //parameters are (LED number in chain, Red 0-255, Green 0-255, Blue 0-255)
        strip.show();
      } else {
        //turn off light
        strip.setPixelColor(0, 0, 0, 0);
        strip.setPixelColor(1, 0, 0, 0);
        strip.setPixelColor(2, 0, 0, 0);
        strip.setPixelColor(3, 0, 0, 0);
         strip.show();
      }
           //Print the response payload

    } else {
      Serial.println('request failed');
      Serial.println(httpCode);
    }
   

    http.end();   //Close connection

  }

   delay(1000); //wait 1 second before requesting again

}
