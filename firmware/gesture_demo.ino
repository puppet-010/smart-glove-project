#include <Wire.h>
 
// ===== FLEX SENSORS =====

const int NB_SENSORS = 5;

// Ordre corrigé : Thumb, Index, Middle, Ring, Pinky

const int SENSOR_PINS[NB_SENSORS] = {34, 35, 32, 39, 33};

const char* fingerName[NB_SENSORS] = {
  "Index", "Middle", "Ring", "Thumb", "Pinky"
};


int threshold[NB_SENSORS] = {
  200,   // Index  GPIO34
  250,   // Middle GPIO35
  300,   // Ring   GPIO32
  1350,  // Thumb  GPIO39
  1200   // Pinky  GPIO33
};

 
// ===== MPU6500 =====

const int MPU6500_ADDR = 0x68;

const int ACCEL_XOUT_H = 0x3B;

const int GYRO_XOUT_H = 0x43;

const int PWR_MGMT_1 = 0x6B;
 
// Seuils de détection du mouvement de recul (tir)

const float RECOIL_ACCEL_THRESHOLD = 1.5;  // g (accélération vers l'arrière)

const float GYRO_THRESHOLD = 100.0;         // degrés/s (rotation du poignet)

const int RECOIL_COOLDOWN = 500;           // ms entre deux détections
 
unsigned long lastShotTime = 0;

bool shotDetected = false;
 
// ===== FONCTIONS FLEX =====

int readStable(int pin) {

  long sum = 0;

  for (int i = 0; i < 10; i++) {

    sum += analogRead(pin);

    delay(2);

  }

  return sum / 10;

}
 
int getPosition2States(int raw, int th) {

  if (raw > th) return 1;

  else return 3;

}
 
// ===== FONCTIONS MPU6500 =====

void writeMPU(byte reg, byte data) {

  Wire.beginTransmission(MPU6500_ADDR);

  Wire.write(reg);

  Wire.write(data);

  Wire.endTransmission();

}
 
int16_t readMPU16(byte reg) {

  Wire.beginTransmission(MPU6500_ADDR);

  Wire.write(reg);

  Wire.endTransmission(false);

  Wire.requestFrom(MPU6500_ADDR, 2);

  int16_t value = Wire.read() << 8;

  value |= Wire.read();

  return value;

}
 
void initMPU6500() {

  Wire.begin();

  delay(100);

  // Réveiller le MPU6500

  writeMPU(PWR_MGMT_1, 0x00);

  delay(100);

  // Configuration de l'accéléromètre : ±4g

  writeMPU(0x1C, 0x08);

  // Configuration du gyroscope : ±500°/s

  writeMPU(0x1B, 0x08);

  Serial.println("MPU6500 initialisé");

}
 
void readMPU6500(float &accelX, float &gyroY, float &gyroZ) {

  // Lire accéléromètre X (axe vertical quand main en position pistolet)

  int16_t ax = readMPU16(ACCEL_XOUT_H);

  accelX = ax / 8192.0; // ±4g scale

  // Lire gyroscope Y et Z (rotation du poignet)

  int16_t gy = readMPU16(GYRO_XOUT_H + 2);

  int16_t gz = readMPU16(GYRO_XOUT_H + 4);

  gyroY = gy / 65.5; // ±500°/s scale

  gyroZ = gz / 65.5;

}
 
bool detectShootingGesture(int pos[]) {

  // Vérifier la position des doigts : Index et Majeur tendus, autres pliés

  bool thumbBent = (pos[0] == 3);        // Pouce plié

  bool indexExtended = (pos[1] == 1);    // Index tendu

  bool middleExtended = (pos[2] == 1);   // Majeur tendu

  bool ringBent = (pos[3] == 3);         // Annulaire plié

  bool pinkyBent = (pos[4] == 3);        // Auriculaire plié

  return indexExtended && middleExtended && thumbBent && ringBent && pinkyBent;

}
 
bool detectRecoil(float accelX, float gyroY, float gyroZ) {

  // Détection du recul : accélération négative sur X (vers l'arrière)

  // et rotation du poignet (gyro)

  bool recoilAccel = (accelX < -RECOIL_ACCEL_THRESHOLD);

  bool wristRotation = (abs(gyroY) > GYRO_THRESHOLD || abs(gyroZ) > GYRO_THRESHOLD);

  return recoilAccel || wristRotation;

}
 
void setup() {

  Serial.begin(115200);

  delay(1000);

  Serial.println("=== DÉTECTEUR DE TIR AU PISTOLET ===");

  Serial.println("Position : Index et Majeur tendus, autres doigts pliés");

  Serial.println("MPU6500 : Axe X vertical");

  Serial.println("====================================");

  Serial.println("Pins corrigés:");

  Serial.println("  Thumb  -> GPIO34");

  Serial.println("  Index  -> GPIO35");

  Serial.println("  Middle -> GPIO32");

  Serial.println("  Ring   -> GPIO39");

  Serial.println("  Pinky  -> GPIO33");

  Serial.println("====================================");

  initMPU6500();

}
 
void loop() {

  // ===== LECTURE FLEX SENSORS =====

  int raw[NB_SENSORS];

  int pos[NB_SENSORS];

  for (int i = 0; i < NB_SENSORS; i++) {

    raw[i] = readStable(SENSOR_PINS[i]);

    pos[i] = getPosition2States(raw[i], threshold[i]);

  }

  // ===== LECTURE MPU6500 =====

  float accelX, gyroY, gyroZ;

  readMPU6500(accelX, gyroY, gyroZ);

  // ===== DÉTECTION DU GESTE =====

  bool isGunPosition = detectShootingGesture(pos);

  // Détection du tir (mouvement de recul)

  if (isGunPosition && !shotDetected && (millis() - lastShotTime > RECOIL_COOLDOWN)) {

    if (detectRecoil(accelX, gyroY, gyroZ)) {

      Serial.println(">>> TIR DÉTECTÉ! <<<");

      shotDetected = true;

      lastShotTime = millis();

    }

  } else if (!detectRecoil(accelX, gyroY, gyroZ)) {

    shotDetected = false;

  }

  // ===== AFFICHAGE =====

  Serial.println("------");

  // Affichage des doigts

  for (int i = 0; i < NB_SENSORS; i++) {

    Serial.print(fingerName[i]);

    Serial.print(" (GPIO");

    Serial.print(SENSOR_PINS[i]);

    Serial.print("): ");

    Serial.print(pos[i] == 1 ? "TENDU" : "PLIÉ");

    Serial.print(" (");

    Serial.print(raw[i]);

    Serial.println(")");

  }

  // Affichage MPU6500

  Serial.print("Accel X: ");

  Serial.print(accelX, 2);

  Serial.print(" g | Gyro Y: ");

  Serial.print(gyroY, 1);

  Serial.print(" | Gyro Z: ");

  Serial.println(gyroZ, 1);

  // Statut

  Serial.print("Position pistolet: ");

  Serial.println(isGunPosition ? "OUI ✓" : "NON");

  delay(50); // Lecture plus rapide pour détecter le mouvement

}
 