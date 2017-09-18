#include "pcint.h"

#ifdef PCINT_NO_MAPS
  HANDLER_TYPE PCintFunc[NUM_DIGITAL_PINS];
  template<int N>  void PCint() {PCintFunc[N]();}
  //static voidFuncPtr PCints[NUM_DIGITAL_PINS];
  //PCints[0]=PCint<0>;
  //PCints[1]=PCint<1>;
#else
  static int PCintMode[3][8];
  static HANDLER_TYPE PCintFunc[3][8];
  static bool PCintLast[3][8];//?we can use only 3 bytes... but will use more processing power calculating masks

  void PCattachInterrupt(uint8_t pin,HANDLER_TYPE userFunc, uint8_t mode) {
    volatile uint8_t *pcmask=digitalPinToPCMSK(pin);
    if (!pcmask) return;//runtime checking if pin has PCINT, i would prefer a compile time check
    uint8_t bit = digitalPinToPCMSKbit(pin);
    uint8_t mask = 1<<bit;
    uint8_t pcicrBit=digitalPinToPCICRbit(pin);
    PCintMode[pcicrBit][bit] = mode;
    PCintFunc[pcicrBit][bit] = userFunc;
    //initialize last status flags
    PCintLast[pcicrBit][bit]=(*portInputRegister(digitalPinToPort(pin)))&digitalPinToBitMask(pin);
    // set the mask
    *pcmask |= mask;
    // enable the interrupt
    PCICR |= (1<<pcicrBit);
  }

  void PCdetachInterrupt(uint8_t pin) {
    volatile uint8_t *pcmask=digitalPinToPCMSK(pin);
    if (!pcmask) return;//runtime checking if pin has PCINT, i would prefer a compile time check
    // disable the mask.
    *pcmask &= ~(1<<digitalPinToPCMSKbit(pin));
    // if that's the last one, disable the interrupt.
    if (*pcmask == 0)
      PCICR &= ~(1<<digitalPinToPCICRbit(pin));
  }

  // common code for isr handler. "port" is the PCINT number.
  // there isn't really a good way to back-map ports and masks to pins.
  // here we consider only the first change found ignoring subsequent, assuming no interrupt cascade
  static void PCint(uint8_t port) {
    const uint8_t* map=pcintPinMapBank(port);//get 8 bits pin change map
    for(int i=0;i<8;i++) {
      uint8_t p=digitalPinFromPCINTBank(map,i);
      if (p==-1)
        continue;//its not assigned
      //uint8_t bit = digitalPinToPCMSKbit(p);
      //uint8_t mask = (1<<bit);
      if (PCintFunc[port][i]!=NULL) {//only check active pins
        bool stat=(*portInputRegister(digitalPinToPort(p)))&digitalPinToBitMask(p);
        if (PCintLast[port][i]^stat) {//pin changed!
          PCintLast[port][i]=stat;//register change
          if (
            (PCintMode[port][i]==CHANGE)
            || ((stat)&&(PCintMode[port][i]==RISING))
            || ((!stat)&&(PCintMode[port][i]==FALLING))
          ) {
            PCintFunc[port][i]();
            break;//if using concurrent interrupts remove this
          }
        }
      }
    }
  }

  //AVR handle pin change... later figure out the pin
  SIGNAL(PCINT0_vect) {
    PCint(0);
  }
  SIGNAL(PCINT1_vect) {
    PCint(1);
  }
  SIGNAL(PCINT2_vect) {
    PCint(2);
  }
#endif
