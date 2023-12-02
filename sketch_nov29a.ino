/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "b8c38c3cab144d2fbc74ab57f686b8df";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "vivo1714";
char pass[] = "sudeesh97";

#define DHTPIN D1       


#define DHTTYPE DHT11    


DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;


void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V3, h);
  Blynk.virtualWrite(V2, t);
}

BLYNK_WRITE(V0)
{
  digitalWrite(D2,param.asInt());       //BULB
  Serial.print("D2=");
  Serial.println(param.asInt());

  digitalWrite(D3,param.asInt());       //FAN
  Serial.print("D3=");
  Serial.println(param.asInt());
  
  digitalWrite(D6,param.asInt());       //KITCHEN
  Serial.print("D6=");
  Serial.println(param.asInt());

  digitalWrite(D7,param.asInt());      //AC
  Serial.print("D7=");
  Serial.println(param.asInt());

  digitalWrite(D4,param.asInt());      //TV - R
  Serial.print("D4=");
  Serial.println(param.asInt());

}
BLYNK_WRITE(V1)
{
  digitalWrite(D3,param.asInt());                                 //FAN  LIVING ROOM  
}
BLYNK_WRITE(V4)                                                   //KITCHEN
{
  analogWrite(D6,param.asInt());
}
BLYNK_WRITE(V5)                                                   //AC BEDROOM
{
  analogWrite(D7,param.asInt());
}

BLYNK_WRITE(V6)                                                   //TV -- R  LIVING ROOM
{
  analogWrite(D4,param.asInt());
}

BLYNK_WRITE(V8)                                                   //BULB
{
  analogWrite(D2,param.asInt());
}



void setup()
{
  pinMode(D2,OUTPUT);  //BULB
  pinMode(D3,OUTPUT); //FAN
  pinMode(D6,OUTPUT); //KITCHEN
  pinMode(D7,OUTPUT); //AC
  pinMode(D4,OUTPUT); //TV --R
  
  digitalWrite(D2,LOW);
  digitalWrite(D3,LOW);
  digitalWrite(D6,LOW);
  digitalWrite(D7,LOW);
  digitalWrite(D4,LOW);
  

  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
 
  dht.begin();
  


  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}