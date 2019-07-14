int pulse;
long timer,esc_timer;
void setup() {
  // put your setup code here, to run once:
  TWBR = 12;
  DDRD |= 00010000;
  PORTD |= 00010000;
  delayMicroseconds(1000);
  PORTD &= 11101111;
  delay(3);
  pulse = 1000;             //initial pulse
  timer = micros();
}

void loop() {
  // put your main code here, to run repeatedly:
  while(timer - micros() < 4000);
  timer = micros();
  while(Serial.available()>0){
    Serial.print("Input Pulse (1000-2000): ");
    while(pulse < 1000 && pulse > 2000){
      pulse = Serial.read();
    }
  }
  esc_timer = timer + pulse;
  PORTD |= 00010000;
  while(PORTD >= 16){
    timer = micros();
    if(timer <= esc_timer)PORTD &= 11101111;
  }
}
