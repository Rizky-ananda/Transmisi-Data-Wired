/*
  ============================================================
  Project   : RS485 Master Transmitter – Kirim Data Analog dari Potensiometer
  Board     : ESP32
  Deskripsi : 
    Program ini berfungsi sebagai master transmitter yang membaca 
    nilai analog dari potensiometer, kemudian mengirimkan data tersebut 
    ke slave melalui modul RS485 (MAX485).

  Perangkat :
    - ESP32
    - Modul RS485 (MAX485)
    - Potensiometer

  Koneksi :
    MAX485  ->  ESP32
      RO    ->  RX_PIN (GPIO16)
      DI    ->  TX_PIN (GPIO17)
      DE,RE ->  DRE_PIN (GPIO4)
      VCC   ->  3.3V
      GND   ->  GND

    Potensiometer -> ESP32
      OUT   ->  GPIO15
      VCC   ->  3.3V
      GND   ->  GND

  Baudrate : 9600 bps
  Author   : Rizky Ananda S
  Date     : 20 Oktober 2024
  Version  : 2.0 (Last Update 4 November 2025)
  ============================================================
*/

// Masukan library yang digunakan
#include <SoftwareSerial.h>

// Konfigurasi Pin RS485 dan Potensiometer
#define RX_PIN   16   // MAX485 RO -> RX ESP32
#define TX_PIN   17   // MAX485 DI -> TX ESP32
#define DRE_PIN  4    // MAX485 DE & RE -> GPIO4
#define PIN_POT  15   // Pin input potensiometer

// Objek Software Serial
SoftwareSerial mySerial(RX_PIN, TX_PIN); // RX, TX

// Setup Awal
void setup() {
  // Inisialisasi komunikasi serial
  Serial.begin(9600);
  mySerial.begin(9600);

  // Setup pin RS485
  pinMode(DRE_PIN, OUTPUT);
  digitalWrite(DRE_PIN, LOW); // mode receive awal

  // Tampilan awal di Serial Monitor
  Serial.println("=== RS485 Master: Transmisi Data Analog ===");
  Serial.println();
}

// Loop Utama
void loop() {
  // Baca nilai analog dari potensiometer
  int nilaiAnalog = analogRead(PIN_POT);

  // Format data yang dikirim
  String dataKirim = "Data Pot: " + String(nilaiAnalog);

  // Mode transmit (DE/RE HIGH)
  digitalWrite(DRE_PIN, HIGH);
  mySerial.println(dataKirim);
  digitalWrite(DRE_PIN, LOW); // kembali ke mode receive

  // Tampilkan di Serial Monitor
  Serial.print("Data terkirim: ");
  Serial.println(dataKirim);

  delay(1000); // jeda antar pengiriman
}
