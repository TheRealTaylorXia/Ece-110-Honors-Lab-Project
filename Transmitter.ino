#include <SPI.h>                      //the communication interface with the modem
#include <nRF24L01.h>
#include <RF24.h>                    //the library which helps us to control the radio modem

int msg[5]; //Total number of data to be sent (data package)

//define the flex sensor input pins
int flex_1 = A1; //Thumb
int flex_2 = A2; //Index
int flex_3 = A3; //Middle
int flex_4 = A4; //Ring
int flex_5 = A5; //Pinky

//define variables for flex sensor values
int flex_1_val;
int flex_2_val;
int flex_3_val;
int flex_4_val;
int flex_5_val;

unsigned long currentMillis;
unsigned long prevMillis;
unsigned long txIntervalMillis = 10;

#define CE_PIN 9
#define CSN_PIN 10

RF24 radio(CE_PIN,CSN_PIN);        
                                      
//const uint64_t address = 0xE8E8F0F0E1LL; //the address of the modem, that will receive data from Arduino.
const byte slaveAddress[5] = {'R','x','A','A','A'};

void setup(void){
  Serial.begin(9600);

  //Serial.println("Prosthetic Hand v1.0 starting up...");
  
  radio.begin();                      //it activates the modem.
  radio.setAutoAck(false);
  radio.setDataRate( RF24_250KBPS );
  radio.setRetries(3,5);
  radio.openWritingPipe(slaveAddress);        //sets the address of the receiver to which the program will send data.
  //Serial.println("#RADIO INITIALIZED");
}

void loop(void){
  flex_5_val = analogRead(flex_5); 
  flex_5_val = map(flex_5_val, 270, 480, 180, 0);
  
  flex_4_val = analogRead(flex_4);
  flex_4_val = map(flex_4_val, 190, 500, 180, 0);
 
  flex_3_val = analogRead(flex_3);
  flex_3_val = map(flex_3_val, 200, 470, 180, 0);
 
  flex_2_val = analogRead(flex_2);
  flex_2_val = map(flex_2_val, 125, 400, 180, 0);
  
  flex_1_val = analogRead(flex_1);
  flex_1_val = map(flex_1_val, 100, 390, 180, 0);

  currentMillis = millis();
  if (currentMillis-prevMillis >= txIntervalMillis){
    send();
    prevMillis = millis();
  }
}

void send() {
  boolean sent;
  msg[0] = flex_1_val;
  msg[1] = flex_2_val;
  msg[2] = flex_3_val;
  msg[3] = flex_4_val;
  msg[4] = flex_5_val;
  sent = radio.write(&msg, sizeof(msg));

  if (sent){
  Serial.print(analogRead(flex_1));
  Serial.print(" ");
  Serial.print(msg[0]);
  Serial.println("---THUMB---");

  Serial.print(analogRead(flex_2));
  Serial.print(" ");
  Serial.print(msg[1]);
  Serial.println("---INDEX---");

  Serial.print(analogRead(flex_3));
  Serial.print(" ");
  Serial.print(msg[2]);
  Serial.println("---MIDDLE---");

  Serial.print(analogRead(flex_4));
  Serial.print(" ");
  Serial.print(msg[3]);
  Serial.println("---RING---");

  Serial.print(analogRead(flex_5));
  Serial.print(" ");
  Serial.print(msg[4]);
  Serial.println("---PINKY---");
  }
}
