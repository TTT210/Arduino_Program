#include <DHT.h>
#include <DHT_U.h>
#include "DHT.h" //ライブラリインクルード
#define DHT_Pin 15 //DHT11のDATAピンを定義
#define DHT_Type DHT11 //センサの型番定義　DHT11,DHT22など

DHT dht(DHT_Pin, DHT_Type); //センサ初期化

/* 計測値設定 */
float humidity = 0.0f; //湿度
float tempC = 0.0f; //摂氏温度

int TRIG = 16;
int ECHO = 17;

double duration = 0;
double distance = 0;



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

  pinMode(ECHO, INPUT);
  pinMode(TRIG, OUTPUT);

  Serial.begin(9600);
  dht.begin(); //温湿度センサー開始
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

    humidity = dht.readHumidity(); //湿度の読み出し
    tempC = dht.readTemperature(); //温度の読み出し 摂氏
    
    Serial.print("湿度: ");
    Serial.print(humidity);
    Serial.println("[%]");
    Serial.print("温度: "); 
    Serial.print(tempC);
    Serial.println("[℃]");

    digitalWrite(TRIG, LOW); 
    delayMicroseconds(2); 
    digitalWrite( TRIG, HIGH );
    delayMicroseconds( 10 ); 
    digitalWrite( TRIG, LOW );
    duration = pulseIn( ECHO, HIGH ); // 往復にかかった時間が返却される[マイクロ秒]

    if (duration > 0) {
    duration = duration / 2; // 往路にかかった時間
    distance = duration * (331.5+0.6*humidity) * 100 / 1000000;
    Serial.print("Distance:");
    Serial.print(distance);
    Serial.println(" cm");
    }

    delay(200);
  
  } else if (data == '1') {//前進
    digitalWrite(AIN1_1, LOW);
    digitalWrite(AIN2_1, HIGH);
    analogWrite(PWMA_1, 150);
        
    digitalWrite(BIN1_1, HIGH);
    digitalWrite(BIN2_1, LOW);
    analogWrite(PWMB_1, 150);
        
    digitalWrite(AIN1_2, HIGH);
    digitalWrite(AIN2_2, LOW);
    analogWrite(PWMA_2, 150);
        
    digitalWrite(BIN1_2, HIGH);
    digitalWrite(BIN2_2, LOW);
    analogWrite(PWMB_2, 150);
    
  } else if (data == '2') {//旋回(左前)
    digitalWrite(AIN1_1, LOW);
    digitalWrite(AIN2_1, HIGH);
    analogWrite(PWMA_1, 25);
        
    digitalWrite(BIN1_1, HIGH);
    digitalWrite(BIN2_1, LOW);
    analogWrite(PWMB_1, 50);
        
    digitalWrite(AIN1_2, HIGH);
    digitalWrite(AIN2_2, LOW);
    analogWrite(PWMA_2, 25);
        
    digitalWrite(BIN1_2, HIGH);
    digitalWrite(BIN2_2, LOW);
    analogWrite(PWMB_2, 50);

  } else if (data == '3') {//旋回(右前)
    digitalWrite(AIN1_1, LOW);
    digitalWrite(AIN2_1, HIGH);
    analogWrite(PWMA_1, 50);
        
    digitalWrite(BIN1_1, HIGH);
    digitalWrite(BIN2_1, LOW);
    analogWrite(PWMB_1, 25);
        
    digitalWrite(AIN1_2, HIGH);
    digitalWrite(AIN2_2, LOW);
    analogWrite(PWMA_2, 50);
        
    digitalWrite(BIN1_2, HIGH);
    digitalWrite(BIN2_2, LOW);
    analogWrite(PWMB_2, 25);

  } else if (data == '4') {//左回転
    digitalWrite(AIN1_1, LOW);
    digitalWrite(AIN2_1, HIGH);
    analogWrite(PWMA_1, 0);
        
    digitalWrite(BIN1_1, HIGH);
    digitalWrite(BIN2_1, LOW);
    analogWrite(PWMB_1, 50);
        
    digitalWrite(AIN1_2, HIGH);
    digitalWrite(AIN2_2, LOW);
    analogWrite(PWMA_2, 0);
        
    digitalWrite(BIN1_2, HIGH);
    digitalWrite(BIN2_2, LOW);
    analogWrite(PWMB_2, 50);
    
  } else if (data == '5') {//右回転
    digitalWrite(AIN1_1, LOW);
    digitalWrite(AIN2_1, HIGH);
    analogWrite(PWMA_1, 50);
        
    digitalWrite(BIN1_1, HIGH);
    digitalWrite(BIN2_1, LOW);
    analogWrite(PWMB_1, 0);
        
    digitalWrite(AIN1_2, HIGH);
    digitalWrite(AIN2_2, LOW);
    analogWrite(PWMA_2, 50);
        
    digitalWrite(BIN1_2, HIGH);
    digitalWrite(BIN2_2, LOW);
    analogWrite(PWMB_2, 0);
    
  } else if (data == '6') {//後退
    digitalWrite(AIN1_1, HIGH);
    digitalWrite(AIN2_1, LOW);
    analogWrite(PWMA_1, 50);
        
    digitalWrite(BIN1_1, LOW);
    digitalWrite(BIN2_1, HIGH);
    analogWrite(PWMB_1, 50);
        
    digitalWrite(AIN1_2, LOW);
    digitalWrite(AIN2_2, HIGH);
    analogWrite(PWMA_2, 50);
        
    digitalWrite(BIN1_2, LOW);
    digitalWrite(BIN2_2, HIGH);
    analogWrite(PWMB_2, 50);
  }
}
