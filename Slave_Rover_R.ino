// 右
#include <SoftwareSerial.h>
SoftwareSerial mySerial(18, 19);  //A4 A5
# include <MsTimer2.h>


const int PWM_PIN = 9;  // for Motor driver and PWM
const int DIR_PIN = 8;  //Direction用（右側車輪）
const int LED = 14;     //基板上判定用

volatile int recieve_key = 1;

//---- モータの物性値 -----//
int gear_ratio = 40;  // モータのギア比
int enc_1rotaly_per_Pulse = 100 ;  // エンコーダ側の一回転当たりのパルス数

//---- PID制御パラメータ ----//
const float Kp = 1;
const float Ki = 0.0005;
const float Kd = 0.001;
volatile long duty = 0;
const int initialDuty = 40;
const int turnDuty = 100;
const int rightDuty = 30;
const int leftDuty = 100;

volatile float P, I, D, preP = 0;
float target_rpm =9 ;  // 目標値の回転速度（RPM)
volatile long Right_duty = 10;
volatile long Left_duty = 20;

//---- 区切り時間 ----//
float deltaT = 0.2;       // PID制御のための微小時間（ΔT）、単位[s]
int deltaT_ms = 200;    // PID制御のための微小時間（ΔT）、単位[ms]
volatile long unit_Time = 1 / deltaT;   // 単位時間

//---- 測定値 ----//
volatile float count_pulse;           // カウントしたパルスを格納
volatile float vol_rpm;               // 現在のRPM
volatile int count_pulse_per_1rotaly; // 1回転当たりのパルス数

//---- 判別用フラグ----//
int flag = 0;
int Pre_Word = 0;



void setup() {
  //-----I/O設定-----//
  pinMode(PWM_PIN, OUTPUT);    //PWMPIN
  pinMode(2, INPUT_PULLUP);   // 割り込み用・エンコーダA相読み込み用、プルアップ抵抗必須なためinput_pullup
  pinMode(3, INPUT_PULLUP);   // 割り込み用・エンコーダB相読み込み用
  pinMode(DIR_PIN, OUTPUT);       // 右側車輪DIRピン
  pinMode(LED, OUTPUT);       // 基板判定用LED（デバッグ用）
  

  //-----PID関連-----//
  attachInterrupt(0, PulseCount, RISING); //パルスカウントするためPulseCount関数の割り込み
  count_pulse = 0;                        // 初期値設定
  vol_rpm = 0;                            // 初期値設定
  duty = constrain(duty, -255, 255);      // dutyの範囲を-255から255に定義→通常


  mySerial.begin(4800); 
  
  //-----MsTimer2設定-----//→採用
  MsTimer2::set(deltaT_ms, PID_compute);
  MsTimer2::start();                    //rpm_compute関数を0.2sで回す。
  
}

void loop() {
  
  if (mySerial.available() > 0) {
    char line;
    line = mySerial.read();  //終了タイミングが明示されることでバッファの待機時間を省略できる

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
  }
}

  //-----------------------------//

//前進
void Go() {  
  duty = initialDuty;       //duty値リセット
      P = 0;
      I = 0;
      D = 0;    //ゲインリセット
    
    analogWrite(PWM_PIN, duty);
    digitalWrite(LED, HIGH);      // 
    digitalWrite(DIR_PIN, LOW);   //
    
}

//後退
void Back() {
      duty = initialDuty;       //duty値リセット
      P = 0;
      I = 0;
      D = 0;    //ゲインリセット
    
    analogWrite(PWM_PIN, duty);
    digitalWrite(LED, HIGH);
    digitalWrite(DIR_PIN, HIGH);
    
}


//停止
void Stop() {
    analogWrite(PWM_PIN, 0);
    digitalWrite(DIR_PIN, LOW);
    digitalWrite(LED, HIGH);
    
}

//PWMで前進する場合
void PWM_Go() {  
    analogWrite(PWM_PIN, 120);     // PWMテスト用
    digitalWrite(DIR_PIN, LOW);
    
}

//PWMで後進する場合
void PWM_Back() {
    analogWrite(PWM_PIN, 255);     // PWMテスト用
    digitalWrite(DIR_PIN, HIGH);
    
}

//右折
void Right() {
  duty = turnDuty;       //duty値リセット
      P = 0;
      I = 0;
      D = 0;    //ゲインリセット
    
    analogWrite(PWM_PIN, duty); //
    digitalWrite(LED, HIGH);      // 
    digitalWrite(DIR_PIN, HIGH);   // 
    
}

//左折
void Left() {
  int pwm;  

  duty = turnDuty;       //duty値リセット
      P = 0;
      I = 0;
      D = 0;    //ゲインリセット
    
    analogWrite(PWM_PIN, duty);
    digitalWrite(LED, HIGH);      // 
    digitalWrite(DIR_PIN, LOW);   // 
    
}

void PulseCount(){    // 立ち上がり検知してインクリメント
  count_pulse++;
}

void PID_compute(){
  //---- 現在のRPM計算部----//
  vol_rpm = 60 * count_pulse / enc_1rotaly_per_Pulse / gear_ratio * unit_Time ; // 現在のRPM

  count_pulse = 0;

  //---- PID制御部----//
  P = target_rpm - vol_rpm; //比例制御のため目標値(target)から現在値(vol)を引く。つまり偏差:e(t)
  I += P * deltaT_ms;      //積分項
  D = (P - preP) / deltaT_ms;  // 微分項（前回偏差との差）
  preP = P;
  if ((-1 < duty) && (duty < 256)){
    duty += (Kp * P) + (Ki * I) + (Kd * D); //dutyをだんだん積み上げていく（オーバシュートしたらマイナスになるので積み下がる）
    //duty += (Kp * P) + (Ki * I);
  }
  if  (255 < duty) { 
    duty = 255;
  }
  else if  (0 > duty){
    duty = 0;
  }
}
