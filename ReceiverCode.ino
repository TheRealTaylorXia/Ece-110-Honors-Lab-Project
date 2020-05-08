#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

#define CE_PIN  9
#define CSN_PIN 10

const byte address[5] = "00001";
RF24 radio(CE_PIN, CSN_PIN); // create radio

int flexVals[5]; // data to receive from transmitter, mapped values from flex sensors
bool newData = false;

Servo th, i, m, r, p;

void setup() {

    // Initialize radio
    Serial.begin(9600);
    radio.begin();
    radio.setDataRate( RF24_250KBPS );
    radio.setAutoAck(false);
    radio.openReadingPipe(1, address);
    radio.startListening();

    // Setup for motors
    p.attach(2);
    r.attach(3);
    m.attach(4);
    i.attach(5);
    th.attach(6);
}

void loop() {
    loadData();
    moveMotors();
    //delay(100);
}

void loadData() {
    if ( radio.available() ) {
        radio.read( &flexVals, sizeof(flexVals) );
        newData = true;
    } //else Serial.println("radio unavailable");
}

void moveMotors() {
    if (newData) {

        Serial.print("THUMB: ");
        Serial.println(flexVals[0]);
        Serial.print("INDEX: ");
        Serial.println(flexVals[1]);
        Serial.print("MIDDLE: ");
        Serial.println(flexVals[2]);
        Serial.print("RING: ");
        Serial.println(flexVals[3]);
        Serial.print("PINKY: ");
        Serial.println(flexVals[4]);
        Serial.println("----------------------");

        moveFinger(th, flexVals[0]);
        moveFinger(i, flexVals[1]);
        moveFinger(m, flexVals[2]);
        moveFinger(r, flexVals[3]);
        moveFinger(p, flexVals[4]);
        
        newData = false;
    }
}

void moveFinger(Servo s, int angle) {

    if(angle < 0) {
      s.write(0);
    } else if (angle > 180) {
      s.write(180);  
    } else {
      s.write(angle);
    }
    
}
