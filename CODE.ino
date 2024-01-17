#include "DHT.h"
#include <SFE_BMP180.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd=LiquidCrystal_I2C(0x27,16,2);


#define DHTPIN 5 // Digital Pin 5
#define DHTTYPE DHT22 // We are Using DHT22
#define TEMPTYPE 0 
#define ALTITUDE 234 // Altitude from PHAGWARA


int i=1;
DHT dht(DHTPIN, DHTTYPE); // Initialising Pin and Type of DHT
SFE_BMP180 pressure;

void setup()
{
pressure.begin();
dht.begin(); // Enabling DHT22
lcd.init();
lcd.backlight();
pinMode(A0,INPUT);
pinMode(A1,INPUT);
}

void loop()
{
int humidity = dht.readHumidity(); // Reading Humidity Value
int temperature = dht.readTemperature(); // Reading Temperature Value
int status = pressure.startTemperature();
double T,P,p0,a;
 if (status != 0)
    {
     
      status = pressure.startPressure(3);
      if (status != 0)
      {
        // Wait for the measurement to complete:
        delay(status);

        status = pressure.getPressure(P,T);
        if (status != 0)
        {
          p0 = pressure.sealevel(P,ALTITUDE); 
          a = pressure.altitude(P,p0);
        }
        else Serial.println("error retrieving pressure measurement\n");
      }
      else Serial.println("error starting pressure measurement\n");
    }
    int co2=map(analogRead(A0),0,1023,400,5000);
    int rainValue = map(analogRead(A1),0,1023,255,0);  // Read the analog value from sensor
    lcd.setCursor(0,0);
    lcd.print(String(temperature)+"C");
    lcd.setCursor(4,0);
    lcd.print(String(humidity)+"%");
    lcd.setCursor(8,0);
    lcd.print(String(co2)+"ppm");
    lcd.setCursor(0,1);
    lcd.print(String(p0)+"Pa");
    lcd.setCursor(10,1);
    lcd.print(String(rainValue)+"mm");
    delay(1000); // Update after every 1 second(s)

}
