// STELLA - HOVEDPROGRAM!!!
// STELLA
// Boksen har stjerner og poeng
// boksen skal bare TA IMOT data
// Send til denne med INGEN LINJESKIFT

#include <Adafruit_NeoPixel.h>
#define PIN      6
#define N_LEDS 66
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2, 3); // RX | TX
char btVal = ' '; //Variablen som mottas
 

void setup() 
{
    strip.begin();
    Serial.begin(9600);
    Serial.println("Arduino with HC-06 is ready");
 
    // BT-modulen starter paa default baud rate (9600)
    // Samme som HC-05
    BTSerial.begin(9600);  
    Serial.println("BTserial started at 9600");
}
 
void loop()
{
  
  // Kontinuerlig lesing fra HC-05 og sender til Arduino serial monitor.
  if (BTSerial.available()) {
    btVal = BTSerial.read();
    if ((btVal-48) >= 0 && (btVal-48) <= 9) { // Oppdatere poeng (verdier fra 1-9)
      oppdaterPoeng(strip.Color(20, 20, 40), (btVal-48));
    } else if ((btVal+0) == 113) { // Oppdater stjerne (q = 113)
      oppdaterStjerne(strip.Color(120, 120, 0), (0));
    } else if ((btVal+0) == 119) { // Oppdater stjerne (w = 119)
      oppdaterStjerne(strip.Color(120, 120, 0), (1));
    } else if ((btVal+0) == 101) { // Oppdater stjerne (e = 101)
      oppdaterStjerne(strip.Color(120, 120, 0), (2));
    } else if ((btVal+0) == 114) { // Set stjerne til 0 (r = 114)
      oppdaterStjerne(strip.Color(120, 120, 0), (3));
    } 
    
    
    Serial.write(btVal);
    
  }
    
  /*
  // Keep reading from Arduino Serial Monitor and send to HC-05
  if (Serial.available()){
    BTSerial.write(Serial.read());
  } 
  */
}

//Metoden oppdaterer poeng, og lyser / slukker LED dioder.
static void oppdaterPoeng(uint32_t c, int poeng) {
  for(uint16_t i=0; i<poeng; i++) {
      strip.setPixelColor(i  , c);
      strip.show();
  }
  for(uint16_t i=poeng; i<=9; i++) {   
      strip.setPixelColor(i, 0);
      strip.show();
  }
}

//Metoden er lik oppdaterPoeng(), men styrer stjerner selvom det er samme LED strip.
static void oppdaterStjerne(uint32_t c, int stjerner) {
  if (stjerner == 0) {
     strip.setPixelColor(21  , 0);
     strip.setPixelColor(18  , 0);
     strip.setPixelColor(15  , 0);
     strip.show();
  } else if(stjerner == 1) {
     strip.setPixelColor(21  , c);
     strip.setPixelColor(18  , 0);
     strip.setPixelColor(15  , 0);
     strip.show();
  } else if (stjerner == 2) {
     strip.setPixelColor(21  , c);
     strip.setPixelColor(18  , c);
     strip.setPixelColor(15  , 0);
     strip.show();
  } else if (stjerner == 3) {
     strip.setPixelColor(21  , c);
     strip.setPixelColor(18  , c);
     strip.setPixelColor(15  , c);
     strip.show();
  }
}
