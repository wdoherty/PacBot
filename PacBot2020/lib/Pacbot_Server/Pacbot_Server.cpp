#include "Pacbot_Server.h"
#include "html_text.h"

Pacbot_Server::Pacbot_Server(const char* ssid, const char* pass, Drive* drive_objs[4]) {
    WiFi.softAP(ssid, pass);

    #if (SHOW_WIFI_IP == 1)
    IPAddress IP = WiFi.softAPIP();
    Serial.print("\nAP IP Address: ");
    Serial.println(IP);
    #endif

    server = new AsyncWebServer(80);

    for (int i = 0; i < 4; i++) drives[i] = drive_objs[i];

    server->on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/html", "root_html");
    });
    
    server->on("/config", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/html", this->config_html());
    });

    server->on("/config/get", HTTP_GET, this->update_configs(request));

    server->onNotFound(notFound);
    server->begin();
}

void Pacbot_Server::notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}


#define NUM_CONFIGS 8
char configs[] = {"drive", "stp", "dyp", "stn", "dyn", "kp", "ki", "kd"};
void Pacbot_Server::update_configs(AsyncWebServerRequest *request) {

  if (!request->hasParam(configs[0])) return;
  int drive_num = request->getParam(configs[0])->value().toInt();

  double old_kp, old_ki, old_kd;

  for (int idx = 1; idx < NUM_CONFIGS; idx++) {
    if (request->hasParam(configs[idx])) {
      double newVal = request->getParam(configs[idx])->value().toDouble();

      switch(configs[idx]) {
        case("stp"):
          drives[drive_num]->_fric.st_p = newVal;
          break;
        case("stn"):
          drives[drive_num]->_fric.st_n = newVal;
          break;
        case("dyp"):
          drives[drive_num]->_fric.dy_p = newVal;
          break;
        case("dyn"):
          drives[drive_num]->_fric.dy_n = newVal;
          break;
        case("kp"):
          old_ki = drives[drive_num]->_ki;
          old_kd = drives[drive_num]->_kd;
          drives[drive_num]->_kp = newVal;
          drives[drive_num]->controller->SetTunings(newVal, old_ki, old_kd);
          break;
        case("ki"):
          old_kp = drives[drive_num]->_kp;
          old_kd = drives[drive_num]->_kd;
          drives[drive_num]->_ki = newVal;
          drives[drive_num]->controller->SetTunings(old_kp, newVal, old_kd);
          break;
        case("kd"):
          old_kp = drives[drive_num]->_kp;
          old_ki = drives[drive_num]->_ki;
          drives[drive_num]->_kd = newVal;
          drives[drive_num]->controller->SetTunings(old_kp, old_ki, newVal);
          break;
        default:
          break;
      }
    }
  }
  
  request->send_P(200, "text/html", config_html());
}

#define DOUBLE_LEN  10
char* Pacbot_Server::config_html() {
  drive_config_t configs[4];

  for (int i = 0; i < 4; i++) {
    configs[i].stp = drives[i]->_fric.st_p;
    configs[i].stn = drives[i]->_fric.st_n;
    configs[i].dyp = drives[i]->_fric.dy_p;
    configs[i].dyn = drives[i]->_fric.dy_n;
    configs[i].kp = drives[i]->_kp;
    configs[i].ki = drives[i]->_ki;
    configs[i].kd = drives[i]->_kd;
  }
  
  char* resp = new char [2298+(7*DOUBLE_LEN)];
  sprintf(resp, DEFAULT_CONFIG_HTML, configs[0].stp, configs[0].dyp, configs[0].stn, configs[0].dyn, configs[0].kp, configs[0].ki, configs[0].kd);

  return resp;
}
