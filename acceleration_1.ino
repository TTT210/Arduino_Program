#include <Arduino.h>
#include <Wire.h>
#include "SparkFun_MMA8452Q.h"

MMA8452Q accel;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  if (accel.begin() == false) {
    Serial.println("Not Connected. Please check connections and read the hookup guide.");
    while (1);
  }
}

void loop() {
  if (accel.available()) {
    float ax = accel.getCalculatedX();
    float az = accel.getCalculatedZ();
    float angle = atan2(ax, az) * 180.0 / PI;

    Serial.print(angle, 3);
    Serial.println();
  }
}
