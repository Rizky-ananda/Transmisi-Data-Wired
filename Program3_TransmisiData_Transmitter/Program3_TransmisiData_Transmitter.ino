/*
  ============================================================
  Project   : RS485 - Transmisi Data wired 2 arah
  Board     : ESP32
  Deskripsi : 
    Program ini merupakan program tranmisi data 2 arah secara wired 
    dengan menggunakan modul RS485, perangkat bisa mengirimkan pesan 
    yang diinput melalui serial monitor dan akan dibaca diperangkat
    lainnya dan perangkat yang satunya bisa mengirimkan balasannya
    jadi bisa interaktif, saling mengirim dan menerima pesan

  Perangkat :
    - ESP32
    - Modul RS485 (MAX485)

  Koneksi :
    MAX485  ->  ESP32
      RO    ->  RX_PIN (GPIO16)
      DI    ->  TX_PIN (GPIO17)
      DE,RE ->  DRE_PIN (GPIO4)
      VCC   ->  5V
      GND   ->  GND

  Baudrate : 9600 bps
  Author   : Rizky Ananda S
  Date     : 20 Oktober 2025
  Version  : 2.0 (Last Update 4 November 2025)
  ============================================================
*/

// Masukan library yang digunakan
#include <SoftwareSerial.h>

// Konfigurasi Pin RS485
#define RX_PIN   16   // MAX485 RO -> RX ESP32
#define TX_PIN   17   // MAX485 DI -> TX ESP32
#define DRE_PIN  4    // MAX485 DE & RE -> GPIO4

// Objek Software Serial
SoftwareSerial mySerial(RX_PIN, TX_PIN); // RX, TX

// Setup Awal
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  pinMode(DRE_PIN, OUTPUT);
  digitalWrite(DRE_PIN, LOW); // mode receive awal

}

// Loop Utama
void loop() {
  // Kirim data dari Serial Monitor ke Master
  if (Serial.available()) {
    String inputData = Serial.readString();  // baca input teks dari Serial Monitor
    digitalWrite(DRE_PIN, HIGH);             // aktifkan mode kirim
    mySerial.print(inputData);               // kirim ke master
    digitalWrite(DRE_PIN, LOW);              // kembali ke mode receive

    Serial.print("Data terkirim: ");
    Serial.println(inputData);
  }

  // Terima data dari Master melalui RS485
  if (mySerial.available()) {
    String terimaData = mySerial.readString();
    Serial.print("Data diterima: ");
    Serial.println(terimaData);
  }

  delay(100);
}
