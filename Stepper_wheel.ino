// ライブラリ使用宣言
#include <Stepper.h>
 
// オブジェクト生成
Stepper stepper1( 2048, 8, 10, 9, 11 );

int data = 0;
 
void setup() {
  // put your setup code here, to run once:
  // 1分間当たりの回転数設定
  stepper1.setSpeed( 5 );
  Serial.begin(9600);
}
 
void loop() {
  if (Serial.available() > 0) {
    data = Serial.read();//シリアル通信で受け取ったデータを読み込む
  }
  if (data == '0') {
  // 出力停止
  digitalWrite(8,  LOW); 
  digitalWrite(10,  LOW); 
  digitalWrite(9, LOW); 
  digitalWrite(11, LOW); 
  } else if (data == '1') {
  // put your main code here, to run repeatedly:
  // 1/2（180度）反転させる
  stepper1.step( 1024 );    
  } else if (data == '2') {
  // 1/4（90度）反転させる
  stepper1.step( 512 );
  } else if (data == '3') {
  // 1/8（45度）反転させる
  stepper1.step( 256 );
  } else if (data == '4') {
  // 1/9（40度）反転させる
  stepper1.step( 227.56 );
  } else if (data == '5') {
  // 1/12（30度）反転させる
  stepper1.step( 170.67 );
  } else if (data == '6') {
  // 1/18（20度）反転させる
  stepper1.step( 113.78 );
  } else if (data == '7') {
  // 1/36（10度）反転させる
  stepper1.step( 56.89 );
  } else if (data == '8') {
  // 1/72（5度）反転させる
  stepper1.step( 28.44 );
  } 
}
