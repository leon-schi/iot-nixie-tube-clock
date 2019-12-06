#include <ESP8266WiFi.h>

#include "time_controller.h"
#include "time_server.h"
#include "wifi_credentials.h"

ClockController* clockController;
ClockServer* server;

void setup() {
    Serial.begin(9600);
    Serial.println();

    WiFi.begin(SSID, PASS);

    Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(100);
        Serial.print(".");
    }
    Serial.println();

    Serial.print("Connected, IP address: ");
    Serial.println(WiFi.localIP());

    clockController = new ClockController(D0, D2, D1, 32);
    server = new ClockServer(clockController);
}

void loop() {
    clockController->update();
    server->handleClient();
    delay(30);
}