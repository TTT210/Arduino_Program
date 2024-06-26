#include <DHT.h>
#include <DHT_U.h>
#include "DHT.h" //ライブラリインクルード
#define DHT_Pin 15 //DHT11のDATAピンを定義
#define DHT_Type DHT11 //センサの型番定義　DHT11,DHT22など
#include <Arduino.h>
#include <Wire.h>
#include "SparkFun_MMA8452Q.h"

MMA8452Q accel;

int data = 0;

const int PWMA_1 = 3;     // Front Motor (left)
const int AIN1_1 = 2;
const int AIN2_1 = 4;
                        // Front  Motor (right)
const int PWMB_1 = 6;
const int BIN1_1 = 5;
const int BIN2_1 = 7;

const int PWMA_2 = 9;     // Rear Motor (left)
const int AIN1_2 = 8;
const int AIN2_2 = 10;
                        // Rear  Motor (right)
const int PWMB_2 = 11;
const int BIN1_2 = 12;
const int BIN2_2 = 13;

void setup()
{
                        // Front Motor (left) : set all pins as output
  pinMode(AIN1_1, OUTPUT);
  pinMode(AIN2_1, OUTPUT);
  pinMode(PWMA_1, OUTPUT);

                        // Front Motor (right) : set all pins as output
  pinMode(BIN1_1, OUTPUT);
  pinMode(BIN2_1, OUTPUT);
  pinMode(PWMB_1, OUTPUT);
                        // Rear Motor (left) : set all pins as output
  pinMode(AIN1_2, OUTPUT);
  pinMode(AIN2_2, OUTPUT);
  pinMode(PWMA_2, OUTPUT);

                        // Rear Motor (right) : set all pins as output
  pinMode(BIN1_2, OUTPUT);
  pinMode(BIN2_2, OUTPUT);
  pinMode(PWMB_2, OUTPUT);

  Serial.begin(9600);
  Wire.begin();

  if (accel.begin() == false) {
    Serial.println("Not Connected. Please check connections and read the hookup guide.");
    while (1);
  }
}

void loop() {
  if (Serial.available() > 0) {
    data = Serial.read();//シリアル通信で受け取ったデータを読み込む
  }
    if (data == '0') { //停止
    digitalWrite(AIN1_1, LOW);
    digitalWrite(AIN2_1, LOW);
    analogWrite(PWMA_1, 0);
      
    digitalWrite(BIN1_1, LOW);
    digitalWrite(BIN2_1, LOW);
    analogWrite(PWMB_1, 0);
      
    digitalWrite(AIN1_2, LOW);
    digitalWrite(AIN2_2, LOW);
    analogWrite(PWMA_2, 0);
      
    digitalWrite(BIN1_2, LOW);
    digitalWrite(BIN2_2, LOW);
    analogWrite(PWMB_2, 0);
  
  } else if (data == '1') {//前進
    delay(1000);
    digitalWrite(AIN1_1, HIGH);
    digitalWrite(AIN2_1, LOW);
    analogWrite(PWMA_1, 150);
        
    digitalWrite(BIN1_1, LOW);
    digitalWrite(BIN2_1, HIGH);
    analogWrite(PWMB_1, 150);
        
    digitalWrite(AIN1_2, HIGH);
    digitalWrite(AIN2_2, LOW);
    analogWrite(PWMA_2, 150);
        
    digitalWrite(BIN1_2, LOW);
    digitalWrite(BIN2_2, HIGH);
    analogWrite(PWMB_2, 150);


    for (int i=0; i<200; i++) {
    if (accel.available()) {
    float ax = accel.getCalculatedX();
    float az = accel.getCalculatedZ();
    float angle = atan2(ax, az) * 180.0 / PI;

    Serial.print(angle, 3);
    Serial.println();
  }
  }
  }
}
