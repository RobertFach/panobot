#include <LiquidCrystal.h>
#include "MenuLCD.h"
#include "MenuEntry.h"
#include "MenuIntHelper.h"
#include "MenuManager.h"
#include "AccelStepper.h"


const int LCDRS = 8;
const int LCDE  = 9;
const int LCDD4 = 4;
const int LCDD5 = 5;
const int LCDD6 = 6;
const int LCDD7 = 7;

const int PAN_STEP_PIN  = 24;
const int PAN_DIR_PIN   = 25;
const int TILT_STEP_PIN = 26;
const int TILT_DIR_PIN = 27;
const int FOCUS_PIN    = 22;
const int SHUTTER_PIN  = 23;

MenuLCD g_menuLCD( LCDRS, LCDE, LCDD4, LCDD5, LCDD6, LCDD7, 16, 2);
MenuManager g_menuManager( &g_menuLCD);

// erstellen einiger Variablen
int Taster = 0;
int Analogwert = 0;
#define Tasterrechts 0
#define Tasteroben 1
#define Tasterunten 2
#define Tasterlinks 3
#define Tasterselect 4
#define KEYPAD_NONE 5
#define KEYPAD_BLOCKED 6

// Ab hier wird ein neuer Programmblock mit dem Namen "Tasterstatus" erstellt. Hier wird ausschließlich ausschließlich geprüft, welcher Taster gedrückt ist.
int Tasterstatus()
{
Analogwert = analogRead(A0); // Auslesen der Taster am Analogen Pin A0.
if (Analogwert > 1000) return KEYPAD_NONE;
if (Analogwert < 50) return Tasterrechts;
if (Analogwert < 195) return Tasteroben;
if (Analogwert < 380) return Tasterunten;
if (Analogwert < 555) return Tasterlinks;
if (Analogwert < 790) return Tasterselect;
 
return KEYPAD_NONE; // Ausgabe wenn kein Taster gedrückt wurde.
}

unsigned long _block_time = 0;
int _last_button;

int blockedButton() {
  // if we are still blocked, return this status
  if (millis() < _block_time)
    return KEYPAD_BLOCKED;

  uint8_t current = Tasterstatus();

  // if some key is pressed, disable presses for block_delay or repeat_delay if button is kept down
  if (current != KEYPAD_NONE)
    _block_time = millis() + (current == _last_button ? 500 : 500);

  _last_button = current;
  return current;  
}


// Menu Structure
// Setup
// |-Max Pan Left
// |-Max Pan Right
// |-Max Tilt Up
// |-Max Tilt Down
// |-Pan Step
// |-Tilt Step
// Run Scan
// Credits

void setupMenus()
{
  g_menuLCD.MenuLCDSetup();
  
  MenuEntry * p_menuEntryRoot;
  p_menuEntryRoot = new MenuEntry("Setup", NULL, NULL);
  g_menuManager.addMenuRoot( p_menuEntryRoot );
  g_menuManager.addChild( new MenuEntry("Max Pan Left", NULL, setMaxPanLeftCallback));
//  g_menuManager.addChild( new MenuEntry("Max Pan Right", NULL, setMaxPanRightCallback));
//  g_menuManager.addChild( new MenuEntry("Max Tilt Up", NULL, setMaxTiltUpCallback));
//  g_menuManager.addChild( new MenuEntry("Max Tilt Down", NULL, setMaxTiltDownCallback));
//  g_menuManager.addChild( new MenuEntry("Pan Step", NULL, setMaxPanStepCallback));
//  g_menuManager.addChild( new MenuEntry("Tilt Step", NULL, setMaxTiltStepCallback));
  
  g_menuManager.addChild( new MenuEntry("Back", (void*) &g_menuManager, MenuEntry_BackCallbackFunc));
  g_menuManager.addSibling( new MenuEntry("Run Scan", NULL, runScanCallback));
  g_menuManager.addSibling( new MenuEntry("Credits", NULL, NULL));
  g_menuManager.DrawMenu();
}

AccelStepper panStepper(AccelStepper::DRIVER, PAN_STEP_PIN, PAN_DIR_PIN);
AccelStepper tiltStepper(AccelStepper::DRIVER, TILT_STEP_PIN, TILT_DIR_PIN);

void setup() 
{
  panStepper.setMaxSpeed(200.0);
  panStepper.setAcceleration(200.0);
  setupMenus();
}

boolean g_runScan = false;
 
int pan_step_per_deg = 100;

void loop()
{
Taster = blockedButton(); //Hier springt der Loop in den oben angegebenen Programmabschnitt "Tasterstatus" und liest dort den gedrückten Taster aus.

switch (Taster) // Abhängig von der gedrückten Taste wird in dem folgenden switch-case Befehl entschieden, was auf dem LCD angezeigt wird.
{
case Tasterrechts: // Wenn die rechte Taste gedrückt wurde...
{
  break;
}
case Tasterlinks:  // Wenn die linke Taste gedrückt wurde...
{
  g_menuManager.DoMenuAction( MENU_ACTION_BACK);
  break;
}
case Tasteroben:
{
  g_menuManager.DoMenuAction( MENU_ACTION_UP);
  break;
}
case Tasterunten:
{
  g_menuManager.DoMenuAction( MENU_ACTION_DOWN);
  break;
}
case Tasterselect:
{
  g_menuManager.DoMenuAction( MENU_ACTION_SELECT);  
  break;
}
case KEYPAD_NONE:
{
//  if (mode == 1) {
//      digitalWrite(panDirPin,HIGH); // Enables the motor to move in a particular direction
//      // Makes 200 pulses for making one full cycle rotation
//      for(int x = 0; x < 10; x++) {
//        digitalWrite(panStepPin,HIGH); 
//        delayMicroseconds(500); 
//        digitalWrite(panStepPin,LOW); 
//        delayMicroseconds(500); 
//      }
//      digitalWrite(focusPin, HIGH);
//      delay(1000);
//      digitalWrite(shutterPin, HIGH);
//      delay(50);
//      digitalWrite(focusPin, LOW);
//      digitalWrite(shutterPin, LOW);   
//  }
break;
}
} //switch-case Befehl beenden
  if (g_runScan) {
    if (panStepper.distanceToGo() == 0)
      panStepper.moveTo(-panStepper.currentPosition());
  }
  panStepper.run();
} //Loop beenden

void rotatePan(int deg)
{
  
}

void runScanCallback( char* pMenuText, void*pUserData)
{
  g_runScan = true; 
  panStepper.moveTo(100);
}

void setMaxPanLeftCallback( char* pMenuText, void*pUserData)
{

}
