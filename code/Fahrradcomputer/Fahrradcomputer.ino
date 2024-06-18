/************************************************************************************************* 
                                      PROGRAMMINFO
************************************************************************************************** 
Funktion: Fahrradcomputer mit Drehgeber, Hallgenerator und SSD1306 Display
**************************************************************************************************
Version: 26.07.2021
**************************************************************************************************
Board: Arduino NANO
**************************************************************************************************
C++ Arduino IDE V1.8.13
**************************************************************************************************
Einstellungen:
https://dl.espressif.com/dl/package_esp32_index.json
http://dan.drown.org/stm32duino/package_STM32duino_index.json
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_dev_index.json
**************************************************************************************************/

#define RADUMFANG     211   // Radumfang in cm

#define HALL_SENSOR   2     // muss Interrupt-fähig sein
#define ENCODER_CLK   3     // muss Interrupt-fähig sein
#define ENCODER_DT    4
#define ENCODER_SW    5

#include "Wire.h"
#include "Adafruit_SSD1306.h"
Adafruit_SSD1306 Display(128, 64);      // Übergabe der Display-Breite und -Höhe                  

byte Modus = 11;
volatile byte EncoderStatus = 200;
volatile unsigned long RadSensor_Zeit = 0;
unsigned long Umdrehungen = 0;
unsigned long LetzteWerte[] = {0,0,0,0,0,0,0,0,0,0};
byte LetzteWerte_Index = 0;
unsigned long LetzteWerte_Timer = 0;
unsigned long aktivSekunden = 0;
unsigned long Knopfdruck = 0;
boolean BlinkIndikator = false;

void setup()
{  
  pinMode(ENCODER_DT, INPUT_PULLUP);
  pinMode(ENCODER_CLK, INPUT_PULLUP);
  pinMode(ENCODER_SW, INPUT_PULLUP);  
  pinMode(HALL_SENSOR, INPUT);
  pinMode(7, OUTPUT);
  digitalWrite(7, LOW);
  
  Display.begin(SSD1306_SWITCHCAPVCC, 60);  // Display-Verbindung initialisieren
                                            // (mit Standard-I²C-Adresse 60) 
  Display.setTextColor(WHITE);
  Display.clearDisplay();

  attachInterrupt(digitalPinToInterrupt(ENCODER_CLK), Encoder, RISING);
  attachInterrupt(digitalPinToInterrupt(HALL_SENSOR), UmdrehungZaehlen, RISING);
}

void loop()
{
  Display.clearDisplay();
  Display.setTextSize(1);
  
  Display.fillRect(122,58,127,63, BlinkIndikator ? WHITE: BLACK);

  if(Modus == 11)         // aktuelle Geschwindigkeit
  {
      Display.setTextSize(1);
      Display.setCursor(0,0);
      Display.print("aktuelle");
      Display.setCursor(0,10);
      Display.print("Geschwindigkeit  km/h"); 
      Display.setTextSize(4);
      Display.setCursor(0,30);
      long Umdrehungen10s = LetzteWerte[LetzteWerte_Index] - 
          LetzteWerte[(LetzteWerte_Index+1)%10];
      float Weg10s = Umdrehungen10s * RADUMFANG / 100.0;
      float kmh = Weg10s * 360.0/1000.0;
      Display.print(kmh);
  }

  if(Modus == 12)         // Durchschnittsgeschwindigkeit
  {
      Display.setTextSize(1);
      Display.setCursor(0,0);
      Display.print("Durchschnitts-");
      Display.setCursor(0,10);
      Display.print("Geschwindigkeit  km/h"); 
      Display.setTextSize(4);
      Display.setCursor(0,30);
      
      long Gesamtstrecke = Umdrehungen * RADUMFANG;         // in cm
      float kmh_ges = Gesamtstrecke * 3.6 / (aktivSekunden*100.0);        
      Display.print(kmh_ges);
  }  

  if(Modus == 13)         // Strecke
  {
      Display.setTextSize(1);
      Display.setCursor(0,0);
      Display.print("Gesamtstrecke      km");
      Display.setTextSize(4);
      Display.setCursor(0,30);
      float km = Umdrehungen * RADUMFANG / 100000.0;
      Display.print(km);
  }  

  if(Modus == 14)         // aktive Zeit
  {
      Display.setTextSize(1);
      Display.setCursor(0,0);
      Display.print("aktive Zeit      m:s");
      Display.setTextSize(4);
      Display.setCursor(0,30);
      Display.print(aktivSekunden/60);
      Display.print(":");
      if(aktivSekunden%60 < 10)
        Display.print("0"); 
      Display.print(aktivSekunden%60);
  }    

  Knopfdruck = millis();
  while(!digitalRead(ENCODER_SW))         // Zurücksetzen
  { 
      Display.clearDisplay();
      Display.setTextSize(2);
      Display.setCursor(0,0);
      Display.print("Loeschen?");

      if(millis() - Knopfdruck > 3000)      // nach 3 Sekunden
      {
        Display.setCursor(30,30);
        Display.print("Ok!");
        Umdrehungen = 0;
        aktivSekunden = 0;
        for(byte i = 0; i < 10; i++)
          LetzteWerte[i] = 0;
      }

      Display.display();
  }    

  Display.display(); 

                                  // Umdrehung detektiert?
  if(millis() - RadSensor_Zeit > 50 && RadSensor_Zeit != 0)
  {
    if(!digitalRead(HALL_SENSOR))
    {
      Umdrehungen++;
      BlinkIndikator = !BlinkIndikator;
    }
    RadSensor_Zeit = 0;
  }


  if(EncoderStatus != 200)          // wurde der Encoder bewegt?
  {
    if(EncoderStatus & B00010000)
      Modus++;
    else
      Modus--;
    EncoderStatus = 200;  
  }
  if(Modus > 14)
    Modus = 11;
  if(Modus < 11)
    Modus = 14;    


  if(millis() > LetzteWerte_Timer)  // jede Sekunde aktuelle Umdrehungszahl speichern
  {
    LetzteWerte_Index = (LetzteWerte_Index + 1) % 10;    
    LetzteWerte[LetzteWerte_Index] = Umdrehungen;
    LetzteWerte_Timer = millis() + 1000;
                                    
    if(LetzteWerte[LetzteWerte_Index] != LetzteWerte[(LetzteWerte_Index+1)%10])
      aktivSekunden++;              // aktive Zeit zählen
  }
}

void Encoder()
{
  EncoderStatus = PIND;   // D-Register enthält auch Pin D4 (DT-Pin des Encoders), dieser gibt Aufschluss über die Drehrichtung
}

void UmdrehungZaehlen()
{
  RadSensor_Zeit = millis();
}
