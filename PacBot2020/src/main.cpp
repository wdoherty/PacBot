#include <Arduino.h>

#include "drive_helpers.h"

#define USE_TUNING_SERVER 1

#if(USE_TUNING_SERVER == 1)
#include <WiFi.h>
//#include <AsyncTCP.h>
#include "ESPAsyncWebServer.h"

const char* ssid = "Apt 421";
const char* password = "fear flimsy";

AsyncWebServer server(80);

const char* PARAM_INPUT_1 = "st1_p";
const char* PARAM_INPUT_2 = "st1_n";
const char* PARAM_INPUT_3 = "dy1_p";
const char* PARAM_INPUT_4 = "dy1_n";

const char* PARAM_INPUT_5 = "st2_p";
const char* PARAM_INPUT_6 = "st2_n";
const char* PARAM_INPUT_7 = "dy2_p";
const char* PARAM_INPUT_8 = "dy2_n";

// HTML web page to handle 3 input fields (input1, input2, input3)
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>ESP Input Form</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head><body>
  <form action="/get">
    st1_p: <input type="text" name="st1_p">
    <input type="submit" value="Submit">
  </form><br>
  <form action="/get">
    st1_n: <input type="text" name="st1_n">
    <input type="submit" value="Submit">
  </form><br>
  <form action="/get">
    dy1_p: <input type="text" name="dy1_p">
    <input type="submit" value="Submit">
  </form><br>
  <form action="/get">
    dy1_n: <input type="text" name="dy1_n">
    <input type="submit" value="Submit">
  </form><br>
  <form action="/get">
    st2_p: <input type="text" name="st2_p">
    <input type="submit" value="Submit">
  </form><br>
  <form action="/get">
    st2_n: <input type="text" name="st2_n">
    <input type="submit" value="Submit">
  </form><br>
  <form action="/get">
    dy2_p: <input type="text" name="dy2_p">
    <input type="submit" value="Submit">
  </form><br>
  <form action="/get">
    dy2_n: <input type="text" name="dy2_n">
    <input type="submit" value="Submit">
  </form>
</body></html>)rawliteral";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

#endif


Drive *main_drives[4];

void setup() {
  Serial.begin(1000000);
  setup_drive_system(&main_drives);
  for (int i = 5; i > 0; i--) {
    delay(1000);
    Serial.println(i);
  }

  #if(USE_TUNING_SERVER == 1)
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed!");
    return;
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  delay(3000);
  // Send web page with input fields to client
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  // Send a GET request to <ESP_IP>/get?input1=<inputMessage>
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    String inputParam;
    // GET input1 value on <ESP_IP>/get?input1=<inputMessage>
    if (request->hasParam(PARAM_INPUT_1)) {
      Serial.print("ST1_P\t");
      inputMessage = request->getParam(PARAM_INPUT_1)->value();
      (main_drives[0]->_fric).st_p = inputMessage.toDouble();
    }
    // GET input2 value on <ESP_IP>/get?input2=<inputMessage>
    else if (request->hasParam(PARAM_INPUT_2)) {
      Serial.print("ST1_N\t");
      inputMessage = request->getParam(PARAM_INPUT_2)->value();
      main_drives[0]->_fric.st_n =  inputMessage.toDouble();
    }
    // GET input3 value on <ESP_IP>/get?input3=<inputMessage>
    else if (request->hasParam(PARAM_INPUT_3)) {
      Serial.print("DY1_P\t");
      inputMessage = request->getParam(PARAM_INPUT_3)->value();
      main_drives[0]->_fric.dy_p =  inputMessage.toDouble();
    }
    // GET input3 value on <ESP_IP>/get?input3=<inputMessage>
    else if (request->hasParam(PARAM_INPUT_4)) {
      Serial.print("DY1_N\t");
      inputMessage = request->getParam(PARAM_INPUT_4)->value();
      main_drives[0]->_fric.dy_n =  inputMessage.toDouble();
    }
    // GET input3 value on <ESP_IP>/get?input3=<inputMessage>
    else if (request->hasParam(PARAM_INPUT_5)) {
      Serial.print("ST2_P\t");
      inputMessage = request->getParam(PARAM_INPUT_5)->value();
      main_drives[2]->_fric.st_p =  inputMessage.toDouble();
    }
    // GET input3 value on <ESP_IP>/get?input3=<inputMessage>
    else if (request->hasParam(PARAM_INPUT_6)) {
      Serial.print("ST2_N\t");
      inputMessage = request->getParam(PARAM_INPUT_6)->value();
      main_drives[2]->_fric.st_n =  inputMessage.toDouble();
    }
    // GET input3 value on <ESP_IP>/get?input3=<inputMessage>
    else if (request->hasParam(PARAM_INPUT_7)) {
      Serial.print("DY2_P\t");
      inputMessage = request->getParam(PARAM_INPUT_7)->value();
      main_drives[2]->_fric.dy_p =  inputMessage.toDouble();
    }
    // GET input3 value on <ESP_IP>/get?input3=<inputMessage>
    else if (request->hasParam(PARAM_INPUT_8)) {
      Serial.print("DY2_N\t");
      inputMessage = request->getParam(PARAM_INPUT_8)->value();
      main_drives[2]->_fric.dy_n =  inputMessage.toDouble();
    }
    else {
      inputMessage = "No message sent";
      inputParam = "none";
    }
    Serial.print("SET WITH VALUE: ");
    Serial.println(inputMessage.toDouble());
    request->send_P(200, "text/html", index_html);
  });
  server.onNotFound(notFound);
  server.begin();
  #endif

  set_CL_velocity(1, 100);
  set_CL_velocity(3, 100);
}

void loop() {
  delay(10);
}



