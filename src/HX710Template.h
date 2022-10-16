#ifndef _HX710_TEMPLATE_H_
#define _HX710_TEMPLATE_H_


#include "Arduino.h"
#include "HX710ClockManager.h"


#define HX710_DIFFERENTIAL_INPUT_10HZ  25
#define HX710_OTHER_INPUT_40HZ  26
#define HX710_DIFFERENTIAL_INPUT_40HZ  27



class HX710Template {

    ////////////////////////////////////////////////////////////////
    // PROTECTED ABSTRACT METHODS
    ////////////////////////////////////////////////////////////////
    protected:
        virtual bool isReady() = 0;
        virtual void beginData() = 0;
        virtual void readBitAndAddToData() = 0;
        virtual void endData( uint8_t pulses ) = 0;


    ////////////////////////////////////////////////////////////////
    // PUBLIC METHODS
    ////////////////////////////////////////////////////////////////
    public:
        HX710Template& initializeClockManager( uint8_t PD_SCK );  // initializes the clock manager
        HX710Template& powerDown();  // powers down the ADC
        HX710Template& powerUp();  // powers up the ADC
        HX710Template& readAndSelectNextData( uint8_t pulses );  // reads data, and selects next data using the number of pulses


    ////////////////////////////////////////////////////////////////
    // PRIVATE VARIABLES
    ////////////////////////////////////////////////////////////////
    private:
        HX710ClockManager cm;

};



#endif  // #ifndef _HX710_TEMPLATE_H_
