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
    
    } else if (data == '1') { //前進
    digitalWrite(AIN1_1, LOW);
    digitalWrite(AIN2_1, HIGH);
    analogWrite(PWMA_1, 50);

    digitalWrite(BIN1_1, HIGH);
    digitalWrite(BIN2_1, LOW);
    analogWrite(PWMB_1, 50);

    digitalWrite(AIN1_2, LOW);
    digitalWrite(AIN2_2, HIGH);
    analogWrite(PWMA_2, 50);

    digitalWrite(BIN1_2, HIGH);
    digitalWrite(BIN2_2, LOW);
    analogWrite(PWMB_2, 50);
 
  } else if (data == '2') {//後退
    digitalWrite(AIN1_1, HIGH);
    digitalWrite(AIN2_1, LOW);
    analogWrite(PWMA_1, 50);
        
    digitalWrite(BIN1_1, LOW);
    digitalWrite(BIN2_1, HIGH);
    analogWrite(PWMB_1, 50);
        
    digitalWrite(AIN1_2, HIGH);
    digitalWrite(AIN2_2, LOW);
    analogWrite(PWMA_2, 50);
        
    digitalWrite(BIN1_2, LOW);
    digitalWrite(BIN2_2, HIGH);
    analogWrite(PWMB_2, 50);
 
  } else if (data == '3') {//右回転
    digitalWrite(AIN1_1, LOW);
    digitalWrite(AIN2_1, HIGH);
    analogWrite(PWMA_1, 50);

    digitalWrite(BIN1_1, HIGH);
    digitalWrite(BIN2_1, LOW);
    analogWrite(PWMB_1, 0);

    digitalWrite(AIN1_2, LOW);
    digitalWrite(AIN2_2, HIGH);
    analogWrite(PWMA_2, 50);

    digitalWrite(BIN1_2, HIGH);
    digitalWrite(BIN2_2, LOW);
    analogWrite(PWMB_2, 0);
    
  } else if (data == '4') {//左回転
    digitalWrite(AIN1_1, LOW);
    digitalWrite(AIN2_1, HIGH);
    analogWrite(PWMA_1, 0);

    digitalWrite(BIN1_1, HIGH);
    digitalWrite(BIN2_1, LOW);
    analogWrite(PWMB_1, 50);

    digitalWrite(AIN1_2, LOW);
    digitalWrite(AIN2_2, HIGH);
    analogWrite(PWMA_2, 0);

    digitalWrite(BIN1_2, HIGH);
    digitalWrite(BIN2_2, LOW);
    analogWrite(PWMB_2, 50);
    
  } else if (data == '5') {//旋回(右前)
    digitalWrite(AIN1_1, LOW);
    digitalWrite(AIN2_1, HIGH);
    analogWrite(PWMA_1, 50);

    digitalWrite(BIN1_1, HIGH);
    digitalWrite(BIN2_1, LOW);
    analogWrite(PWMB_1, 25);

    digitalWrite(AIN1_2, LOW);
    digitalWrite(AIN2_2, HIGH);
    analogWrite(PWMA_2, 50);

    digitalWrite(BIN1_2, HIGH);
    digitalWrite(BIN2_2, LOW);
    analogWrite(PWMB_2, 25);
    
  } else if (data == '6') {//旋回(左前)
    digitalWrite(AIN1_1, LOW);
    digitalWrite(AIN2_1, HIGH);
    analogWrite(PWMA_1, 25);

    digitalWrite(BIN1_1, HIGH);
    digitalWrite(BIN2_1, LOW);
    analogWrite(PWMB_1, 50);

    digitalWrite(AIN1_2, LOW);
    digitalWrite(AIN2_2, HIGH);
    analogWrite(PWMA_2, 25);

    digitalWrite(BIN1_2, HIGH);
    digitalWrite(BIN2_2, LOW);
    analogWrite(PWMB_2, 50);
    
  } else if (data == '7') {//旋回(右後)
    digitalWrite(AIN1_1, HIGH);
    digitalWrite(AIN2_1, LOW);
    analogWrite(PWMA_1, 50);
        
    digitalWrite(BIN1_1, LOW);
    digitalWrite(BIN2_1, HIGH);
    analogWrite(PWMB_1, 25);
        
    digitalWrite(AIN1_2, HIGH);
    digitalWrite(AIN2_2, LOW);
    analogWrite(PWMA_2, 50);
        
    digitalWrite(BIN1_2, LOW);
    digitalWrite(BIN2_2, HIGH);
    analogWrite(PWMB_2, 25);
    
  } else if (data == '8') {//旋回(左後)
    digitalWrite(AIN1_1, HIGH);
    digitalWrite(AIN2_1, LOW);
    analogWrite(PWMA_1, 25);
        
    digitalWrite(BIN1_1, LOW);
    digitalWrite(BIN2_1, HIGH);
    analogWrite(PWMB_1, 50);
        
    digitalWrite(AIN1_2, HIGH);
    digitalWrite(AIN2_2, LOW);
    analogWrite(PWMA_2, 25);
        
    digitalWrite(BIN1_2, LOW);
    digitalWrite(BIN2_2, HIGH);
    analogWrite(PWMB_2, 50);

  }
}
