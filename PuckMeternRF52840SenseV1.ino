#include <Wire.h>
#include <LSM6DS3.h>

// Crear una instancia del sensor IMU
LSM6DS3 myIMU(I2C_MODE, 0x6A); 

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

void loop() {
  // Leer datos del acelerómetro
  float accelX = myIMU.readFloatAccelX();
  float accelY = myIMU.readFloatAccelY();
  float accelZ = myIMU.readFloatAccelZ();

  // Leer datos del giroscopio
  float gyroX = myIMU.readFloatGyroX();
  float gyroY = myIMU.readFloatGyroY();
  float gyroZ = myIMU.readFloatGyroZ();

  // Imprimir los datos en el monitor serie
  Serial.print("Acelerómetro: X=");
  Serial.print(accelX);
  Serial.print(" Y=");
  Serial.print(accelY);
  Serial.print(" Z=");
  Serial.println(accelZ);

  Serial.print("Giroscopio: X=");
  Serial.print(gyroX);
  Serial.print(" Y=");
  Serial.print(gyroY);
  Serial.print(" Z=");
  Serial.println(gyroZ);

  // Esperar un poco antes de la siguiente lectura
  delay(100);
}
