#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

const char* ssid = "VIETTEL_DucThuy";
const char* password = "88888888";
const char* mqtt_server = "192.168.2.178";
const int mqtt_port = 1883;
const char* mqtt_user = "ducanh";
const char* mqtt_pass = "ducanh";
const char* student_id = "10124034"; // Đã cập nhật mã sinh viên mới
const char* mqtt_topic = "iot/lab1/10124034/sensor";

// Tạo 2 topic riêng biệt cho nhiệt độ và độ ẩm
const char* topic_temp = "iot/lab1/10124034/temperature";
const char* topic_hum  = "iot/lab1/10124034/humidity";

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void reconnect() {
  while (!client.connected()) {
    String clientId = "ESP32S3-" + String(student_id);
    if (client.connect(clientId.c_str(), mqtt_user, mqtt_pass)) {
      Serial.println("MQTT connected");
    } else {
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Tạo giá trị ngẫu nhiên
  float temp = random(250, 350) / 10.0;
  float hum = random(400, 800) / 10.0;

  // Gửi trực tiếp giá trị lên 2 topic khác nhau
  client.publish(topic_temp, String(temp).c_str());
  client.publish(topic_hum, String(hum).c_str());
  
  Serial.print("Sent Temp: "); Serial.print(temp);
  Serial.print(" | Sent Hum: "); Serial.println(hum);
  
  delay(5000);
}