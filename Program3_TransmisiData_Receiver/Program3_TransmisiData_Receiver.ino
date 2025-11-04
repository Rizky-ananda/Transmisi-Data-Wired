/*
  ============================================================
  Project   : RS485 Slave Receiver – Display Data Analog on OLED
  Board     : ESP32
  Deskripsi : 
    Program ini berfungsi sebagai slave receiver yang menerima 
    data dari master melalui modul RS485 (MAX485). 
    Data yang diterima kemudian ditampilkan pada Serial Monitor 
    dan layar OLED menggunakan protokol I2C.

  Perangkat :
    - ESP32
    - Modul RS485 (MAX485)
    - OLED Display 0.96" I2C (alamat 0x3C)

  Koneksi :
    MAX485  ->  ESP32
      RO    ->  RX_PIN (GPIO16)
      DI    ->  TX_PIN (GPIO17)
      DE,RE ->  DRE_PIN (GPIO4)
      VCC   ->  3.3V
      GND   ->  GND

    OLED    ->  ESP32
      SDA   ->  GPIO21
      SCL   ->  GPIO22

  Baudrate : 9600 bps
  Author   : Rizky Ananda S
  Date     : 20 Oktober 2024
  Version  : 2.0 (Last Update 4 November 2025)
  ============================================================
*/

// Masukan library Yang digunakan
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Konfigurasi Pin RS485, OLED
// RS485
#define RX_PIN   16   // MAX485 RO -> RX ESP32
#define TX_PIN   17   // MAX485 DI -> TX ESP32
#define DRE_PIN  4    // MAX485 DE & RE -> GPIO4

//OLED
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Objek Software Serial
SoftwareSerial mySerial(RX_PIN, TX_PIN); // RX, TX


// Setup Awal
void setup() {
  // Inisialisasi komunikasi serial
  Serial.begin(9600);
  mySerial.begin(9600);

  // Setup pin RS485
  pinMode(DRE_PIN, OUTPUT);
  digitalWrite(DRE_PIN, LOW); // mode receive

  // Inisialisasi OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("Gagal inisialisasi OLED!"));
    for (;;); // Berhenti di sini jika OLED gagal
  }

  // Tampilan awal OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.display();
}

// Loop Utama
void loop() {
  // Cek apakah ada data dari RS485 (via SoftwareSerial)
  if (mySerial.available()) {
    // Baca string data yang dikirim dari master
    String message = mySerial.readString();

    // Cetak Hasil Transmisi Data
    // Tampilkan di Serial Monitor
    Serial.print("Data diterima: ");
    Serial.println(message);

    // Tampilkan di OLED
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(10, 0);
    display.print("Komunikasi RS485");
    display.setCursor(10, 20);
    display.print("Kelompok 2 - A1");
    display.setCursor(0, 40);
    display.print("Data: ");
    display.print(message);
    display.display();
  }
}
