const int NB_SENSORS = 4;

const int SENSOR_PINS[NB_SENSORS] = {34, 35, 32, 33};

 

 

int minRaw[NB_SENSORS] = {0, 0, 620, 420};

int maxRaw[NB_SENSORS] = {720, 1150, 1525, 1460};

 

 

float getPercent(int value, int minVal, int maxVal) {

  if (maxVal == minVal) return 0.0;

 

  float percent = (maxVal - value) * 100.0 / (maxVal - minVal);

 

  if (percent < 0.0) percent = 0.0;

  if (percent > 100.0) percent = 100.0;

 

  return percent;

}

 

// 每根手指单独分段

int getPosition(int sensorIndex, float percent) {

  // C1, C2：中间状态加宽很多

  if (sensorIndex == 0 || sensorIndex == 1) {

    if (percent < 20.0) return 1;

    else if (percent < 85.0) return 2;

    else return 3;

  }

 

  // C3, C4：保持正常三段

  if (percent < 30.0) return 1;

  else if (percent < 70.0) return 2;

  else return 3;

}

 

void printData(int raw[], float percent[], int position[]) {

  Serial.println("------");

 

  for (int i = 0; i < NB_SENSORS; i++) {

    Serial.print("Capteur ");

    Serial.print(i + 1);

 

    Serial.print(" (GPIO");

    Serial.print(SENSOR_PINS[i]);

    Serial.print(")");

 

    Serial.print(" | Raw: ");

    Serial.print(raw[i]);

 

    Serial.print(" | %: ");

    Serial.print(percent[i], 1);

 

    Serial.print(" | Pos: ");

    Serial.println(position[i]);

  }

}

 

void setup() {

  Serial.begin(115200);

  delay(1000);

 

  Serial.println("Systeme 4 capteurs - 3 positions");

  Serial.println("0% = doigt plat / 100% = doigt plie");

}

 

void loop() {

  int raw[NB_SENSORS];

  float percent[NB_SENSORS];

  int position[NB_SENSORS];

 

  for (int i = 0; i < NB_SENSORS; i++) {

    raw[i] = analogRead(SENSOR_PINS[i]);

    percent[i] = getPercent(raw[i], minRaw[i], maxRaw[i]);

    position[i] = getPosition(i, percent[i]);

  }

 

  printData(raw, percent, position);

 

  delay(300);

}