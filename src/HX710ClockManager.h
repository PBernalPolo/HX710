#ifndef _HX710_CLOCK_MANAGER_H_
#define _HX710_CLOCK_MANAGER_H_


#include "Arduino.h"



class HX710ClockManager {

    ////////////////////////////////////////////////////////////////
    // PUBLIC METHODS
    ////////////////////////////////////////////////////////////////
    public:
        void initialize( uint8_t PD_SCK );  // initializes the clock manager
        void powerDown();  // sends the power down command through the clock signal
        void powerUp();  // sends the power up command through the clock signal
        void sendClockPulse();  // sends a clock pulse


    ////////////////////////////////////////////////////////////////
    // PRIVATE VARIABLES
    ////////////////////////////////////////////////////////////////
    private :
        uint8_t sck;  // PD_SCK

};



#endif  // #ifndef _HX710_CLOCK_MANAGER_H_
