// COSMOS - HOVEDPROGRAM!!!
// COSMOS
// Boksen har knapper
// boksen skal bare SENDE data
// Send data med INGEN LINJESKIFT

#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2, 3); // RX | TX

//Deklarering av variabler for lysdiode
const int RED_PIN = 8;
const int GREEN_PIN = 6;
const int BLUE_PIN = 7;


void setup() 
{
    //Hvilke pin som brukes
    
    // PinMode for poenggivningsknapp og belønningsknapp
    pinMode(4,INPUT);
    pinMode(5,INPUT); 
    // PinMode for lys
    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, HIGH);
    digitalWrite(BLUE_PIN, LOW);
    
    
    Serial.begin(9600);
    Serial.println("Arduino with HC-05 is ready");
 
    // BT-modulen starter paa default baud rate (9600)
    // Samme som HC-06
    BTSerial.begin(9600);  
    Serial.println("BTserial started at 9600");
}



int poeng = 0;
int stjerne = 0;
boolean storKnappTrykket = false; // knapp for hovedbrikken
boolean resetKnappTrykket = false; // knapp for reset av stjerner

int autoSendTeller = 0;

void loop()
{   
    autoSendTeller++;
    if (autoSendTeller > 25000) {
     // sendData();
     autoSendTeller = 0;
     //Denne brukes til testing ved a se om data blir sendt.
     Serial.println("Data sendt!");
    }
    // loop
    topKnappHendelse();
    resetKnappHendelse();
    
}

int highTeller = 0;
//Metode som registrerer trykk paa knappen oppa boksen
void topKnappHendelse() { // Knapp for top
  if(storKnappTrykket == false && digitalRead(4) == HIGH) {
    highTeller++;
    if (highTeller > 500) { // Unngår bug ved halvveis trykket knapp
      storKnappTrykket = true;
      //Brukes til testing for aa se om det registrerer at knappen er trykket inn
      Serial.println("Knapp trykket inn!");
      blinkBlaa();
      oekPoeng();
      test();
      sendData();
      
      
    }
  }
  else if (digitalRead(4) == LOW) {
    storKnappTrykket = false;
    highTeller = 0; //Else if-en registrer om at knappen er sluppet
    // Serial.println("Knapp sluppet!");
  }
}

int resetHighTeller = 0;
//Metode som registrerer om at nullstillingsknappen er trykket
void resetKnappHendelse() { // Knapp for top
  if(resetKnappTrykket == false && digitalRead(5) == HIGH) {
    resetHighTeller++;
    if (resetHighTeller > 500) { // Unngår bug ved halvveis trykket knapp
      blinkGul();
      resetKnappTrykket = true;
      brukStjerne();
      sendData();
    }
  }
  else if (digitalRead(5) == LOW) {
    resetKnappTrykket = false;
    resetHighTeller = 0;
  }
}

//En metode som oker poeng, og hvis poeng er mer enn 9, sa lyser den en stjerne.
void oekPoeng() { // Øker poengdata
  if (poeng < 9) { // poeng er under 9
    poeng++;
  } else { // poeng er 9 og skal gi en ny stjerne
    if (stjerne < 3) { // stjerner er mindre enn 3
      stjerne++;
      poeng = 0;
    } else { // detta suger litt, stjerne er 3.  slem forelder!
      // loesning her
    }
  }
}

//Metode som registrerer bruk av en stjerne. Denne brukes i nullstillingsmetoden
void brukStjerne() {
  if(stjerne > 0) {
    stjerne--;
    sendData();
  }
}

//Metoden definerer hva som skal sendes for aa tenne pa stjerne 1, 2, og 3
void sendData(){
  // send poeng via bluetooth til slave Arduino
  BTSerial.println(poeng);
  delay(50);
  if (stjerne == 0) {
    BTSerial.println('q');
  } else if (stjerne == 1) {
    BTSerial.println('w');
  } else if (stjerne == 2) {
    BTSerial.println('e');
  } else if (stjerne == 3) {
    BTSerial.println('r');
  }
}

//Metode som for aa teste 
void test() {
  Serial.println(poeng);
  Serial.println(stjerne);
}
//Metode som styrer hvilken farge RGB lysdioden skal lyse.
void blinkBlaa() {
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, HIGH);
  delay(50);
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN, LOW);
}
void blinkGul() {
  digitalWrite(RED_PIN, HIGH);
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN, LOW);
  delay(50);
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN, LOW);
}















 /*
  // Keep reading from HC-05 and send to Arduino Serial Monitor
  if (BTSerial.available()) {
    Serial.write(BTSerial.read());
  }

 
  // Keep reading from Arduino Serial Monitor and send to HC-05
  if (Serial.available()){
    BTSerial.write(Serial.read());
  } 
  */ 
