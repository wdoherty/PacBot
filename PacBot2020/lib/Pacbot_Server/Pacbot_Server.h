
#ifndef PACBOT_SERVER_H
#define PACBOT_SERVER_H

#include <WiFi.h>
#include "ESPAsyncWebServer.h"
#include "Drive.h"

#define SHOW_WIFI_IP    1

typedef struct drive_config {
    double stp;
    double stn;
    double dyp;
    double dyn;
    double kp;
    double ki;
    double kd;
} drive_config_t;

// DEFAULT HAS IP OF 192.168.4.1
class Pacbot_Server {
    public:
        Pacbot_Server(const char* ssid, const char* pass, Drive *drive_objs[4]);

        static void notFound(AsyncWebServerRequest *request);

        static char* config_html();
        static void update_configs(AsyncWebServerRequest *request);

        AsyncWebServer* server;
};

#endif
