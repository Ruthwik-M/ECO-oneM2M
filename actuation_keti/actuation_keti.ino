#include<HTTPClient.h>
#include <WiFi.h>

HTTPClient http;

#define MAIN_SSID "JioFi3_127A1C"
#define MAIN_PASS "0rn36u30sm"

#define CSE_IP      "192.168.255.64"
#define CSE_PORT    8080
#define HTTPS     false
#define OM2M_ORGIN    "admin:admin"
#define OM2M_MN     "/~/in-cse/in-name/"
#define OM2M_AE     "AE-Misc"
#define OM2M_DATA_CONT  "OC-KH95-05/Data"
#define OM2M_Monitor_CONT  "OC-KH95-05/Monitor_cont"
#define OM2M_Sub_CONT  "OC-KH95-00/Data"

WiFiServer server(8000);
int subscribe_to_containers();

int over_ride = 0;
int Light_set_1 = 16 ;                    
int Light_set_2 = 17 ;  
int status_node = 0;

void setup() {
  Serial.begin(115200);
   pinMode(Light_set_1, OUTPUT);
  pinMode(Light_set_2, OUTPUT);
  WiFi.begin(MAIN_SSID,MAIN_PASS);
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());
  server.begin();
  //int x = subscribe_to_containers();
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client = server.available();
  if(client){
  //Serial.println("in the loop");
  String w=client.readString();
  int a=w.indexOf("switchon");
  int b=w.indexOf("switchoff");
  int c=w.indexOf("Override ON");
  int d=w.indexOf("Override OFF");

  if(c>0){
    over_ride = 1;
    digitalWrite(Light_set_1,LOW);
    digitalWrite(Light_set_2,LOW);
    status_node = 1;
    }
   if(d>0){
    over_ride = 0;
    digitalWrite(Light_set_1,HIGH);
    digitalWrite(Light_set_2,HIGH);
    status_node = 0;
    }

    if(a>0 & over_ride==0)
    {
    digitalWrite(Light_set_1,LOW);
    digitalWrite(Light_set_2,LOW);
    status_node = 1;
      }

    if(b>0 &over_ride==0){
     
    digitalWrite(Light_set_1,HIGH);
    digitalWrite(Light_set_2,HIGH);
    status_node = 0;
      }  
  Serial.println("status");
  Serial.println(status_node);
  client.flush();
  // Send HTTP response to the client
  String s = "HTTP/1.1 200 OK\r\n";
  client.print(s);
  
  }
  delay(100);
  Serial.println("done");
}

int subscribe_to_containers(){

  String server="http://" + String() + CSE_IP + ":" + String() + CSE_PORT + String()+OM2M_MN;
   http.begin(server + String() +OM2M_AE + "/" + OM2M_Monitor_CONT + "/");
   delay(3000);
   http.addHeader("X-M2M-Origin", OM2M_ORGIN);
   http.addHeader("Content-Type", "application/json;ty=23");
   http.addHeader("Content-Length", "100");
   String req_data = String() + "{\"m2m:sub\": {"
     + "\"rn\": \"led_subscription\""+","
     + "\"nu\": \"" + "http://"+String(WiFi.localIP())+":"+"8000" + "\","
     + "\"nct\": \"2\""
     + "}}";
   int x=http.POST(req_data);
   delay(3000);
   Serial.println(x);
   http.end();
   //Lamp-1 Object
   delay(3000);
   http.begin(server + String() +OM2M_AE + "/" + OM2M_Sub_CONT + "/");
   delay(3000);
   http.addHeader("X-M2M-Origin", OM2M_ORGIN);
   http.addHeader("Content-Type", "application/json;ty=23");
   http.addHeader("Content-Length", "100");
   req_data = String() + "{\"m2m:sub\": {"  
     + "\"rn\": \"led_sub_test\""+","
     + "\"nu\": \"" + "http://"+String(WiFi.localIP())+":"+"8000" + "\","
     + "\"nct\": \"2\""
     + "}}";
   x =http.POST(req_data);
   Serial.println(x);
   http.end();
  
   return 5;
  }
