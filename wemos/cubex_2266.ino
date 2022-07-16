#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <Servo.h>

Servo servo;
//Demon enabler
int common_topic = 0;
String demon_topic = "cubex/";
int sw = 0;


const char* mqtt_server = "broker.emqx.io";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);


void setup() 
{

  
    Serial.begin(115200);

    servo.attach(D0);
    servo.write(0);
    delay(2000);
    


    //wifiManager section
    WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
    // it is a good practice to make sure your code sets wifi mode how you want it.

    // put your setup code here, to run once:
    Serial.begin(115200);
    
    //WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wm;

    // reset settings - wipe stored credentials for testing
    // these are stored by the esp library
    wm.resetSettings();

    // Automatically connect using saved credentials,
    // if connection fails, it starts an access point with the specified name ( "AutoConnectAP"),
    // if empty will auto generate SSID, if password is blank it will be anonymous AP (wm.autoConnect())
    // then goes into a blocking loop awaiting configuration and will return success result

    bool res;
    // res = wm.autoConnect(); // auto generated AP name from chipid
    // res = wm.autoConnect("AutoConnectAP"); // anonymous ap
    res = wm.autoConnect("cubex2266","cubex2266"); // password protected ap

    if(!res) {
        Serial.println("Failed to connect");
        // ESP.restart();
    } 
    else {
        //if you get here you have connected to the WiFi    
        Serial.println("connected...yeey :)");
    }









  // mqtt connection section

  
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(MQTTcallback);
  while (!client.connected()) 
  {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP8266"))
    {
      Serial.println("connected");
    }
    else
    {
      Serial.print("failed with state ");
      Serial.println(client.state());
      delay(2000);
    }
  }

  // mqtt sec  
 
  
  client.subscribe("cubex/cubex2266");
  client.subscribe("cubex/demon1");
  

}


void MQTTcallback(char* topic, byte* payload, unsigned int length) 
{
  Serial.print("Message received in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  String message;
  for (int i = 0; i < length; i++) 
  {
    message = message + (char)payload[i];
  }
  Serial.print(message.substring(7));

  if(message.substring(0,6) == "enable"){
      common_topic = 1; 
     Serial.println("enabled ...");
    }

  demon_topic += message.substring(7);
  
  if(common_topic == 1){
          char copy[50];
          demon_topic.toCharArray(copy, 50);
          client.subscribe(copy);
         
        }
  if(message == "on"){
          
          if(sw == 0){
            servo.write(180);
            sw = 1;
          }else if(sw == 1){
            servo.write(0);
            sw = 0;
            
            }
          Serial.println("got signal from rfid");
          Serial.println("YEAHHHHHHHH");
    }
  
  Serial.println();
  Serial.println("-----------------------");
}



void loop() 
{
  
  client.loop();
}
