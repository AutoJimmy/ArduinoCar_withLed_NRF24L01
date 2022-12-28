#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(4,3); //CE = 4 dan CSN = 3
const byte address[6] = "00001";

int motor1N1 = 7;
int motor1N2 = 8;
int motor2N1 = 9;
int motor2N2 = 10;

int led_pin = 6;

void setup() {
  // put your setup code here, to run once:
  pinMode(led_pin, OUTPUT);
  pinMode(motor1N1, OUTPUT);
  pinMode(motor1N2, OUTPUT);
  pinMode(motor2N1, OUTPUT);
  pinMode(motor2N2, OUTPUT);
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0,address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.startListening();
}

void loop() {  
    char text[32] = "";  
    if (radio.available()) {
      radio.read(&text, sizeof(text));
      String transData = String(text);          
      //Serial.println(transData);
      if (transData == "forward") {
           digitalWrite(motor1N1, HIGH); //roda kiri forward
           digitalWrite(motor1N2, LOW);
           digitalWrite(motor2N1, HIGH); //roda kanan forward
           digitalWrite(motor2N2, LOW);
           transData="";
        }
      else if (transData == "back") {
          digitalWrite(motor1N1, LOW); //roda kiri reverse
          digitalWrite(motor1N2, HIGH);
          digitalWrite(motor2N1, LOW); //roda kanan reverse
          digitalWrite(motor2N2, HIGH);
          transData="";
        }     
      else if (transData == "right") {
          digitalWrite(motor1N1, LOW); //roda kiri reverse
          digitalWrite(motor1N2, HIGH);
          digitalWrite(motor2N1, HIGH); //roda kanan forward
          digitalWrite(motor2N2, LOW);
          transData="";
        }
      else if (transData == "left") {
          digitalWrite(motor1N1, HIGH); //roda kiri forward
          digitalWrite(motor1N2, LOW);
          digitalWrite(motor2N1, LOW); //roda kanan reverse
          digitalWrite(motor2N2, HIGH);
          transData="";
        }         
      else if (transData == "stop") {
          digitalWrite(motor1N1, LOW); //roda kiri
          digitalWrite(motor1N2, LOW);
          digitalWrite(motor2N1, LOW); //roda kanan
          digitalWrite(motor2N2, LOW);
          transData="";
        }
    
      //Turn the led on if radio is available   
      if(transData == "onled"){
          digitalWrite(led_pin, HIGH);
          transData="";        
        }
      else if(transData == "offled"){
          digitalWrite(led_pin, LOW);
          transData="";        
        }
     }              
}


