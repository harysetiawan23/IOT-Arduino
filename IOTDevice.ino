#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C  lcd(0x27, 2, 1, 0, 4, 5, 6, 7); // 0x27 = alamat I2C modul

/*
   This sample sketch demonstrates the normal use of a TinyGPS++ (TinyGPSPlus) object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/
static const int RXPin = 6, TXPin = 7;
static const uint32_t GPSBaud = 9600;

static int no = 1;
// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setup()
{
  Serial.begin(115200);
  ss.begin(GPSBaud);
  Serial.println("\n");
  Serial.println(F("Pembacaan Tekanan"));
  Serial.println(F("by Hary Setiawan"));
  Serial.println(F("----------------------------------------------------------------------------------------------------------------------------------------"));

  Serial.println();
  lcd.begin (16, 2); // LCD 16x2
  lcd.setBacklightPin(3, POSITIVE);
  lcd.setBacklight(HIGH);

  lcd.home (); // set cursor to 0,0
  lcd.print("S1[kPa]= ");
  lcd.setCursor (0,1);
  lcd.print("S2[kPa]= ");
}

void loop() {
  // This sketch displays information every time a new sentence is correctly encoded.
//  while (ss.available() > 0) {
//    if (gps.encode(ss.read())) {
//
//     
//    }
//
//
//  }
 display_status();
 delay(1000);
}


String waktu() {
  String jam, menit, detik = "";
  if (gps.time.isValid()) {
    if (gps.time.hour() < 10) {
      jam = "0";
    } else {
      jam = String(gps.time.hour() - 4);
    }

    if (gps.time.minute() < 10) {
      menit = "0";
    } else {
      menit = String(gps.time.minute());
    }

    if (gps.time.second() < 10) {
      detik = "0";
    } else {
      detik = String(gps.time.second());
    }

  }
  else
  {
    Serial.print(F("INVALID"));
  }

  String waktu = jam + ":" + menit + ":" + detik;
  return waktu;
}

String lattidute() {
  String Tiny_latitude = String(gps.location.lat(), 6);
  return Tiny_latitude;
}

String longitude() {
  String Tiny_latitude = String(gps.location.lng(), 6);
  return Tiny_latitude;
}



String pascal_slotA() {
  int sensorVal = analogRead(A1);
  //  Serial.print("Sensor Value: ");
  //  Serial.print(sensorVal);

  float voltage = (sensorVal * 5.0) / 1024.0;
  //  Serial.print("Volts: ");
  //  Serial.print(voltage);

  float pressure_pascal = (3.0 * ((float)voltage - 0.47)) * 1000000.0;
  float pressure_bar = pressure_pascal / 10e5;
  //  Serial.print("Pressure = ");
  //  Serial.print(pressure_bar);
  //  Serial.println(" bars");
  //  Serial.print("Pressure = ");

//  turn to KPa
  String pa = String(pressure_bar * 100);
  return pa;


}

String pascal_slotB() {
  int sensorVal = analogRead(A2);
  //  Serial.print("Sensor Value: ");
  //  Serial.print(sensorVal);

  float voltage = (sensorVal * 5.0) / 1024.0;
  //  Serial.print("Volts: ");
  //  Serial.print(voltage);

  float pressure_pascal = (3.0 * ((float)voltage - 0.47)) * 1000000.0;
  float pressure_bar = pressure_pascal / 10e5;
  //  Serial.print("Pressure = ");
  //  Serial.print(pressure_bar);
  //  Serial.println(" bars");
  //  Serial.print("Pressure = ");

//  turn to KPa
  String pa = String(pressure_bar * 100);
  return pa;


}


String mPa_slotA() {
  int sensorVal = analogRead(A1);
  //  Serial.print("Sensor Value: ");
  //  Serial.print(sensorVal);

  float voltage = (sensorVal * 5.0) / 1024.0;
  //  Serial.print("Volts: ");
  //  Serial.print(voltage);

  float pressure_pascal = (3.0 * ((float)voltage - 0.47)) * 1000000.0;
  float pressure_bar = pressure_pascal / 10e5;
  //  Serial.print("Pressure = ");
  //  Serial.print(pressure_bar);
  //  Serial.println(" bars");
  //  Serial.print("Pressure = ");




  String pa = String((pressure_bar * 100000) / 1000000);
  return pa;

}

String mPa_slotB() {
  int sensorVal = analogRead(A2);
  //  Serial.print("Sensor Value: ");
  //  Serial.print(sensorVal);

  float voltage = (sensorVal * 5.0) / 1024.0;
  //  Serial.print("Volts: ");
  //  Serial.print(voltage);

  float pressure_pascal = (3.0 * ((float)voltage - 0.47)) * 1000000.0;
  float pressure_bar = pressure_pascal / 10e5;
  //  Serial.print("Pressure = ");
  //  Serial.print(pressure_bar);
  //  Serial.println(" bars");
  //  Serial.print("Pressure = ");




  String pa = String((pressure_bar * 100000) / 1000000);
  return pa;

}


String pressure_bar() {
  int sensorVal = analogRead(A1);
  float voltage = (sensorVal * 5.0) / 1024.0;
  float pressure_pascal = (3.0 * ((float)voltage - 0.47)) * 1000000.0;
  float pressure_bar = pressure_pascal / 10e5;
  String bar = String(pressure_bar, 3);
  return bar;
}
//
String tanggal() {
  String tanggal = String(gps.date.year()) + "-" + String(gps.date.month()) + "-" + String(gps.date.day());
  return tanggal;
}


void display_status() {
  Serial.print("Longitude       : " );
  Serial.println(lattidute());
  Serial.print("Lattidute       : " );
  Serial.println(longitude());
  Serial.print("Pressure (Bars) : " );
  Serial.println(pressure_bar());

//  Serial.println("Pressure (Pa)   : " + pascal());
//  Serial.println("Pressure (MPa)  : " + mPa());
  Serial.println(F("----------------------------------------------------------------------------------------------------------------------------------------"));
  no++;
 
//  lcd.clear();
  lcd.setCursor (9,0);
  lcd.print(pascal_slotA());
  lcd.setCursor (9,1);
  lcd.print(pascal_slotB());
//  lcd.setCursor (10,1);
//  lcd.print("MPa=" + mPa_slotA());

}
