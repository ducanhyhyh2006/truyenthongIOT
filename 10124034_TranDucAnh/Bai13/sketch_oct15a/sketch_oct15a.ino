
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif

#include <WiFiUdp.h>
#include <coap-simple.h>

/* ========== CONFIG ========== */

// Thay bằng ten va mat khau Wi-Fi cua ban
const char* WIFI_SSID = "TVQQ";
const char* WIFI_PASS = "123456789";

// Dia chi IP cua may chay CoAP Server Node.js
IPAddress coap_server_ip(172, 18, 187, 132);
const int coap_port = 5683;

// Tai nguyen CoAP
const char* coap_resource = "sensor/temp";

// Gui du lieu moi 5 giay
const unsigned long SEND_INTERVAL = 5000;

/* ========== COAP CLIENT ========== */

WiFiUDP udp;
Coap coap(udp);
// Token CoAP dung de nhan dien yeu cau
const uint8_t token[] = {0x01, 0x02};
unsigned long lastSend = 0;

/* ========== WIFI ========== */

void setup_wifi() {
  Serial.print("Connecting to WiFi");

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");

  }

  Serial.println();
  Serial.println("WiFi connected");

  Serial.print("ESP IP: ");
  Serial.println(WiFi.localIP());

  Serial.print("CoAP Server IP: ");
  Serial.println(coap_server_ip);
}

/* ========== SETUP ========== */

void setup() {
  Serial.begin(115200);
  delay(1000);

  setup_wifi();

  coap.start();

  Serial.println("CoAP client started");
}

/* ========== LOOP ========== */

void loop() {
  // Gui lai neu Wi-Fi bi mat ket noi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi disconnected. Reconnecting...");
    WiFi.disconnect();
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

    Serial.println();
    Serial.println("WiFi reconnected");
  }

  // Gui du lieu moi 5 giay
  if (millis() - lastSend >= SEND_INTERVAL) {
    lastSend = millis();

    // Payload mau
    String payload = "temp=30.5";

    Serial.print("Sending CoAP NON POST to /");
    Serial.println(coap_resource);

    Serial.print("Payload: ");
    Serial.println(payload);

    coap.send(
      coap_server_ip,
      coap_port,
      coap_resource,
      COAP_NONCON,  // NON message
      COAP_POST,    // POST method
      token,        // Token
      sizeof(token),
      (const uint8_t*)payload.c_str(),
      payload.length()
    );
  }

  // Xu ly cac goi CoAP den
  coap.loop();

  delay(10);
}
