#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <SPI.h>
#include <MFRC522.h>


//RFIF config
constexpr uint8_t RST_PIN = D0;     // Configurable, see typical pin layout above
constexpr uint8_t SS_PIN = D2;     // Configurable, see typical pin layout above

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key;

String tag;
int common_topic = 1; //1

String demon_topic = "cubex/demon";

const char* mqtt_server = "broker.emqx.io";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    String client_id = "esp32-client-";
    if (client.connect(client_id.c_str(), "emqx", "public")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic","hello world");
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}





void setup() 
{

  
    Serial.begin(115200);

    //RFID init
    SPI.begin(); // Init SPI bus
    rfid.PCD_Init(); // Init MFRC522


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
    res = wm.autoConnect("cubex1155","cubex1155"); // password protected ap

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
    String client_id = "esp32-client-";
    if (client.connect(client_id.c_str(), "emqx", "public"))
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
 
  
  client.subscribe("cubex/cubex1155");
 

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
      Serial.println(" Cubex1155 got enabled...");
    }

  demon_topic += message.substring(7);
  
  Serial.println();
  Serial.println("-----------------------");
}



void loop() 
{

    if ( ! rfid.PICC_IsNewCardPresent())
    return;
    if (rfid.PICC_ReadCardSerial()) {
    for (byte i = 0; i < 4; i++) {
      tag += rfid.uid.uidByte[i];
    }
    

    
//    tag = "";
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }

  
  if(tag == "871016677"){
        Serial.println(tag);
          char copy[50];
          demon_topic.toCharArray(copy, 50);
          client.publish(copy, "on");
         
        
      }
  
  tag = "";
  
  //Reconnect
  if (!client.connected()) {
    reconnect();
    Serial.println(common_topic);
    Serial.print(demon_topic);
  }
  
  client.loop();
}
