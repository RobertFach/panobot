//Stepper Pins for Pan Stepper
#define PAN_STEP_PIN  24
#define PAN_DIR_PIN 25
//Stepper Pins for Tilt Stepper
#define TILT_STEP_PIN 26
#define TILT_DIR_PIN 27
//Pins to the Optocopplers for focus & shutter
#define FOCUS_PIN 22
#define SHUTTER_PIN 23

//SmartLCD display pins, for hardware SPI use these, CS can be rerouted
#define DISPLAY_CLOCK_PIN 52 //CLK
#define DISPLAY_DATA_PIN 51 //MOSI
#define DISPLAY_CS_PIN 34

//SmartLCD clickencoder pins, ecoder a/b uses PCINT, so make sure that its supported
#define ENCODER_A_PIN A8
#define ENCODER_B_PIN A9
//negative means active internal pull-up
#define ENCODER_BTN_PIN -44
#define DISPLAY_RESET_BTN_PIN -45 //negative means active internal pull-up
