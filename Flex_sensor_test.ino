#include <Servo.h>

int flexs = A0;
int data = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(flexs, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  data = analogRead(flexs);
  Serial.print("Flex: ");
  Serial.println(data);
  delay(1000);
}

//Ranges (From right to left)
//Flex 5: 500 - 260
//Flex 4: 520 - 200
//Flex 3: 500 - 210
//Flex 2: 450 - 140
//Flex 1: 400 - 100
