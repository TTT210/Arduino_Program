#include <DHT.h>
#include <DHT_U.h>

//Lesson 11 温湿度センサモジュール
//温度、湿度を測定するスケッチ
//https://omoroya.com/

#include "DHT.h" //ライブラリインクルード

#define DHT_Pin 15 //DHT11のDATAピンを定義
#define DHT_Type DHT11 //センサの型番定義　DHT11,DHT22など

DHT dht(DHT_Pin, DHT_Type); //センサ初期化

/* 計測値設定 */
float humidity = 0.0f; //湿度
float tempC = 0.0f; //摂氏温度
float tempF = 0.0f; //華氏温度
float discomfortIndex = 0.0f; //不快指数
bool isFahrenheit = true; //華氏読み出し引数にtrueを設定

void setup() {
Serial.begin(9600); //シリアル通信のデータ転送レートを9600bpsで指定。bpsはビット/秒。
Serial.println("DHT11 Lesson11"); //画面に表示
dht.begin(); //温湿度センサー開始
}

void loop() {
delay(2000); //2秒待つ　データの読み出し周期1秒以上必要。

humidity = dht.readHumidity(); //湿度の読み出し
tempC = dht.readTemperature(); //温度の読み出し 摂氏
tempF = dht.readTemperature( isFahrenheit ); //温度の読み出し 華氏

/* 読み取れたかどうかのチェック */
if (isnan(humidity) || isnan(tempC) || isnan(tempF)) {
Serial.println("Read failure!");
return;
}

/* おまけ　不快指数計算 */
discomfortIndex = 0.81f * tempC + 0.01f * humidity * (0.99f * tempC - 14.3f) + 46.3f;

/* 以下読み取り値の表示 */
Serial.print("湿度: ");
Serial.print(humidity);
Serial.println("[%]");
Serial.print("温度: "); 
Serial.print(tempC);
Serial.println("[℃]");
Serial.print("華氏: "); 
Serial.print(tempF);
Serial.println("[F]");
Serial.print("不快指数： "); 
Serial.println(discomfortIndex);
}
