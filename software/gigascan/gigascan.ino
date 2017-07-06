#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); //Angabe der erforderlichen Pins
 
// erstellen einiger Variablen
int Taster = 0;
int Analogwert = 0;
#define Tasterrechts 0
#define Tasteroben 1
#define Tasterunten 2
#define Tasterlinks 3
#define Tasterselect 4
#define KeinTaster 5

const int panStepPin  = 24;
const int panDirPin   = 25;
const int tiltStepPin = 26;
const int tiltDirPin  = 27;
const int focusPin    = 22;
const int shutterPin  = 23;
 
// Ab hier wird ein neuer Programmblock mit dem Namen "Tasterstatus" erstellt. Hier wird ausschließlich ausschließlich geprüft, welcher Taster gedrückt ist.
int Tasterstatus()
{
Analogwert = analogRead(A0); // Auslesen der Taster am Analogen Pin A0.
if (Analogwert > 1000) return KeinTaster;
if (Analogwert < 50) return Tasterrechts;
if (Analogwert < 195) return Tasteroben;
if (Analogwert < 380) return Tasterunten;
if (Analogwert < 555) return Tasterlinks;
if (Analogwert < 790) return Tasterselect;
 
return KeinTaster; // Ausgabe wenn kein Taster gedrückt wurde.
}
// Hier wird der Programmblock "Tasterstatus" abeschlossen.


void setup() 
{
  pinMode(panStepPin, OUTPUT);
  pinMode(panDirPin, OUTPUT);
  pinMode(tiltStepPin, OUTPUT);
  pinMode(tiltDirPin, OUTPUT);
  pinMode(focusPin, OUTPUT);
  pinMode(shutterPin, OUTPUT);

  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Gigascan");
  lcd.setCursor(0,1);
  lcd.print("Mindfab.NET");
  delay(3000);
}

int mode = 0;
 
void loop()
{
  lcd.setCursor(0,1);
  lcd.print(mode + "          ");
  lcd.setCursor(12,1); // Bewegt den Cursor in Zeile 2 (Line0=Zeile1 und Line1=Zeile2) and die Stelle "12".
  lcd.print(millis()/1000); // Zeigt die Sekunden seit Start des Programms in Sekunden an.
  lcd.setCursor(0,1); // Bewegt den Cursor and die Stelle "0" in Zeile 2.

Taster = Tasterstatus(); //Hier springt der Loop in den oben angegebenen Programmabschnitt "Tasterstatus" und liest dort den gedrückten Taster aus.

switch (Taster) // Abhängig von der gedrückten Taste wird in dem folgenden switch-case Befehl entschieden, was auf dem LCD angezeigt wird.
{
case Tasterrechts: // Wenn die rechte Taste gedrückt wurde...
{
lcd.print("Rechts      "); //Erscheint diese Zeile. Die Leerzeichen hinter dem Text sorgen dafür, dass der vorherige Text in der Zeile gelöscht wird.
break;
}
case Tasterlinks:  // Wenn die linke Taste gedrückt wurde...
{
lcd.print("Links       ");  //Erscheint diese Zeile... usw...
break;
}
case Tasteroben:
{
lcd.print("Oben        ");
break;
}
case Tasterunten:
{
lcd.print("Unten       ");
break;
}
case Tasterselect:
{
  if (mode == 0) {
    mode = 1;
  } else {
    mode = 0;
  }
lcd.print("SELECT      " + mode);
break;
}
case KeinTaster:
{
  if (mode == 0) {
    lcd.print("idle      ");
  }
  if (mode == 1) {
      lcd.print("scanning... ");
      digitalWrite(panDirPin,HIGH); // Enables the motor to move in a particular direction
      // Makes 200 pulses for making one full cycle rotation
      for(int x = 0; x < 10; x++) {
        digitalWrite(panStepPin,HIGH); 
        delayMicroseconds(500); 
        digitalWrite(panStepPin,LOW); 
        delayMicroseconds(500); 
      }
      digitalWrite(focusPin, HIGH);
      delay(1000);
      digitalWrite(shutterPin, HIGH);
      delay(50);
      digitalWrite(focusPin, LOW);
      digitalWrite(shutterPin, LOW);   
  }
break;
}
} //switch-case Befehl beenden

} //Loop beenden
