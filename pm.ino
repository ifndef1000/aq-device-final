// Libraries included

#include <Wire.h> // ??
#include <RTClib.h> // real time clock
#include <SPI.h> // SD card?
#include <SD.h> // SD card
#include <sps30.h> // Sensirion SPS30
static uint8_t recv_cmd[8] = {}; // Integer for Grove sensor

// Definitions

File dataFilePM; // define file to save PM data to
int counter=0;
RTC_DS1307 rtc; // define timeclock

// defines variables ret, auto_clean_days and auto_clean
void setup() {
  pinMode(4,INPUT_PULLUP);


  Serial.begin(9600);
  delay(1000);

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
  }

  if (!SD.begin(10)) {
  Serial.println("initialization failed!");
  counter=0;


}


}

void loop() {
 
  DateTime now = rtc.now();
  delay(1000);


  struct sps30_measurement m;
  char serial[SPS30_MAX_SERIAL_LEN];
  uint16_t data_ready;
  int16_t ret;
  
  ret = sps30_start_measurement();
  ret = sps30_read_data_ready(&data_ready);
  ret = sps30_read_measurement(&m);
  
  if(digitalRead(4)==LOW){
  dataFilePM = SD.open("PM.CSV", FILE_WRITE);
  dataFilePM.print(now.year(), DEC);
  dataFilePM.print('/');
  dataFilePM.print(now.month(), DEC);
  dataFilePM.print('/');
  dataFilePM.print(now.day(), DEC);
  dataFilePM.print(",");
  dataFilePM.print(now.hour(), DEC);
  dataFilePM.print(':');
  dataFilePM.print(now.minute(), DEC);
  dataFilePM.print(':');
  dataFilePM.print(now.second(), DEC);
  dataFilePM.print(',');
  dataFilePM.print(m.mc_2p5);
  dataFilePM.print(",");
  dataFilePM.print(m.mc_10p0);
  dataFilePM.print(",");
  dataFilePM.print(m.nc_2p5);
  dataFilePM.print(",");
  dataFilePM.print(m.nc_10p0);
  dataFilePM.print(",");
  dataFilePM.print(m.typical_particle_size);
  dataFilePM.print(",");
  dataFilePM.println();
  dataFilePM.close();
  Serial.print("S=");
  Serial.print(now.second());
  Serial.print("           L=");

  }
  Serial.println(counter++);
  
  


}
