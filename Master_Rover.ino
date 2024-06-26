// master
#include <SoftwareSerial.h>
SoftwareSerial mySerial(19, 18); //A5,A4

const int Relay_brakeR = 15; //電磁Break
const int Relay_brakeL = 14; //電磁Break
const int Relay_LED1 = 10; //前面用LED
const int Relay_LED2 = 9; //前面用LED 
const int LED1 = 12; //判定用基盤上LED
const int LED2 = 11; //判定用基板上LED
const int DIR_PIN_L = 7; //後方左・DIRピン（左側DIR→回路図見る限りこうなっている後方左は間違い？）
const int DIR_PIN_R = 8; //後方右・DIRピン（左側DIR→回路図見る限りこうなっている後方右は間違い？）

//---- 判別用フラグ----//
int flag;

#define SOFT 0
#define RIGID 1
#define NUM_CMD 3 //コマンド数
#define right_lim 20
#define left_lim -20




void setup() {
  //--------シリアル通信準備--------//
  Serial.begin(9600); // start serial for output
  mySerial.begin(4800); // start Software serial for output


  //-----I/O設定-----//
  pinMode(Relay_brakeR, OUTPUT);
  pinMode(Relay_brakeL, OUTPUT);
  pinMode(Relay_LED1, OUTPUT);
  pinMode(Relay_LED2, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(DIR_PIN_L, OUTPUT);
  pinMode(DIR_PIN_R, OUTPUT);

  

  digitalWrite(Relay_brakeR, LOW);
  digitalWrite(Relay_brakeL, LOW);
  digitalWrite(Relay_LED1, LOW);
  digitalWrite(Relay_LED2, LOW);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(DIR_PIN_L, LOW);
  digitalWrite(DIR_PIN_R, LOW);
  
  
}

void loop() {

  if(Serial.available() > 0){   // シリアルポートに何かデータが到着しているか確認

    char line;
    line = Serial.read();  
    mySerial.println(line);

    if(line == 's'){
      Stop();
      
    }else{
      
      if(line == 'd' ){
        Right();
      }else if(line == 'a'){
        Left();
      }else if(line == 'w'){
        Go();
      }else if(line == 'x'){
        Back();
      }
    }
    
    //if (detect == SOFT) Soft();
    //if (detect == RIGID) Rigid();

  }
}
    

//前進
void Go() {
    flag = 1;                       // フラグを1に設定

    digitalWrite(DIR_PIN_L, HIGH);
    digitalWrite(DIR_PIN_R, LOW);
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(Relay_brakeR, HIGH);
    digitalWrite(Relay_brakeL, HIGH);
    digitalWrite(Relay_LED1, HIGH);
    digitalWrite(Relay_LED2, HIGH);
}

//後退
void Back() {
    flag = 2;                       // フラグを2に設定

    digitalWrite(DIR_PIN_L, LOW);
    digitalWrite(DIR_PIN_R, HIGH);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(Relay_LED1, LOW);
    digitalWrite(Relay_LED2, LOW);
    digitalWrite(Relay_brakeR, HIGH);
    digitalWrite(Relay_brakeL, HIGH);
}

//停止
void Stop() {
    flag = 3;                       // フラグを3に設定

    digitalWrite(Relay_brakeR, LOW);
    digitalWrite(Relay_brakeL, LOW);
    digitalWrite(Relay_LED1, LOW);
    digitalWrite(Relay_LED2, LOW);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(DIR_PIN_L, LOW);
    digitalWrite(DIR_PIN_R, LOW);
}

//PWM制御で前進する場合
void PWM_Go() {
    flag = 4;                       // フラグを4に設定

    digitalWrite(DIR_PIN_L, HIGH);
    digitalWrite(DIR_PIN_R, LOW);
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(Relay_brakeR, HIGH);
    digitalWrite(Relay_brakeL, HIGH);
    digitalWrite(Relay_LED1, HIGH);
    digitalWrite(Relay_LED2, HIGH);
}


//PWM制御で後進する場合
void PWM_Back() {
    flag = 5;                       // フラグを4に設定

    digitalWrite(DIR_PIN_L, LOW);
    digitalWrite(DIR_PIN_R, HIGH);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(Relay_LED1, LOW);
    digitalWrite(Relay_LED2, LOW);
    digitalWrite(Relay_brakeR, HIGH);
    digitalWrite(Relay_brakeL, HIGH);
}

//右折
void Right() {
    flag = 6;                       // フラグを5に設定

    digitalWrite(DIR_PIN_L, HIGH);
    digitalWrite(DIR_PIN_R, HIGH);
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(Relay_brakeR, HIGH);
    digitalWrite(Relay_brakeL, HIGH);
    digitalWrite(Relay_LED1, HIGH);
    digitalWrite(Relay_LED2, HIGH);
}

//左折
void Left() {
    flag = 7;                       // フラグを7に設定

    digitalWrite(DIR_PIN_L, LOW);
    digitalWrite(DIR_PIN_R, LOW);
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(Relay_brakeR, HIGH);
    digitalWrite(Relay_brakeL, HIGH);
    digitalWrite(Relay_LED1, HIGH);
    digitalWrite(Relay_LED2, HIGH);
}
