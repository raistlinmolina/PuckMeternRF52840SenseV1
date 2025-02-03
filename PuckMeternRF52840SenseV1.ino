#include <Wire.h>
#include <LSM6DS3.h>

// Crear una instancia del sensor IMU
LSM6DS3 myIMU(I2C_MODE, 0x6A);

// Umbral para detectar movimiento
float umbral_aceleracion = 0.2; // Ajusta según tus necesidades
float umbral_rotacion = 0.5;    // Ajusta según tus necesidades

void setup() {
  Serial.begin(115200);
  while (!Serial);

  // Inicializar el sensor IMU
  if (myIMU.begin() != 0) {
    Serial.println("Error al inicializar el IMU.");
    while (1);
  }
  Serial.println("IMU inicializado correctamente.");
}

bool detectar_movimiento(float accelX, float accelY, float accelZ, float gyroX, float gyroY, float gyroZ) {
  // Detección de movimiento
  float mag_aceleracion = sqrt(accelX * accelX + accelY * accelY + accelZ * accelZ);
  float mag_rotacion = sqrt(gyroX * gyroX + gyroY * gyroY + gyroZ * gyroZ);

  bool en_movimiento = mag_aceleracion > umbral_aceleracion;
  bool en_rotacion = mag_rotacion > umbral_rotacion;

  // Condición para detectar inicio de movimiento
  return en_movimiento || en_rotacion;
}

void loop() {
  // Leer datos del acelerómetro
  float accelX = myIMU.readFloatAccelX();
  float accelY = myIMU.readFloatAccelY();
  float accelZ = myIMU.readFloatAccelZ();

  // Leer datos del giroscopio
  float gyroX = myIMU.readFloatGyroX();
  float gyroY = myIMU.readFloatGyroY();
  float gyroZ = myIMU.readFloatGyroZ();

  // Detectar movimiento
  bool movimiento = detectar_movimiento(accelX, accelY, accelZ, gyroX, gyroY, gyroZ);

  // Imprimir los datos en el monitor serie
  Serial.print("Acelerómetro: X=");
  Serial.print(accelX);
  Serial.print(" Y=");
  Serial.print(accelY);
  Serial.print(" Z=");
  Serial.print(accelZ);

  Serial.print(" | Giroscopio: X=");
  Serial.print(gyroX);
  Serial.print(" Y=");
  Serial.print(gyroY);
  Serial.print(" Z=");
  Serial.print(gyroZ);

  Serial.print(" | Movimiento: ");
  if (movimiento) {
    Serial.println("Detectado");
  } else {
    Serial.println("No detectado");
  }

  // Esperar un poco antes de la siguiente lectura
  delay(100);
}
