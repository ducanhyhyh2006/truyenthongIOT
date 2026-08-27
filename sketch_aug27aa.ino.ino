void setup() {
  pinMode(2, OUTPUT);  // LED trên
  pinMode(3, OUTPUT);  // LED giữa
  pinMode(4, OUTPUT);  // LED dưới
}

void loop() {
  // Chạy từ trên xuống
  digitalWrite(2, HIGH);
  delay(300);
  digitalWrite(2, LOW);

  digitalWrite(3, HIGH);
  delay(300);
  digitalWrite(3, LOW);

  digitalWrite(4, HIGH);
  delay(300);
  digitalWrite(4, LOW);

  // Chạy từ dưới lên
  digitalWrite(3, HIGH);
  delay(300);
  digitalWrite(3, LOW);

  digitalWrite(2, HIGH);
  delay(300);
  digitalWrite(2, LOW);
}