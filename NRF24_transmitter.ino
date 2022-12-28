#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(10, 9); //atau, CE = 4 dan CSN = 3
const byte address[6] = "00001";

#define JoyStick_X_PIN     A1
#define JoyStick_Y_PIN     A0

int led_pin = 8;
boolean btn_led = 0;

void setup() {
  pinMode(led_pin, INPUT);   
  Serial.begin(9600);  
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.stopListening();
}

void loop() {
  int posisiX = analogRead(JoyStick_X_PIN);
  int posisiY = analogRead(JoyStick_Y_PIN);
  btn_led = digitalRead(led_pin);

  //when led button pushed
  if(btn_led == HIGH){
      const char text[] = "onled";
      radio.write(&text, sizeof(text));
  }
  else if(btn_led == LOW){
      const char text[] = "offled";
      radio.write(&text, sizeof(text));
  }
  
  if (posisiY >= 700 && posisiY <= 1023) {
    const char text[] = "forward";
    radio.write(&text, sizeof(text));
  }
  else if (posisiY >= 0 && posisiY <= 450) {
    const char text[] = "back";
    radio.write(&text, sizeof(text));
  }
  else if (posisiX >= 700 && posisiX <= 1023) {
    const char text[] = "right";
    radio.write(&text, sizeof(text));
  }
  else if (posisiX >= 0 && posisiX <= 450) {
    const char text[] = "left";
    radio.write(&text, sizeof(text));
  } 
  else {
    const char text[] = "stop";
    radio.write(&text, sizeof(text));    
  }
  delay(100); //klap klik lampunya
}
