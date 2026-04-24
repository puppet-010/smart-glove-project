#include <Wire.h>

#include <math.h>

 

#define MPU_ADDR 0x68   // AD0接地一般就是0x68，若不通可试0x69

 

// ESP32 I2C引脚

#define SDA_PIN 21

#define SCL_PIN 22

 

// MPU寄存器

#define REG_WHO_AM_I    0x75

#define REG_PWR_MGMT_1  0x6B

#define REG_ACCEL_XOUT_H 0x3B

#define REG_GYRO_CONFIG  0x1B

#define REG_ACCEL_CONFIG 0x1C

 

int16_t rawAx, rawAy, rawAz;

int16_t rawGx, rawGy, rawGz;

 

float ax, ay, az;   // 单位 g

float gx, gy, gz;   // 单位 deg/s

 

float pitch, roll;

 

void writeRegister(uint8_t reg, uint8_t value) {

  Wire.beginTransmission(MPU_ADDR);

  Wire.write(reg);

  Wire.write(value);

  Wire.endTransmission();

}

 

uint8_t readRegister(uint8_t reg) {

  Wire.beginTransmission(MPU_ADDR);

  Wire.write(reg);

  Wire.endTransmission(false);

 

  Wire.requestFrom(MPU_ADDR, (uint8_t)1);

  if (Wire.available()) {

    return Wire.read();

  }

  return 0xFF;

}

 

void readMPU() {

  Wire.beginTransmission(MPU_ADDR);

  Wire.write(REG_ACCEL_XOUT_H);

  Wire.endTransmission(false);

 

  Wire.requestFrom(MPU_ADDR, (uint8_t)14);

 

  if (Wire.available() >= 14) {

    rawAx = (Wire.read() << 8) | Wire.read();

    rawAy = (Wire.read() << 8) | Wire.read();

    rawAz = (Wire.read() << 8) | Wire.read();

 

    Wire.read(); Wire.read();   // 温度先跳过

 

    rawGx = (Wire.read() << 8) | Wire.read();

    rawGy = (Wire.read() << 8) | Wire.read();

    rawGz = (Wire.read() << 8) | Wire.read();

  }

 

  // 默认配置下：

  // 加速度 ±2g -> 16384 LSB/g

  // 陀螺仪 ±250 dps -> 131 LSB/(deg/s)

  ax = rawAx / 16384.0;

  ay = rawAy / 16384.0;

  az = rawAz / 16384.0;

 

  gx = rawGx / 131.0;

  gy = rawGy / 131.0;

  gz = rawGz / 131.0;

}

 

void computeAngles() {

  // 仅用加速度计估算倾角，适合静态或慢速动作

  roll  = atan2(ay, az) * 180.0 / PI;

  pitch = atan2(-ax, sqrt(ay * ay + az * az)) * 180.0 / PI;

}

 

void setup() {

  Serial.begin(115200);

  delay(1000);

 

  Wire.begin(SDA_PIN, SCL_PIN);

  Wire.setClock(400000);

 

  Serial.println("Start MPU6500 / MPU9250 test...");

 

  // 唤醒MPU

  writeRegister(REG_PWR_MGMT_1, 0x00);

  delay(100);

 

  // 加速度量程设为 ±2g

  writeRegister(REG_ACCEL_CONFIG, 0x00);

 

  // 陀螺仪量程设为 ±250 deg/s

  writeRegister(REG_GYRO_CONFIG, 0x00);

 

  delay(100);

 

  uint8_t whoami = readRegister(REG_WHO_AM_I);

  Serial.print("WHO_AM_I = 0x");

  Serial.println(whoami, HEX);

 

  if (whoami == 0x70) {

    Serial.println("Detected MPU6500");

  } else if (whoami == 0x71) {

    Serial.println("Detected MPU9250");

  } else if (whoami == 0x73) {

    Serial.println("Possible MPU9255 / similar");

  } else {

    Serial.println("Unknown device, check wiring/address!");

  }

}

 

void loop() {

  readMPU();

  computeAngles();

 

  Serial.println("------------");

  Serial.print("Accel (g): ");

  Serial.print("ax=");

  Serial.print(ax, 3);

  Serial.print("  ay=");

  Serial.print(ay, 3);

  Serial.print("  az=");

  Serial.println(az, 3);

 

  Serial.print("Gyro (deg/s): ");

  Serial.print("gx=");

  Serial.print(gx, 2);

  Serial.print("  gy=");

  Serial.print(gy, 2);

  Serial.print("  gz=");

  Serial.println(gz, 2);

 

  Serial.print("Angle (deg): ");

  Serial.print("pitch=");

  Serial.print(pitch, 2);

  Serial.print("  roll=");

  Serial.println(roll, 2);

 

  delay(200);

}