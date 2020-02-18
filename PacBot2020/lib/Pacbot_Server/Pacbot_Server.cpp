#include "Pacbot_Server.h"
#include "html_text.h"

Drive *server_drives[4];

Pacbot_Server::Pacbot_Server(const char* ssid, const char* pass, Drive *drive_objs[4]) {
    WiFi.softAP(ssid, pass);

    #if (SHOW_WIFI_IP == 1)
    IPAddress IP = WiFi.softAPIP();
    Serial.print("\nAP IP Address: ");
    Serial.println(IP);
    #endif

    server = new AsyncWebServer(80);

    for (int i = 0; i < 4; i++) server_drives[i] = drive_objs[i];

    server->on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/html", ROOT_HTML);
    });
    
    server->on("/config", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/html", config_html());
    });

    server->on("/get", HTTP_GET, update_configs);

    server->on("/config_stylesheet.css", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/css", DEFAULT_CONFIG_STYLE);
    });

    server->onNotFound(notFound);
    server->begin();
}

void Pacbot_Server::notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}


#define NUM_CONFIGS 8
char configs[NUM_CONFIGS][3] = {"dv", "sp", "sn", "dp", "dn", "kp", "ki", "kd"};

void Pacbot_Server::update_configs(AsyncWebServerRequest *request) {

  if (!request->hasParam(configs[0])) return;
  int drive_num = request->getParam(configs[0])->value().toInt()-1;

  double old_kp, old_ki, old_kd;

  for (int idx = 1; idx < NUM_CONFIGS; idx++) {

    if (request->hasParam(configs[idx])) {
      double newVal = request->getParam(configs[idx])->value().toDouble();

      switch(idx) {
        case(1):
          server_drives[drive_num]->_fric.st_p = newVal;
          break;
        case(2):
          server_drives[drive_num]->_fric.st_n = newVal;
          break;
        case(3):
          server_drives[drive_num]->_fric.dy_p = newVal;
          break;
        case(4):
          server_drives[drive_num]->_fric.dy_n = newVal;
          break;
        case(5):
          old_ki = server_drives[drive_num]->_ki;
          old_kd = server_drives[drive_num]->_kd;
          server_drives[drive_num]->_kp = newVal;
          server_drives[drive_num]->controller->SetTunings(newVal, old_ki, old_kd);
          break;
        case(6):
          old_kp = server_drives[drive_num]->_kp;
          old_kd = server_drives[drive_num]->_kd;
          server_drives[drive_num]->_ki = newVal;
          server_drives[drive_num]->controller->SetTunings(old_kp, newVal, old_kd);
          break;
        case(7):
          old_kp = server_drives[drive_num]->_kp;
          old_ki = server_drives[drive_num]->_ki;
          server_drives[drive_num]->_kd = newVal;
          server_drives[drive_num]->controller->SetTunings(old_kp, old_ki, newVal);
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
    configs[i].stp = server_drives[i]->_fric.st_p;
    configs[i].stn = server_drives[i]->_fric.st_n;
    configs[i].dyp = server_drives[i]->_fric.dy_p;
    configs[i].dyn = server_drives[i]->_fric.dy_n;
    configs[i].kp = server_drives[i]->_kp;
    configs[i].ki = server_drives[i]->_ki;
    configs[i].kd = server_drives[i]->_kd;
  }
  
  char* resp = new char [2298+(7*DOUBLE_LEN)];
  sprintf(resp, DEFAULT_CONFIG_HTML, configs[0].stp, configs[0].dyp, configs[0].stn, configs[0].dyn, configs[0].kp, configs[0].ki, configs[0].kd);

  return resp;
}
